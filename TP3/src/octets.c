#include <stdio.h>

static void afficher_octets(const char *nom, const void *adresse, size_t taille)
{
    const unsigned char *octets = adresse;
    printf("Octets de %s :\n", nom);
    for (size_t i = 0; i < taille; i++) {
        printf(" %02x", (unsigned int)octets[i]);
    }
    printf("\n\n");
}

int main(void)
{
    short court = 0x203;
    int entier = 0x1020304;
    long int long_entier = 0x102030L;
    float flottant = 1.25f;
    double double_precision = 1.5;
    long double grande_precision = 1.0L;

    afficher_octets("short", &court, sizeof court);
    afficher_octets("int", &entier, sizeof entier);
    afficher_octets("long int", &long_entier, sizeof long_entier);
    afficher_octets("float", &flottant, sizeof flottant);
    afficher_octets("double", &double_precision, sizeof double_precision);
    afficher_octets("long double", &grande_precision, sizeof grande_precision);
    return 0;
}