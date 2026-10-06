#include <stdio.h>

int main(void)
{
    unsigned int n;
    unsigned long long precedent = 0;
    unsigned long long courant = 1;

    printf("Entrez n (entre 0 et 93) : ");
    if (scanf("%u", &n) != 1 || n > 93u) {
        fprintf(stderr, "n doit être un entier compris entre 0 et 93.\n");
        return 1;
    }

    for (unsigned int i = 0; i <= n; i++) {
        unsigned long long terme;

        if (i == 0u) {
            terme = 0;
        } else if (i == 1u) {
            terme = 1;
        } else {
            terme = precedent + courant;
            precedent = courant;
            courant = terme;
        }

        printf("%s%llu", i == 0u ? "" : ", ", terme);
    }
    printf("\n");
    return 0;
}