#include "operator.h"

int somme(int num1, int num2)
{
    return num1 + num2;
}

int difference(int num1, int num2)
{
    return num1 - num2;
}

int produit(int num1, int num2)
{
    return num1 * num2;
}

int quotient(int num1, int num2)
{
    return num1 / num2;
}

int modulo(int num1, int num2)
{
    return num1 % num2;
}

int et_binaire(int num1, int num2)
{
    return num1 & num2;
}

int ou_binaire(int num1, int num2)
{
    return num1 | num2;
}

int negation(int num1)
{
    return ~num1;
}

int appliquer_operation(int num1, int num2, char operateur, int *resultat)
{
    if (resultat == 0) {
        return 0;
    }

    switch (operateur) {
    case '+':
        *resultat = somme(num1, num2);
        return 1;
    case '-':
        *resultat = difference(num1, num2);
        return 1;
    case '*':
        *resultat = produit(num1, num2);
        return 1;
    case '/':
        if (num2 == 0) {
            return 0;
        }
        *resultat = quotient(num1, num2);
        return 1;
    case '%':
        if (num2 == 0) {
            return 0;
        }
        *resultat = modulo(num1, num2);
        return 1;
    case '&':
        *resultat = et_binaire(num1, num2);
        return 1;
    case '|':
        *resultat = ou_binaire(num1, num2);
        return 1;
    case '~':
        *resultat = negation(num1);
        return 1;
    default:
        return 0;
    }
}