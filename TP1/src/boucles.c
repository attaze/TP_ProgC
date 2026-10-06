#include <stdio.h>

int main(void)
{
    int compteur;

    printf("Entrez la taille du triangle (entre 1 et 9) : ");
    if (scanf("%d", &compteur) != 1 || compteur < 1 || compteur >= 10) {
        fprintf(stderr, "La taille doit être un entier entre 1 et 9.\n");
        return 1;
    }

    printf("Triangle avec des boucles for :\n");
    for (int ligne = 1; ligne <= compteur; ligne++) {
        for (int colonne = 1; colonne <= ligne; colonne++) {
            if (ligne == 1 || ligne == compteur
                || colonne == 1 || colonne == ligne) {
                printf("*");
            } else {
                printf("#");
            }
            if (colonne < ligne) {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Triangle avec des boucles while :\n");
    int ligne = 1;
    while (ligne <= compteur) {
        int colonne = 1;
        while (colonne <= ligne) {
            if (ligne == 1 || ligne == compteur
                || colonne == 1 || colonne == ligne) {
                printf("*");
            } else {
                printf("#");
            }
            if (colonne < ligne) {
                printf(" ");
            }
            colonne++;
        }
        printf("\n");
        ligne++;
    }

    return 0;
}