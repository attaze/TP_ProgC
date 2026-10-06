#define _POSIX_C_SOURCE 200809L

#include "serveur.h"

#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int socket_serveur = -1;
static volatile sig_atomic_t arret_demande = 0;

static void gerer_sigint(int signal_recu)
{
    (void)signal_recu;
    arret_demande = 1;
    if (socket_serveur >= 0) {
        (void)close(socket_serveur);
        socket_serveur = -1;
    }
}

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
            if (longueur == 0) {
                return 0;
            }
            break;
        }
        if (resultat < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("recv");
            return -1;
        }
        if (caractere == '\n') {
            break;
        }
        tampon[longueur++] = caractere;
    }
    tampon[longueur] = '\0';
    return 1;
}

int renvoie_message(int client_socket_fd, const char *message)
{
    char ligne[TAILLE_MESSAGE + 2];
    int longueur = snprintf(ligne, sizeof ligne, "%s\n", message);
    if (longueur < 0 || (size_t)longueur >= sizeof ligne) {
        fprintf(stderr, "Réponse trop longue.\n");
        return EXIT_FAILURE;
    }
    return envoyer_texte(client_socket_fd, ligne) ? EXIT_SUCCESS : EXIT_FAILURE;
}

static int calculer(char operateur, long long gauche, long long droite,
                    long long *resultat)
{
    switch (operateur) {
    case '+':
        *resultat = gauche + droite;
        return 1;
    case '-':
        *resultat = gauche - droite;
        return 1;
    case '*':
        *resultat = gauche * droite;
        return 1;
    case '/':
        if (droite == 0) {
            return 0;
        }
        *resultat = gauche / droite;
        return 1;
    case '%':
        if (droite == 0) {
            return 0;
        }
        *resultat = gauche % droite;
        return 1;
    case '&':
        *resultat = gauche & droite;
        return 1;
    case '|':
        *resultat = gauche | droite;
        return 1;
    case '~':
        *resultat = ~gauche;
        return 1;
    default:
        return 0;
    }
}

static int traiter_calcul(int client_socket_fd, const char *message)
{
    char operateur;
    long long num1;
    long long num2;
    long long resultat;
    int consommes = 0;

    if (sscanf(message, "calcule : %c %lld %lld %n",
               &operateur, &num1, &num2, &consommes) != 3
        && sscanf(message, "%c %lld %lld %n",
                  &operateur, &num1, &num2, &consommes) != 3) {
        return renvoie_message(client_socket_fd, "Erreur : calcul invalide");
    }
    while (message[consommes] == ' ' || message[consommes] == '\t') {
        consommes++;
    }
    if (message[consommes] != '\0'
        || !calculer(operateur, num1, num2, &resultat)) {
        return renvoie_message(client_socket_fd,
                               "Erreur : opération invalide ou division par zéro");
    }

    char reponse[128];
    (void)snprintf(reponse, sizeof reponse, "calcule : %lld", resultat);
    return renvoie_message(client_socket_fd, reponse);
}

int recois_envoie_message(int client_socket_fd, char *message)
{
    printf("Message reçu : %s\n", message);
    if (strncmp(message, "message: ", 9) == 0) {
        char reponse[TAILLE_MESSAGE];
        printf("Réponse à envoyer au client : ");
        fflush(stdout);
        if (fgets(reponse, sizeof reponse, stdin) == NULL) {
            return renvoie_message(client_socket_fd,
                                   "Erreur : aucune réponse saisie par le serveur");
        }
        size_t longueur = strcspn(reponse, "\n");
        reponse[longueur] = '\0';
        char message_reponse[TAILLE_MESSAGE + 16];
        int taille = snprintf(message_reponse, sizeof message_reponse,
                              "message: %s", reponse);
        if (taille < 0 || (size_t)taille >= sizeof message_reponse) {
            return renvoie_message(client_socket_fd, "Erreur : réponse trop longue");
        }
        return renvoie_message(client_socket_fd, message_reponse);
    }
    if (strncmp(message, "calcule :", 9) == 0
        || strchr("+-*/%&|~", message[0]) != NULL) {
        return traiter_calcul(client_socket_fd, message);
    }
    return renvoie_message(client_socket_fd, "Erreur : requête inconnue");
}

static void gerer_client(int client_socket_fd)
{
    char message[TAILLE_MESSAGE];
    while (!arret_demande) {
        int statut = recevoir_ligne(client_socket_fd, message, sizeof message);
        if (statut <= 0) {
            if (statut < 0) {
                perror("réception");
            }
            break;
        }
        if (recois_envoie_message(client_socket_fd, message) != EXIT_SUCCESS) {
            break;
        }
    }
    (void)close(client_socket_fd);
}

int main(void)
{
    struct sockaddr_in adresse;
    int option = 1;

    socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_serveur < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }
    if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR,
                   &option, sizeof option) != 0) {
        perror("setsockopt");
        (void)close(socket_serveur);
        return EXIT_FAILURE;
    }
    memset(&adresse, 0, sizeof adresse);
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(PORT);
    adresse.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socket_serveur, (struct sockaddr *)&adresse, sizeof adresse) != 0) {
        perror("bind");
        (void)close(socket_serveur);
        return EXIT_FAILURE;
    }
    if (listen(socket_serveur, 10) != 0) {
        perror("listen");
        (void)close(socket_serveur);
        return EXIT_FAILURE;
    }
    (void)signal(SIGINT, gerer_sigint);
    (void)signal(SIGPIPE, SIG_IGN);
    printf("Serveur en attente de connexions...\n");
    fflush(stdout);

    while (!arret_demande) {
        struct sockaddr_in adresse_client;
        socklen_t longueur_adresse = sizeof adresse_client;
        int client_socket_fd = accept(socket_serveur,
                                      (struct sockaddr *)&adresse_client,
                                      &longueur_adresse);
        if (client_socket_fd < 0) {
            if (errno == EINTR || arret_demande) {
                continue;
            }
            perror("accept");
            continue;
        }
        gerer_client(client_socket_fd);
    }

    if (socket_serveur >= 0) {
        (void)close(socket_serveur);
    }
    return EXIT_SUCCESS;
}
