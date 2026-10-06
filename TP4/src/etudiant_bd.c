#include <stdio.h>

#define NOMBRE_ETUDIANTS 5

struct etudiant {
    char nom[64];
    char prenom[64];
    char adresse[256];
    float note_programmation;
    float note_systeme;
};

static int lire_chaine(const char *invite, char *destination, size_t taille)
{
    printf("%s", invite);
    if (fgets(destination, taille, stdin) == NULL) {
        return 0;
    }
    size_t i = 0;
    while (destination[i] != '\0' && destination[i] != '\n') {
        i++;
    }
    destination[i] = '\0';
    return i < taille - 1 || destination[i] == '\n';
}

int main(void)
{
    struct etudiant etudiants[NOMBRE_ETUDIANTS];
    FILE *fichier = fopen("etudiant.txt", "w");

    if (fichier == NULL) {
        perror("etudiant.txt");
        return 1;
    }

    for (int i = 0; i < NOMBRE_ETUDIANTS; i++) {
        printf("Entrez les détails de l'étudiant.e %d :\n", i + 1);
        if (!lire_chaine("Nom : ", etudiants[i].nom, sizeof etudiants[i].nom)
            || !lire_chaine("Prénom : ", etudiants[i].prenom, sizeof etudiants[i].prenom)
            || !lire_chaine("Adresse : ", etudiants[i].adresse, sizeof etudiants[i].adresse)) {
            fprintf(stderr, "Saisie de texte invalide ou trop longue.\n");
            (void)fclose(fichier);
            return 1;
        }
        printf("Note 1 : ");
        if (scanf("%f", &etudiants[i].note_programmation) != 1) {
            fprintf(stderr, "Note invalide.\n");
            (void)fclose(fichier);
            return 1;
        }
        printf("Note 2 : ");
        if (scanf("%f", &etudiants[i].note_systeme) != 1) {
            fprintf(stderr, "Note invalide.\n");
            (void)fclose(fichier);
            return 1;
        }
        (void)getchar();

        if (fprintf(fichier, "%s;%s;%s;%.2f;%.2f\n",
                    etudiants[i].nom, etudiants[i].prenom, etudiants[i].adresse,
                    etudiants[i].note_programmation, etudiants[i].note_systeme) < 0) {
            perror("Erreur d'écriture");
            (void)fclose(fichier);
            return 1;
        }
    }

    if (fclose(fichier) != 0) {
        perror("Erreur de fermeture");
        return 1;
    }
    printf("Les détails des étudiants ont été enregistrés dans etudiant.txt.\n");
    return 0;
}