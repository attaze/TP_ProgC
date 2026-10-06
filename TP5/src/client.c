#define _POSIX_C_SOURCE 200809L

#include "client.h"

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int envoyer_texte(int socketfd, const char *texte)
{
    size_t longueur = strlen(texte);
    size_t envoye = 0;
    while (envoye < longueur) {
        ssize_t resultat = send(socketfd, texte + envoye, longueur - envoye, 0);
        if (resultat < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("send");
            return 0;
        }
        envoye += (size_t)resultat;
    }
    return 1;
}

static int recevoir_ligne(int socketfd, char *tampon, size_t capacite)
{
    size_t longueur = 0;
    while (longueur + 1 < capacite) {
        char caractere;
        ssize_t resultat = recv(socketfd, &caractere, 1, 0);
        if (resultat == 0) {
            break;
        }
        if (resultat < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("recv");
            return 0;
        }
        if (caractere == '\n') {
            break;
        }
        tampon[longueur++] = caractere;
    }
    tampon[longueur] = '\0';
    return longueur > 0;
}

int envoie_recois_message(int socketfd)
{
    char message[TAILLE_MESSAGE];
    char demande[TAILLE_MESSAGE + 16];
    char reponse[TAILLE_MESSAGE];

    printf("Message (ou 'calcule : op n1 n2', 'quit' pour quitter) : ");
    if (fgets(message, sizeof message, stdin) == NULL) {
        return 0;
    }
    size_t longueur = strcspn(message, "\n");
    message[longueur] = '\0';
    if (strcmp(message, "quit") == 0) {
        return 0;
    }

    if (strncmp(message, "calcule :", 9) != 0
        && strncmp(message, "+ ", 2) != 0
        && strncmp(message, "- ", 2) != 0
        && strncmp(message, "* ", 2) != 0
        && strncmp(message, "/ ", 2) != 0
        && strncmp(message, "% ", 2) != 0
        && strncmp(message, "& ", 2) != 0
        && strncmp(message, "| ", 2) != 0
        && strncmp(message, "~ ", 2) != 0) {
        if (snprintf(demande, sizeof demande, "message: %s\n", message)
            >= (int)sizeof demande) {
            fprintf(stderr, "Message trop long.\n");
            return 1;
        }
    } else if (snprintf(demande, sizeof demande, "%s\n", message)
               >= (int)sizeof demande) {
        fprintf(stderr, "Message trop long.\n");
        return 1;
    }

    if (!envoyer_texte(socketfd, demande)) {
        return -1;
    }
    if (!recevoir_ligne(socketfd, reponse, sizeof reponse)) {
        fprintf(stderr, "Le serveur a fermé la connexion sans réponse.\n");
        return -1;
    }
    printf("Message reçu : %s\n", reponse);
    return 1;
}

int envoie_operateur_numeros(int socketfd, char operateur,
                            long long num1, long long num2)
{
    char demande[128];
    char reponse[TAILLE_MESSAGE];
    int longueur = snprintf(demande, sizeof demande,
                            "calcule : %c %lld %lld\n",
                            operateur, num1, num2);
    if (longueur < 0 || (size_t)longueur >= sizeof demande
        || !envoyer_texte(socketfd, demande)
        || !recevoir_ligne(socketfd, reponse, sizeof reponse)) {
        return 0;
    }
    printf("%s\n", reponse);
    return 1;
}

static int envoyer_notes(int socketfd, int nombre_fichiers, char **fichiers)
{
    long long somme = 0;

    for (int i = 0; i < nombre_fichiers; i++) {
        FILE *fichier = fopen(fichiers[i], "r");
        long long note;
        if (fichier == NULL) {
            perror(fichiers[i]);
            return 0;
        }
        if (fscanf(fichier, "%lld", &note) != 1) {
            fprintf(stderr, "Note entière invalide dans %s.\n", fichiers[i]);
            (void)fclose(fichier);
            return 0;
        }
        if (fclose(fichier) != 0) {
            perror("fclose");
            return 0;
        }
        if (i == 0) {
            somme = note;
        } else {
            char reponse[TAILLE_MESSAGE];
            char demande[128];
            int longueur = snprintf(demande, sizeof demande,
                                    "calcule : + %lld %lld\n", somme, note);
            if (longueur < 0 || (size_t)longueur >= sizeof demande
                || !envoyer_texte(socketfd, demande)
                || !recevoir_ligne(socketfd, reponse, sizeof reponse)
                || sscanf(reponse, "calcule : %lld", &somme) != 1) {
                fprintf(stderr, "Réponse de calcul invalide du serveur.\n");
                return 0;
            }
        }
    }

    char reponse[TAILLE_MESSAGE];
    char demande[128];
    int longueur = snprintf(demande, sizeof demande,
                            "calcule : / %lld %d\n", somme, nombre_fichiers);
    if (longueur < 0 || (size_t)longueur >= sizeof demande
        || !envoyer_texte(socketfd, demande)
        || !recevoir_ligne(socketfd, reponse, sizeof reponse)) {
        return 0;
    }
    printf("Moyenne entière : %s\n", reponse);
    return 1;
}

static int connecter(void)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in adresse;
    memset(&adresse, 0, sizeof adresse);
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(PORT);
    adresse.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(socketfd, (struct sockaddr *)&adresse, sizeof adresse) != 0) {
        perror("connect");
        (void)close(socketfd);
        return -1;
    }
    return socketfd;
}

int main(int argc, char **argv)
{
    int socketfd = connecter();
    if (socketfd < 0) {
        return EXIT_FAILURE;
    }

    int succes = 1;
    if (argc >= 3 && strcmp(argv[1], "--notes") == 0) {
        succes = envoyer_notes(socketfd, argc - 2, argv + 2);
    } else if (argc != 1) {
        fprintf(stderr, "Utilisation : %s [--notes fichier1 ... fichierN]\n", argv[0]);
        succes = 0;
    } else {
        int statut;
        do {
            statut = envoie_recois_message(socketfd);
        } while (statut > 0);
        succes = statut == 0;
    }

    (void)close(socketfd);
    return succes ? EXIT_SUCCESS : EXIT_FAILURE;
}
