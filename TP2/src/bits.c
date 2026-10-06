#include <limits.h>
#include <stdio.h>

int main(void)
{
    const unsigned int largeur = (unsigned int)(sizeof(unsigned int) * CHAR_BIT);
    unsigned int d;
    unsigned int bit_4;
    unsigned int bit_20;

    if (largeur < 20u) {
        fprintf(stderr, "unsigned int doit contenir au moins 20 bits.\n");
        return 1;
    }

    d = (1u << (largeur - 4u)) | (1u << (largeur - 20u));
    bit_4 = (d >> (largeur - 4u)) & 1u;
    bit_20 = (d >> (largeur - 20u)) & 1u;

    printf("%u\n", bit_4 == 1u && bit_20 == 1u ? 1u : 0u);
    return 0;
}