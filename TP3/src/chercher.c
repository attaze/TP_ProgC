#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

int main(void)
{
    int nombres[TAILLE];
    int recherche;
    int present = 0;

    srand((unsigned int)time(NULL));
    for (int i = 0; i < TAILLE; i++) {
        nombres[i] = rand() % 1000 + 1;
        printf("%d%c", nombres[i], i == TAILLE - 1 ? '\n' : ' ');
    }

    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &recherche) != 1) {
        fprintf(stderr, "Valeur invalide.\n");
        return 1;
    }

    for (int i = 0; i < TAILLE; i++) {
        if (nombres[i] == recherche) {
            present = 1;
            break;
        }
    }

    printf("Résultat : entier %s\n", present ? "présent" : "absent");
    return 0;
}