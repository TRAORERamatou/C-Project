#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"
#ifndef FONCTION_H
#define FONCTION_H

#define MAX_PRODUITS 1000
#define FICHIER_SAUVEGARDE "produits.txt"
#define TAILLE_NOM 100
#define TAILLE_LIGNE 100

typedef struct {
    int id;
    int quantite;
    char nom[TAILLE_NOM];
} Produit;


int generer_id();
void afficher_produits(Produit produits[], int nb_produits);
void vider_buffer();
void ajouter_produit(Produit produits[], int *nb_produits);
int selectionner_produit(Produit produits[], int nb_produits, const char *action);
void modifier_produit(Produit produits[], int nb_produits);
void supprimer_produit(Produit produits[], int *nb_produits);
void rechercher_produit(Produit produits[], int nb_produits);
void sauvegarder_produits(Produit produits[], int nb_produits);
int charger_produits(Produit produits[]);
void afficher_menu();

#endif
