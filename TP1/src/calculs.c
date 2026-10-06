
#include <stdio.h>

int main(void)
{
    int num1;
    int num2;
    int resultat;
    char op;

    printf("Entrez num1 : ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Valeur invalide pour num1.\n");
        return 1;
    }

    printf("Entrez num2 : ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Valeur invalide pour num2.\n");
        return 1;
    }

    printf("Entrez l'opérateur (+, -, *, /, %%, &, |, ~) : ");
    if (scanf(" %c", &op) != 1) {
        fprintf(stderr, "Opérateur invalide.\n");
        return 1;
    }

    switch (op) {
    case '+':
        resultat = num1 + num2;
        break;
    case '-':
        resultat = num1 - num2;
        break;
    case '*':
        resultat = num1 * num2;
        break;
    case '/':
        if (num2 == 0) {
            fprintf(stderr, "Division par zéro impossible.\n");
            return 1;
        }
        resultat = num1 / num2;
        break;
    case '%':
        if (num2 == 0) {
            fprintf(stderr, "Modulo par zéro impossible.\n");
            return 1;
        }
        resultat = num1 % num2;
        break;
    case '&':
        resultat = num1 & num2;
        break;
    case '|':
        resultat = num1 | num2;
        break;
    case '~':
        resultat = ~num1;
        break;
    default:
        fprintf(stderr, "Opérateur non pris en charge : %c\n", op);
        return 1;
    }

    printf("Résultat : %d\n", resultat);
    return 0;
}
