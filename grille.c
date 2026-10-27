#include <stdio.h> 
#include "puissance4.h"

// Initialise toutes les cases de la grille à VIDE et remet le compteur de jetons à zéro.
void initialiserGrille(Partie *partie) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            (*partie).grille[i][j] = VIDE;
        }
    }
    (*partie).nombreJetons = 0;
}

// Affiche l'etat actuel du plateau de jeu et les numeros des colonnes dans le terminal.
void afficherGrille(Partie *partie) {
    printf("\n");
    for (int i = 0; i < NB_LIGNES; i++) {
        printf("|");
        for (int j = 0; j < NB_COLONNES; j++) {
            if ((*partie).grille[i][j] == VIDE) {
                printf(" . ");
            } else if ((*partie).grille[i][j] == 1) {
                printf(" X ");
            } else if ((*partie).grille[i][j] == 2) {
                printf(" O ");
            }
        }
        printf("|\n");
    }
    printf("+---------------------+\n");
    printf("  1  2  3  4  5  6  7\n\n");
}

// Verifie si 4 jetons identiques sont alignes horizontalement sur une meme ligne.
int alignementHorizontal(Partie *partie, int jeton) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j <= NB_COLONNES - 4; j++) {
            if ((*partie).grille[i][j] == jeton &&
                (*partie).grille[i][j + 1] == jeton &&
                (*partie).grille[i][j + 2] == jeton &&
                (*partie).grille[i][j + 3] == jeton) {
                return 1;
            }
        }
    }
    return 0;
}
// Verifie si 4 jetons identiques sont alignes verticalement sur une meme colonne.
int alignementVertical(Partie *partie, int jeton) {
    for (int j = 0; j < NB_COLONNES; j++) {
        for (int i = 0; i <= NB_LIGNES - 4; i++) {
            if ((*partie).grille[i][j] == jeton &&
                (*partie).grille[i + 1][j] == jeton &&
                (*partie).grille[i + 2][j] == jeton &&
                (*partie).grille[i + 3][j] == jeton) {
                return 1;
            }
        }
    }
    return 0;
}

// Verifie si 4 jetons identiques sont alignes sur une diagonale montante ou descendante.
// Retourne 1 en cas d'alignement gagnant, 0 sinon.
int alignementDiagonal(Partie *partie, int jeton) {

    // Diagonale descendante vers la droite (\)
    for (int i = 0; i <= NB_LIGNES - 4; i++) {
        for (int j = 0; j <= NB_COLONNES - 4; j++) {
            if ((*partie).grille[i][j] == jeton &&
                (*partie).grille[i + 1][j + 1] == jeton &&
                (*partie).grille[i + 2][j + 2] == jeton &&
                (*partie).grille[i + 3][j + 3] == jeton) {
                return 1;
            }
        }
    }

    // Diagonale montante vers la droite (/)
    for (int i = 3; i < NB_LIGNES; i++) {
        for (int j = 0; j <= NB_COLONNES - 4; j++) {
            if ((*partie).grille[i][j] == jeton &&
                (*partie).grille[i - 1][j + 1] == jeton &&
                (*partie).grille[i - 2][j + 2] == jeton &&
                (*partie).grille[i - 3][j + 3] == jeton) {
                return 1;
            }
        }
    }
    return 0;
}


// Verifie si la grille est totalement remplie de jetons.
// Retourne 1 si la grille est pleine, 0 sinon.
int grillePleine(Partie *partie){
            if ((*partie).nombreJetons== NB_COLONNES * NB_LIGNES ){
                return 1;
            }else{
                return 0;    
            }
    }