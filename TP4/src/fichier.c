#include "fichier.h"

#include <stdio.h>

int lire_fichier(const char *nom_de_fichier)
{
    FILE *fichier = fopen(nom_de_fichier, "r");
    char ligne[1024];

    if (fichier == NULL) {
        perror(nom_de_fichier);
        return 0;
    }

    printf("Contenu du fichier %s :\n", nom_de_fichier);
    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        fputs(ligne, stdout);
    }
    if (ferror(fichier)) {
        perror("Erreur de lecture");
        (void)fclose(fichier);
        return 0;
    }
    if (fclose(fichier) != 0) {
        perror("Erreur de fermeture");
        return 0;
    }
    return 1;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
    FILE *fichier = fopen(nom_de_fichier, "w");
    if (fichier == NULL) {
        perror(nom_de_fichier);
        return 0;
    }

    if (fputs(message, fichier) == EOF || fputc('\n', fichier) == EOF) {
        perror("Erreur d'écriture");
        (void)fclose(fichier);
        return 0;
    }
    if (fclose(fichier) != 0) {
        perror("Erreur de fermeture");
        return 0;
    }
    printf("Le message a été écrit dans le fichier %s.\n", nom_de_fichier);
    return 1;
}