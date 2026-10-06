#define _POSIX_C_SOURCE 200809L

#include "repertoire.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static char *joindre_chemin(const char *dossier, const char *nom)
{
    size_t longueur_dossier = strlen(dossier);
    size_t longueur_nom = strlen(nom);
    int ajouter_separateur = longueur_dossier > 0
        && dossier[longueur_dossier - 1] != '/';
    char *chemin = malloc(longueur_dossier + (size_t)ajouter_separateur
                          + longueur_nom + 1);

    if (chemin == NULL) {
        perror("malloc");
        return NULL;
    }
    memcpy(chemin, dossier, longueur_dossier);
    if (ajouter_separateur) {
        chemin[longueur_dossier++] = '/';
    }
    memcpy(chemin + longueur_dossier, nom, longueur_nom + 1);
    return chemin;
}

int lire_dossier(const char *nom_repertoire)
{
    DIR *dossier = opendir(nom_repertoire);
    if (dossier == NULL) {
        perror(nom_repertoire);
        return 0;
    }

    struct dirent *entree;
    int succes = 1;
    while ((entree = readdir(dossier)) != NULL) {
        if (strcmp(entree->d_name, ".") != 0
            && strcmp(entree->d_name, "..") != 0) {
            puts(entree->d_name);
        }
    }
    if (closedir(dossier) != 0) {
        perror("closedir");
        succes = 0;
    }
    return succes;
}

static int lire_recursif(const char *chemin)
{
    DIR *dossier = opendir(chemin);
    if (dossier == NULL) {
        perror(chemin);
        return 0;
    }

    struct dirent *entree;
    int succes = 1;
    while ((entree = readdir(dossier)) != NULL) {
        if (strcmp(entree->d_name, ".") == 0
            || strcmp(entree->d_name, "..") == 0) {
            continue;
        }

        char *enfant = joindre_chemin(chemin, entree->d_name);
        if (enfant == NULL) {
            succes = 0;
            break;
        }
        puts(enfant);

        struct stat informations;
        if (lstat(enfant, &informations) != 0) {
            perror(enfant);
            succes = 0;
        } else if (S_ISDIR(informations.st_mode)
                   && !lire_recursif(enfant)) {
            succes = 0;
        }
        free(enfant);
    }
    if (closedir(dossier) != 0) {
        perror("closedir");
        succes = 0;
    }
    return succes;
}

int lire_dossier_recursif(const char *nom_repertoire)
{
    return lire_recursif(nom_repertoire);
}

int lire_dossier_iteratif(const char *nom_repertoire)
{
    size_t capacite = 16;
    size_t debut = 0;
    size_t fin = 0;
    char **dossiers = malloc(capacite * sizeof *dossiers);
    int succes = 1;

    if (dossiers == NULL) {
        perror("malloc");
        return 0;
    }
    dossiers[fin] = strdup(nom_repertoire);
    if (dossiers[fin] == NULL) {
        perror("strdup");
        free(dossiers);
        return 0;
    }
    fin++;

    while (debut < fin) {
        char *chemin = dossiers[debut++];
        DIR *dossier = opendir(chemin);
        if (dossier == NULL) {
            perror(chemin);
            free(chemin);
            succes = 0;
            continue;
        }

        struct dirent *entree;
        while ((entree = readdir(dossier)) != NULL) {
            if (strcmp(entree->d_name, ".") == 0
                || strcmp(entree->d_name, "..") == 0) {
                continue;
            }
            char *enfant = joindre_chemin(chemin, entree->d_name);
            if (enfant == NULL) {
                succes = 0;
                continue;
            }
            puts(enfant);

            struct stat informations;
            if (lstat(enfant, &informations) != 0) {
                perror(enfant);
                succes = 0;
                free(enfant);
            } else if (S_ISDIR(informations.st_mode)) {
                if (fin == capacite) {
                    size_t nouvelle_capacite = capacite * 2;
                    char **nouveaux_dossiers =
                        realloc(dossiers, nouvelle_capacite * sizeof *dossiers);
                    if (nouveaux_dossiers == NULL) {
                        perror("realloc");
                        free(enfant);
                        succes = 0;
                        continue;
                    }
                    dossiers = nouveaux_dossiers;
                    capacite = nouvelle_capacite;
                }
                dossiers[fin++] = enfant;
            } else {
                free(enfant);
            }
        }
        if (closedir(dossier) != 0) {
            perror("closedir");
            succes = 0;
        }
        free(chemin);
    }

    free(dossiers);
    return succes;
}