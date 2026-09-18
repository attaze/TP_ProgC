#include <stdio.h>

int main() {
    // i. char
    printf("Taille de signed char : %zu octets\n", sizeof(signed char));
    printf("Taille de unsigned char : %zu octets\n", sizeof(unsigned char));

    // ii. short
    printf("Taille de signed short : %zu octets\n", sizeof(signed short));
    printf("Taille de unsigned short : %zu octets\n", sizeof(unsigned short));

    // iii. int
    printf("Taille de signed int : %zu octets\n", sizeof(signed int));
    printf("Taille de unsigned int : %zu octets\n", sizeof(unsigned int));

    // iv. long int
    printf("Taille de signed long int : %zu octets\n", sizeof(signed long int));
    printf("Taille de unsigned long int : %zu octets\n", sizeof(unsigned long int));

    // v. long long int
    printf("Taille de signed long long int : %zu octets\n", sizeof(signed long long int));
    printf("Taille de unsigned long long int : %zu octets\n", sizeof(unsigned long long int));

    // vi. float (Pas de version signed/unsigned)
    printf("Taille de float : %zu octets\n", sizeof(float));

    // vii. double (Pas de version signed/unsigned)
    printf("Taille de double : %zu octets\n", sizeof(double));

    // viii. long double (Pas de version signed/unsigned)
    printf("Taille de long double : %zu octets\n", sizeof(long double));

    return 0;
}