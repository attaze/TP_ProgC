#ifndef LISTE_H
#define LISTE_H

#include <stdint.h>

struct couleur {
    uint8_t rouge;
    uint8_t vert;
    uint8_t bleu;
    uint8_t alpha;
};

struct noeud_couleur;

struct liste_couleurs {
    struct noeud_couleur *tete;
};

void init_liste(struct liste_couleurs *liste);
int insertion(const struct couleur *couleur, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);
void liberer_liste(struct liste_couleurs *liste);

#endif