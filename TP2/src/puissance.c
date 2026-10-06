#include <stdio.h>

int main(void)
{
    const int a = 2;
    const unsigned int b = 3;
    int resultat = 1;

    for (unsigned int i = 0; i < b; i++) {
        resultat *= a;
    }

    printf("%d puissance %u = %d\n", a, b, resultat);
    return 0;
}