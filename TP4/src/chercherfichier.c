#include <stdio.h>
#include <string.h>

#define TAILLE_LIGNE 4096
#define TAILLE_PHRASE 1024

int main(int argc, char *argv[])
{
    char phrase[TAILLE_PHRASE];
    char ligne[TAILLE_LIGNE];
    unsigned long numero_ligne = 0;
    FILE *fichier;

    if (argc != 2) {
        fprintf(stderr, "Utilisation : %s <nom_du_fichier>\n", argv[0]);
        return 1;
    }

    printf("Entrez la phrase que vous souhaitez rechercher : ");
    if (fgets(phrase, sizeof phrase, stdin) == NULL) {
        fprintf(stderr, "Impossible de lire la phrase.\n");
        return 1;
    }
    size_t longueur = strcspn(phrase, "\n");
    phrase[longueur] = '\0';
    if (longueur == 0) {
        fprintf(stderr, "La phrase recherchée ne peut pas être vide.\n");
        return 1;
    }

    fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        perror(argv[1]);
        return 1;
    }

    printf("Résultats de la recherche :\n");
    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        unsigned int occurrences = 0;
        char *position = ligne;
        numero_ligne++;
        while ((position = strstr(position, phrase)) != NULL) {
            occurrences++;
            position += longueur;
        }
        if (occurrences > 0) {
            printf("Ligne %lu, %u fois\n", numero_ligne, occurrences);
        }
    }
    if (ferror(fichier)) {
        perror("Erreur de lecture");
        (void)fclose(fichier);
        return 1;
    }
    if (fclose(fichier) != 0) {
        perror("Erreur de fermeture");
        return 1;
    }
    return 0;
}