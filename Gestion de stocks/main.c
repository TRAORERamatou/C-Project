#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"
#include "Fonction.h"
#include "Fonction.c"




int main() {
    Produit produits[MAX_PRODUITS];
    int nb_produits = charger_produits(produits);
    int choix;

    do {
        afficher_menu();
        
        while(scanf("%d", &choix) != 1) {
            printf("Choix invalide. Veuillez entrer un nombre : ");
            vider_buffer();
        }
        vider_buffer();
        system("cls");
        
        switch (choix) {
            case 1:
                afficher_produits(produits, nb_produits);
                break;
            case 2:
                ajouter_produit(produits, &nb_produits);
                break;
            case 3:
                modifier_produit(produits, nb_produits);
                break;
            case 4:
                supprimer_produit(produits, &nb_produits);
                break;
            case 5:
                rechercher_produit(produits, nb_produits);
                break;
            case 0:
                if (nb_produits > 0) {
                    printf("\nVoulez-vous sauvegarder avant de quitter ? (1=Oui/0=Non) : ");
                    int reponse;
                    while(scanf("%d", &reponse) != 1 || (reponse != 0 && reponse != 1)) {
                        printf("Réponse invalide (0=Non/1=Oui) : ");
                        vider_buffer();
                    }
                    if (reponse == 1) {
                        sauvegarder_produits(produits, nb_produits);
                    }
                }
                printf("\nAu revoir!\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir entre 0 et 5.\n");
        }
        
        if (choix != 0) {
            printf("\nAppuyez sur Entree pour continuer...");
            getchar();
            system("cls");
        }
    } while (choix != 0);

    return 0;
}


