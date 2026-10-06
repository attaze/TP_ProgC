#include <stdio.h>

static unsigned long long factorielle(unsigned int nombre)
{
    if (nombre <= 1u) {
        return 1;
    }
    return (unsigned long long)nombre * factorielle(nombre - 1u);
}

int main(void)
{
    unsigned int nombre;

    printf("Entrez un entier entre 0 et 20 : ");
    if (scanf("%u", &nombre) != 1 || nombre > 20u) {
        fprintf(stderr, "La valeur doit être comprise entre 0 et 20.\n");
        return 1;
    }
    printf("%u! = %llu\n", nombre, factorielle(nombre));
    return 0;
}