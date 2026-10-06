#include <stdio.h>
#include <string.h>

struct etudiant {
    char nom[32];
    char prenom[32];
    char adresse[80];
    float programmation;
    float systeme;
};

int main(void)
{
    struct etudiant etudiants[5] = {0};
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
        strcpy(etudiants[i].nom, noms[i]);
        strcpy(etudiants[i].prenom, prenoms[i]);
        strcpy(etudiants[i].adresse, adresses[i]);
        etudiants[i].programmation = programmation[i];
        etudiants[i].systeme = systeme[i];
    }

    for (int i = 0; i < 5; i++) {
        printf("Étudiant.e %d : %s %s\n", i + 1,
               etudiants[i].prenom, etudiants[i].nom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Programmation en C : %.1f\n", etudiants[i].programmation);
        printf("Système d'exploitation : %.1f\n\n", etudiants[i].systeme);
    }
    return 0;
}