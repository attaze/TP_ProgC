#include <stdio.h>

#define AFFICHER_OCTETS(nom, variable) do { \
    const unsigned char *octets_ = (const unsigned char *)&(variable); \
    printf("%s (adresse %p) :", (nom), (void *)&(variable)); \
    for (size_t i_ = 0; i_ < sizeof(variable); i_++) { \
        printf(" %02x", (unsigned int)octets_[i_]); \
    } \
    printf("\n"); \
} while (0)

int main(void)
{
    char caractere = 'A';
    short court = 123;
    int entier = 456;
    long long_entier = 789L;
    long long long_long_entier = 1234LL;
    float reel = 1.5f;
    double double_precision = 2.5;
    long double grande_precision = 3.5L;
    char *p_caractere = &caractere;
    short *p_court = &court;
    int *p_entier = &entier;
    long *p_long = &long_entier;
    long long *p_long_long = &long_long_entier;
    float *p_reel = &reel;
    double *p_double = &double_precision;
    long double *p_long_double = &grande_precision;

    printf("Avant la manipulation :\n");
    AFFICHER_OCTETS("char", caractere);
    AFFICHER_OCTETS("short", court);
    AFFICHER_OCTETS("int", entier);
    AFFICHER_OCTETS("long", long_entier);
    AFFICHER_OCTETS("long long", long_long_entier);
    AFFICHER_OCTETS("float", reel);
    AFFICHER_OCTETS("double", double_precision);
    AFFICHER_OCTETS("long double", grande_precision);

    *p_caractere = 'B';
    *p_court = 124;
    *p_entier = 457;
    *p_long = 790L;
    *p_long_long = 1235LL;
    *p_reel = 2.5f;
    *p_double = 3.5;
    *p_long_double = 4.5L;

    printf("\nAprès la manipulation :\n");
    AFFICHER_OCTETS("char", caractere);
    AFFICHER_OCTETS("short", court);
    AFFICHER_OCTETS("int", entier);
    AFFICHER_OCTETS("long", long_entier);
    AFFICHER_OCTETS("long long", long_long_entier);
    AFFICHER_OCTETS("float", reel);
    AFFICHER_OCTETS("double", double_precision);
    AFFICHER_OCTETS("long double", grande_precision);
    return 0;
}