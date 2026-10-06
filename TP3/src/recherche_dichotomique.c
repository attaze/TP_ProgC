#include <stdio.h>

#define TAILLE 100

int main(void)
{
    int nombres[TAILLE];
    int recherche;

    for (int i = 0; i < TAILLE; i++) {
        nombres[i] = i * 2;
        printf("%d%c", nombres[i], i == TAILLE - 1 ? '\n' : ' ');
    }

    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &recherche) != 1) {
        fprintf(stderr, "Valeur invalide.\n");
        return 1;
    }

    int gauche = 0;
    int droite = TAILLE - 1;
    int present = 0;
    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;
        if (nombres[milieu] == recherche) {
            present = 1;
            break;
        }
        if (nombres[milieu] < recherche) {
            gauche = milieu + 1;
        } else {
            droite = milieu - 1;
        }
    }

    printf("Résultat : entier %s\n", present ? "présent" : "absent");
    return 0;
}