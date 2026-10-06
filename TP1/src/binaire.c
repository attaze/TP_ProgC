#include <limits.h>
#include <stdio.h>

int main(void)
{
    const int nombres[] = {0, 4096, 65536, 65535, 1024};
    const int nombre_de_valeurs = (int)(sizeof nombres / sizeof nombres[0]);

    for (int i = 0; i < nombre_de_valeurs; i++) {
        unsigned int valeur = (unsigned int)nombres[i];
        int bit_debut = 1;

        printf("%d en binaire : ", nombres[i]);
        for (int bit = (int)(sizeof valeur * CHAR_BIT) - 1; bit >= 0; bit--) {
            unsigned int chiffre = (valeur >> bit) & 1u;
            if (chiffre != 0u) {
                bit_debut = 0;
            }
            if (!bit_debut || bit == 0) {
                printf("%u", chiffre);
            }
        }
        printf("\n");
    }

    return 0;
}