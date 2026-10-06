#include <stdio.h>

int main(void)
{
    const char *noms[5] = {"Dupont", "Martin", "Bernard", "Petit", "Robert"};
    const char *prenoms[5] = {"Marie", "Pierre", "Sophie", "Lucas", "Emma"};
    const char *adresses[5] = {
        "20 boulevard Niels Bohr, Lyon",
        "22 boulevard Niels Bohr, Lyon",
        "5 rue de la Paix, Paris",
        "10 avenue Victor Hugo, Lille",
        "8 rue Centrale, Nantes"
    };
    const float programmation[5] = {16.5f, 14.0f, 18.0f, 12.5f, 15.0f};
    const float systeme[5] = {12.1f, 14.1f, 15.5f, 13.0f, 17.0f};

    for (int i = 0; i < 5; i++) {
        printf("Étudiant.e %d : %s %s\n", i + 1, prenoms[i], noms[i]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Programmation en C : %.1f\n", programmation[i]);
        printf("Système d'exploitation : %.1f\n\n", systeme[i]);
    }
    return 0;
}