#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



static int dernier_id = 0;

int generer_id() {
    return ++dernier_id;
}

void afficher_produits(Produit produits[], int nb_produits) {
    printf("\n=== Liste des produits (%d) ===\n", nb_produits);
    
    if (nb_produits == 0) {
        printf("Aucun produit enregistre.\n");
        return;
    }
    
    printf("ID   | %-30s | Quantite\n", "Nom du produit");
    printf("-----|--------------------------------|----------\n");
    for (int i = 0; i < nb_produits; i++) {
        printf("%-4d | %-30s | %-9d\n", 
              produits[i].id, produits[i].nom, produits[i].quantite);
    }
}

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ajouter_produit(Produit produits[], int *nb_produits) {
    if (*nb_produits >= MAX_PRODUITS) {
        printf("Capacite maximale atteinte (%d produits).\n", MAX_PRODUITS);
        return;
    }
    
    Produit *p = &produits[*nb_produits];
    p->id = generer_id();
    
    printf("\n=== Ajout d'un nouveau produit (ID: %d) ===\n", p->id);
    
    printf("Nom du produit : ");
    fgets(p->nom, TAILLE_NOM, stdin);
    p->nom[strcspn(p->nom, "\n")] = '\0';
    
    if (p->nom[0] != '\0') {
        p->nom[0] = toupper(p->nom[0]);
        for (int i = 1; p->nom[i] != '\0'; i++) {
            p->nom[i] = tolower(p->nom[i]);
        }
    }
    
    printf("Quantite : ");
    while(scanf("%d", &p->quantite) != 1 || p->quantite < 0) {
        printf("Veuillez entrer une quantite valide (>= 0) : ");
        vider_buffer();
    }
    vider_buffer();
    
    (*nb_produits)++;
    printf("Produit ajoute avec succes!\n");
}

int selectionner_produit(Produit produits[], int nb_produits, const char *action) {
    afficher_produits(produits, nb_produits);
    
    if (nb_produits == 0) {
        printf("Aucun produit à %s.\n", action);
        return -1;
    }

    int choix;
    printf("\nSelectionnez le produit à %s (0 pour annuler) : ", 
          action);
    while(scanf("%d", &choix) != 1 || choix < 0 || choix > nb_produits) {
        printf("Selection invalide. Veuillez entrer un nombre entre 0 et %d : ", 
              nb_produits);
        vider_buffer();
    }
    vider_buffer();
    
    return (choix == 0) ? -1 : choix - 1;
}

void modifier_produit(Produit produits[], int nb_produits) {
    printf("\n=== Modification de produit ===\n");
    
    int index = selectionner_produit(produits, nb_produits, "modifier");
    if (index == -1) return;
    
    Produit *p = &produits[index];
    
    printf("\nModification du produit ID %d\n", p->id);
    printf("Nouveau nom [%s] : ", p->nom);
    char nouveau_nom[TAILLE_NOM];
    fgets(nouveau_nom, TAILLE_NOM, stdin);
    if (nouveau_nom[0] != '\n') {
        nouveau_nom[strcspn(nouveau_nom, "\n")] = '\0';
        
        if (nouveau_nom[0] != '\0') {
            nouveau_nom[0] = toupper(nouveau_nom[0]);
            for (int i = 1; nouveau_nom[i] != '\0'; i++) {
                nouveau_nom[i] = tolower(nouveau_nom[i]);
            }
        }
        
        strcpy(p->nom, nouveau_nom);
    }
    
    printf("Nouvelle quantite [%d] : ", p->quantite);
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (input[0] != '\n') {
        int nouvelle_quantite = atoi(input);
        if (nouvelle_quantite >= 0) {
            p->quantite = nouvelle_quantite;
        }
    }
    
    printf("Produit modifie avec succes!\n");
}

void supprimer_produit(Produit produits[], int *nb_produits) {
    printf("\n=== Suppression de produit ===\n");
    
    int index = selectionner_produit(produits, *nb_produits, "supprimer");
    if (index == -1) return;
    
    printf("\nSuppression du produit ID %d - %s\n", 
          produits[index].id, produits[index].nom);
    
    for (int i = index; i < *nb_produits - 1; i++) {
        produits[i] = produits[i + 1];
    }
    (*nb_produits)--;
    
    printf("Produit supprime avec succes!\n");
}

void rechercher_produit(Produit produits[], int nb_produits) {
    if (nb_produits == 0) {
        printf("Aucun produit enregistre.\n");
        return;
    }

    printf("\n=== Recherche de produit ===\n");
    printf("1. Par ID\n");
    printf("2. Par nom\n");
    printf("0. Annuler\n");
    printf("Choix : ");
    
    int choix;
    while(scanf("%d", &choix) != 1 || choix < 0 || choix > 2) {
        printf("Choix invalide (0-2) : ");
        vider_buffer();
    }
    vider_buffer();
    
    if (choix == 0) return;
    
    int trouve = 0;
    system("cls");
    
    if (choix == 1) {
        printf("ID du produit a rechercher : ");
        int id;
        while(scanf("%d", &id) != 1) {
            printf("ID invalide. Veuillez entrer un nombre : ");
            vider_buffer();
        }
        vider_buffer();
        
        printf("\nResultats pour l'ID %d :\n", id);
        for (int i = 0; i < nb_produits; i++) {
            if (produits[i].id == id) {
                printf("-> ID: %d | Nom: %s | Quantite: %d\n", 
                      produits[i].id, produits[i].nom, produits[i].quantite);
                trouve = 1;
                break;
            }
        }
    } 
    else if (choix == 2) {
        printf("Nom (ou partie du nom) a rechercher : ");
        char terme[TAILLE_NOM];
        fgets(terme, TAILLE_NOM, stdin);
        terme[strcspn(terme, "\n")] = '\0';
        
        if (terme[0] != '\0') {
            terme[0] = toupper(terme[0]);
            for (int i = 1; terme[i] != '\0'; i++) {
                terme[i] = tolower(terme[i]);
            }
        }
        
        printf("\nResultats pour \"%s\" :\n", terme);
        for (int i = 0; i < nb_produits; i++) {
            if (strstr(produits[i].nom, terme) != NULL) {
                printf("-> ID: %d | Nom: %s | Quantite: %d\n", 
                      produits[i].id, produits[i].nom, produits[i].quantite);
                trouve = 1;
            }
        }
    }
    
    if (!trouve) {
        printf("Aucun produit trouve.\n");
    }
}

void sauvegarder_produits(Produit produits[], int nb_produits) {
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible de créer le fichier de sauvegarde.\n");
        return;
    }

    for (int i = 0; i < nb_produits; i++) {
        fprintf(fichier, "%d;%s;%d\n", 
               produits[i].id, produits[i].nom, produits[i].quantite);
    }

    fclose(fichier);
    printf("%d produits sauvegardes dans %s\n", nb_produits, FICHIER_SAUVEGARDE);
}

int charger_produits(Produit produits[]) {
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "r");
    if (fichier == NULL) {
        return 0;
    }

    int nb_produits = 0;
    char ligne[TAILLE_LIGNE];
    int max_id = 0;
    
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && nb_produits < MAX_PRODUITS) {
        char *token = strtok(ligne, ";");
        if (token == NULL) continue;
        
        int current_id = atoi(token);
        produits[nb_produits].id = current_id;
        
        
        if (current_id > max_id) {
            max_id = current_id;
        }
        
        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strcpy(produits[nb_produits].nom, token);
        
        token = strtok(NULL, "\n");
        if (token == NULL) continue;
        produits[nb_produits].quantite = atoi(token);
        
        nb_produits++;
    }

    fclose(fichier);
    
    
    extern int dernier_id;
    dernier_id = max_id;
    
    return nb_produits;
}

void afficher_menu() {
    printf("\n=== GESTION DE STOCK ===\n");
    printf("1. Afficher tous les produits\n");
    printf("2. Ajouter un produit\n");
    printf("3. Modifier un produit\n");
    printf("4. Supprimer un produit\n");
    printf("5. Rechercher un produit\n");
    printf("0. Quitter\n");
    printf("Choix : ");
}
