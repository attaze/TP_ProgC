#include "operator.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int lire_entier(const char *texte, int *valeur)
{
    char *fin;
    long nombre;

    errno = 0;
    nombre = strtol(texte, &fin, 10);
    if (errno != 0 || fin == texte || *fin != '\0'
        || nombre < (long)INT_MIN || nombre > (long)INT_MAX) {
        return 0;
    }
    *valeur = (int)nombre;
    return 1;
}

int main(int argc, char *argv[])
{
    int num1;
    int num2;
    int resultat;

    if (argc != 4 || argv[1][0] == '\0' || argv[1][1] != '\0'
        || !lire_entier(argv[2], &num1) || !lire_entier(argv[3], &num2)) {
        fprintf(stderr, "Utilisation : %s <opérateur> <num1> <num2>\n", argv[0]);
        return 1;
    }

    if (!appliquer_operation(num1, num2, argv[1][0], &resultat)) {
        fprintf(stderr, "Opération invalide ou division par zéro.\n");
        return 1;
    }
    printf("Résultat : %d\n", resultat);
    return 0;
}