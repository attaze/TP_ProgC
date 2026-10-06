#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

static int comparer_entiers(const void *a, const void *b)
{
    int gauche = *(const int *)a;
    int droite = *(const int *)b;
    return (gauche > droite) - (gauche < droite);
}

static void afficher_tableau(const int nombres[TAILLE])
{
    for (int i = 0; i < TAILLE; i++) {
        printf("%d%c", nombres[i], i == TAILLE - 1 ? '\n' : ' ');
    }
}

int main(void)
{
    int nombres[TAILLE];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < TAILLE; i++) {
        nombres[i] = rand() % 2001 - 1000;
    }

    printf("Tableau non trié :\n");
    afficher_tableau(nombres);
    qsort(nombres, TAILLE, sizeof nombres[0], comparer_entiers);
    printf("Tableau trié par ordre croissant :\n");
    afficher_tableau(nombres);
    return 0;
}