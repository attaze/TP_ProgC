
#include "fichier.h"
#include "liste.h"
#include "operator.h"

#include <stdio.h>

static int executer_calcul(void)
{
    int num1;
    int num2;
    int resultat;
    char operateur;

    printf("Entrez num1 : ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Valeur invalide.\n");
        return 1;
    }
    printf("Entrez num2 : ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Valeur invalide.\n");
        return 1;
    }
    printf("Entrez l'opérateur (+, -, *, /, %%, &, |, ~) : ");
    if (scanf(" %c", &operateur) != 1) {
        fprintf(stderr, "Opérateur invalide.\n");
        return 1;
    }

    if (!appliquer_operation(num1, num2, operateur, &resultat)) {
        fprintf(stderr, "Opération invalide ou division par zéro.\n");
        return 1;
    }
    printf("Résultat : %d\n", resultat);
    return 0;
}

static int executer_fichier(void)
{
    char nom[256];
    char message[1024];
    int choix;

    printf("1. Lire un fichier\n2. Écrire dans un fichier\nVotre choix : ");
    if (scanf("%d", &choix) != 1) {
        fprintf(stderr, "Choix invalide.\n");
        return 1;
    }
    (void)getchar();

    printf("Entrez le nom du fichier : ");
    if (fgets(nom, sizeof nom, stdin) == NULL) {
        fprintf(stderr, "Impossible de lire le nom du fichier.\n");
        return 1;
    }
    size_t longueur = 0;
    while (nom[longueur] != '\0' && nom[longueur] != '\n') {
        longueur++;
    }
    nom[longueur] = '\0';

    if (choix == 1) {
        return lire_fichier(nom) ? 0 : 1;
    }
    if (choix != 2) {
        fprintf(stderr, "Choix invalide.\n");
        return 1;
    }

    printf("Entrez le message à écrire : ");
    if (fgets(message, sizeof message, stdin) == NULL) {
        fprintf(stderr, "Impossible de lire le message.\n");
        return 1;
    }
    longueur = 0;
    while (message[longueur] != '\0' && message[longueur] != '\n') {
        longueur++;
    }
    message[longueur] = '\0';
    return ecrire_dans_fichier(nom, message) ? 0 : 1;
}

static int executer_liste(void)
{
    const struct couleur couleurs[10] = {
        {0xff, 0x00, 0x00, 0xff}, {0x00, 0xff, 0x00, 0xff},
        {0x00, 0x00, 0xff, 0xff}, {0xff, 0xff, 0x00, 0xff},
        {0xff, 0x00, 0xff, 0xff}, {0x00, 0xff, 0xff, 0xff},
        {0x80, 0x00, 0x00, 0xff}, {0x00, 0x80, 0x00, 0xff},
        {0x00, 0x00, 0x80, 0xff}, {0x80, 0x80, 0x80, 0xff}
    };
    struct liste_couleurs liste;
    init_liste(&liste);

    for (int i = 0; i < 10; i++) {
        if (!insertion(&couleurs[i], &liste)) {
            liberer_liste(&liste);
            return 1;
        }
    }

    printf("Liste des couleurs :\n");
    parcours(&liste);
    liberer_liste(&liste);
    return 0;
}

int main(void)
{
    int exercice;

    printf("Choisissez l'exercice (1 : opérateurs, 2 : fichiers, 7 : liste) : ");
    if (scanf("%d", &exercice) != 1) {
        fprintf(stderr, "Choix invalide.\n");
        return 1;
    }

    switch (exercice) {
    case 1:
        return executer_calcul();
    case 2:
        return executer_fichier();
    case 7:
        return executer_liste();
    default:
        fprintf(stderr, "Exercice non géré par ce programme.\n");
        return 1;
    }
}
