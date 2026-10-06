
#include <stdio.h>

int main(void)
{
    const int hauteur = 5;

    for (int ligne = 1; ligne <= hauteur; ligne++) {
        for (int espace = ligne; espace < hauteur; espace++) {
            printf(" ");
        }
        for (int chiffre = 1; chiffre <= ligne; chiffre++) {
            printf("%d", chiffre);
        }
        for (int chiffre = ligne - 1; chiffre >= 1; chiffre--) {
            printf("%d", chiffre);
        }
        printf("\n");
    }

    printf("Pyramide terminée.\n");
    return 0;
}
