#include <stdio.h>

int main() {
    // i. char
    signed char var_s_char = 'A';
    unsigned char var_u_char = 250;
    printf("signed char : %c\n", var_s_char);
    printf("unsigned char : %u\n", var_u_char);

    // ii. short
    signed short var_s_short = -15000;
    unsigned short var_u_short = 50000;
    printf("signed short : %d\n", var_s_short);
    printf("unsigned short : %u\n", var_u_short);

    // iii. int
    signed int var_s_int = -2000000000;
    unsigned int var_u_int = 4000000000;
    printf("signed int : %d\n", var_s_int);
    printf("unsigned int : %u\n", var_u_int);

    // iv. long int
    signed long int var_s_long = -2000000000;
    unsigned long int var_u_long = 4000000000;
    printf("signed long int : %ld\n", var_s_long);
    printf("unsigned long int : %lu\n", var_u_long);

    // v. long long int
    signed long long int var_s_llong = -9000000000000000000LL;
    unsigned long long int var_u_llong = 18000000000000000000ULL;
    printf("signed long long int : %lld\n", var_s_llong);
    printf("unsigned long long int : %llu\n", var_u_llong);

    // vi. float
    float var_float = 3.14159f;
    printf("float : %f\n", var_float);

    // vii. double
    double var_double = 2.718281828459;
    printf("double : %lf\n", var_double);

    // viii. long double
    long double var_ldouble = 1.618033988749894L;
    printf("long double : %Lf\n", var_ldouble);

    return 0;
}