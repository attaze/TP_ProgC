#include <stdio.h>
#include <stdbool.h> // Nécessaire pour utiliser le type bool 

int main() {
    int a = 16;
    int b = 3;

    // 1. Addition
    printf("Addition (a + b) : %d\n", a + b);

    // 2. Soustraction
    printf("Soustraction (a - b) : %d\n", a - b);

    // 3. Multiplication
    printf("Multiplication (a * b) : %d\n", a * b);

    // 4. Division (division entière car a et b sont des int)
    printf("Division (a / b) : %d\n", a / b);

    // 5. Modulo (reste de la division)
    // On utilise %% dans printf pour afficher le symbole %
    printf("Modulo (a %% b) : %d\n", a % b);

    // 6. Égalité (Affichage sous forme de booléen : 1 = Vrai, 0 = Faux)
    bool estEgal = (a == b);
    printf("a est égal à b : %d\n", estEgal);

    // 7. Supériorité (Affichage sous forme de booléen)
    bool estSuperieur = (a > b);
    printf("a est supérieur à b : %d\n", estSuperieur);

    return 0;
}