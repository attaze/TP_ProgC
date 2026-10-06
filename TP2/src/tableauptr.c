#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 10

int main(void)
{
    int entiers[TAILLE];
    float reels[TAILLE];
    int *p_entier;
    float *p_reel;

    srand((unsigned int)time(NULL));
    for (p_entier = entiers, p_reel = reels;
         p_entier < entiers + TAILLE; p_entier++, p_reel++) {
        *p_entier = rand() % 100 + 1;
        *p_reel = (float)(rand() % 1000) / 100.0f;
    }

    printf("Entiers avant :");
    for (p_entier = entiers; p_entier < entiers + TAILLE; p_entier++) {
        printf(" %d", *p_entier);
    }
    printf("\nRéels avant :");
    for (p_reel = reels; p_reel < reels + TAILLE; p_reel++) {
        printf(" %.2f", (double)*p_reel);
    }
    printf("\n");

    for (p_entier = entiers, p_reel = reels;
         p_entier < entiers + TAILLE; p_entier += 2, p_reel += 2) {
        *p_entier *= 3;
        *p_reel *= 3.0f;
    }

    printf("Entiers après :");
    for (p_entier = entiers; p_entier < entiers + TAILLE; p_entier++) {
        printf(" %d", *p_entier);
    }
    printf("\nRéels après :");
    for (p_reel = reels; p_reel < reels + TAILLE; p_reel++) {
        printf(" %.2f", (double)*p_reel);
    }
    printf("\n");
    return 0;
}