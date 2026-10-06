#include "liste.h"

#include <stdio.h>
#include <stdlib.h>

struct noeud_couleur {
    struct couleur couleur;
    struct noeud_couleur *suivant;
};

void init_liste(struct liste_couleurs *liste)
{
    if (liste != NULL) {
        liste->tete = NULL;
    }
}

int insertion(const struct couleur *couleur, struct liste_couleurs *liste)
{
    if (couleur == NULL || liste == NULL) {
        return 0;
    }

    struct noeud_couleur *noeud = malloc(sizeof *noeud);
    if (noeud == NULL) {
        perror("malloc");
        return 0;
    }
    noeud->couleur = *couleur;
    noeud->suivant = liste->tete;
    liste->tete = noeud;
    return 1;
}

void parcours(const struct liste_couleurs *liste)
{
    if (liste == NULL) {
        return;
    }

    for (const struct noeud_couleur *noeud = liste->tete;
         noeud != NULL; noeud = noeud->suivant) {
        printf("R=%u G=%u B=%u A=%u\n",
               (unsigned int)noeud->couleur.rouge,
               (unsigned int)noeud->couleur.vert,
               (unsigned int)noeud->couleur.bleu,
               (unsigned int)noeud->couleur.alpha);
    }
}

void liberer_liste(struct liste_couleurs *liste)
{
    if (liste == NULL) {
        return;
    }

    struct noeud_couleur *noeud = liste->tete;
    while (noeud != NULL) {
        struct noeud_couleur *suivant = noeud->suivant;
        free(noeud);
        noeud = suivant;
    }
    liste->tete = NULL;
}