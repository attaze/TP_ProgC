#include <stdio.h>

#define NOMBRE_PHRASES 10
#define TAILLE_PHRASE 128

static int memes_chaine(const char *gauche, const char *droite)
{
    unsigned int i = 0;
    while (gauche[i] != '\0' && droite[i] != '\0') {
        if (gauche[i] != droite[i]) {
            return 0;
        }
        i++;
    }
    return gauche[i] == '\0' && droite[i] == '\0';
}

int main(void)
{
    const char *phrases[NOMBRE_PHRASES] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };
    char recherche[TAILLE_PHRASE];
    int trouve = 0;

    printf("Entrez la phrase à rechercher : ");
    if (fgets(recherche, sizeof recherche, stdin) == NULL) {
        fprintf(stderr, "Impossible de lire la phrase.\n");
        return 1;
    }

    unsigned int fin = 0;
    while (recherche[fin] != '\0' && recherche[fin] != '\n') {
        fin++;
    }
    recherche[fin] = '\0';

    for (int i = 0; i < NOMBRE_PHRASES; i++) {
        if (memes_chaine(recherche, phrases[i])) {
            trouve = 1;
            break;
        }
    }

    printf("Phrase %s\n", trouve ? "trouvée" : "non trouvée");
    return 0;
}
