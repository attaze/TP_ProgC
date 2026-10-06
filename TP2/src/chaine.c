#include <stdio.h>

static unsigned int longueur(const char *chaine)
{
    unsigned int taille = 0;
    while (chaine[taille] != '\0') {
        taille++;
    }
    return taille;
}

static void copier(char *destination, const char *source)
{
    unsigned int i = 0;
    do {
        destination[i] = source[i];
    } while (source[i++] != '\0');
}

static void concatener(char *destination, const char *source)
{
    unsigned int fin = longueur(destination);
    unsigned int i = 0;
    do {
        destination[fin + i] = source[i];
    } while (source[i++] != '\0');
}

int main(void)
{
    const char premiere[] = "Hello";
    const char seconde[] = " World!";
    char copie[sizeof premiere];
    char concatenee[sizeof premiere + sizeof seconde - 1];

    copier(copie, premiere);
    copier(concatenee, premiere);
    concatener(concatenee, seconde);

    printf("Longueur de la première chaîne : %u\n", longueur(premiere));
    printf("Copie : %s\n", copie);
    printf("Concaténation : %s\n", concatenee);
    return 0;
}