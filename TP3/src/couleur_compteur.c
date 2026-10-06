#include <stdint.h>
#include <stdio.h>

#define TAILLE 100
#define PALETTE 10

struct couleur {
    uint8_t rouge;
    uint8_t vert;
    uint8_t bleu;
    uint8_t alpha;
};

struct couleur_comptee {
    struct couleur couleur;
    unsigned int occurrences;
};

static int memes_couleurs(struct couleur gauche, struct couleur droite)
{
    return gauche.rouge == droite.rouge
        && gauche.vert == droite.vert
        && gauche.bleu == droite.bleu
        && gauche.alpha == droite.alpha;
}

int main(void)
{
    const struct couleur palette[PALETTE] = {
        {0xff, 0x23, 0x23, 0x45}, {0xff, 0x00, 0x23, 0x12},
        {0x10, 0x20, 0x30, 0xff}, {0x40, 0x50, 0x60, 0xff},
        {0x70, 0x80, 0x90, 0xff}, {0xa0, 0xb0, 0xc0, 0xff},
        {0x01, 0x02, 0x03, 0xff}, {0x11, 0x22, 0x33, 0xff},
        {0x44, 0x55, 0x66, 0xff}, {0x77, 0x88, 0x99, 0xff}
    };
    struct couleur couleurs[TAILLE];
    struct couleur_comptee distinctes[TAILLE];
    unsigned int nombre_distinctes = 0;

    for (int i = 0; i < TAILLE; i++) {
        couleurs[i] = palette[i % PALETTE];
    }

    for (int i = 0; i < TAILLE; i++) {
        unsigned int j;
        for (j = 0; j < nombre_distinctes; j++) {
            if (memes_couleurs(couleurs[i], distinctes[j].couleur)) {
                distinctes[j].occurrences++;
                break;
            }
        }
        if (j == nombre_distinctes) {
            distinctes[j].couleur = couleurs[i];
            distinctes[j].occurrences = 1;
            nombre_distinctes++;
        }
    }

    for (unsigned int i = 0; i < nombre_distinctes; i++) {
        const struct couleur c = distinctes[i].couleur;
        printf("%02x %02x %02x %02x : %u\n",
               (unsigned int)c.rouge, (unsigned int)c.vert,
               (unsigned int)c.bleu, (unsigned int)c.alpha,
               distinctes[i].occurrences);
    }
    return 0;
}