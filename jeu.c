#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "puissance4.h"

void afficherRegles(void){
        printf("=== PUISSANCE 4 === \n");
        printf("Alignez quatre jetons horizontalement, verticalement ou en diagonale.\n");
        printf("Les colonnes sont numerotees de 1 a 7.\n");
}

// Alterne le tour entre les deux joueurs en inversant l'indice joueurCourant. !1 = 0 et !0 =1.
void changerJoueur(Partie *partie){
    (*partie).joueurCourant = !(*partie).joueurCourant ;
}

// Asks en boucle au joueur courant de choisir une colonne valide et non pleine.
// Retourne l'indice reel de la colonne choisie (entre 0 et NB_COLONNES - 1).

int demanderColonne(Partie *partie) {
    char entree ;
    int colonne;
    int playerindex = (*partie).joueurCourant;

    while (1) {
        char poubelle='0' ;
        int extra=0 ;

        printf("%s, choisissez une colonne (1-%d) : \n", (*partie).joueurs[playerindex].nom, NB_COLONNES);
        scanf(" %c", &entree);
        scanf("%c", &poubelle);          // Reads le caractère suivant
        while (poubelle != '\n') {       // Tant qu'on n'est pas à la fin de la ligne
            scanf("%c", &poubelle);
            extra = 1; // Traite le cas du premier charactère valide mais par les suivants (Ex: = 3gh)
        }

        colonne = colonneValide(entree);

        if (extra == 1 || (entree < '0' || entree > '9') ) {
            printf("Entree invalide.\n");
        } else if (colonne == 0 ) {
            printf("Cette colonne n'existe pas.\n");
        } else if (!colonneLibre(partie, colonne - 1)) {
            printf("La colonne choisie est pleine.\n");
        } else {
            return colonne - 1;
        }
    }
}

// Runs 1 tour : Recupere le coup du joueur (qui est par défaut valide par construction des autres fonctions), Insere le jeton et Affiche la grille after the hit.
void jouerTour(Partie *partie) {
    int colonne = demanderColonne(partie);

    placerJeton(partie, colonne);
    afficherGrille(partie);
}

// Verifie si le char saisi est compris entre les char '0', et '9' (entre '1' et NB_COLONNES).
// if ok : Returns le char - '0' -> le convertit en sa vraie valeur numérique.
// See table ASCII
// Return 0 if invalide.
int colonneValide(char entree) {
     if (entree >= '1' && entree <= '0' + NB_COLONNES) {
        return entree - '0';   // bonne colonne entre 1 et 7 
    } else {
        return 0;   // la colonne n'existe pas
    }
}

// Returns 1 si au minimum 1 colonne de la upper ligne peut accepter un jeton <=> is = VIDE
int colonneLibre(Partie *partie, int colonne) {
    return ((*partie).grille[0][colonne] == VIDE);
}

// Checks from the bottom la colonne and places a jeton dès que une case est libre
// Par construction, la colonne verifiee a necessairement une place
// // Incrémente le nbJeton de 1 et Return 1 when jeton est placé
int placerJeton(Partie *partie, int colonne) {
    for (int i = NB_LIGNES - 1; i >= 0; i--) {
        if ((*partie).grille[i][colonne] == VIDE) {
            (*partie).grille[i][colonne] = (*partie).joueurs[(*partie).joueurCourant].jeton;
            (*partie).nombreJetons++;
            return 1;
        }
    }
    return 0;
}

// returns 1 if au moins 1 des 3 win con a retourne 1
// keeps track of the actual player with (*partie).joueurs[(*partie).joueurCourant].jeton
int joueurAGagne(Partie *partie){
    int jeton = (*partie).joueurs[(*partie).joueurCourant].jeton ;
    return alignementHorizontal(partie, jeton) || alignementVertical(partie, jeton) || alignementDiagonal(partie, jeton) ;
}


// Alloue dynamiquement une nouvelle structure Partie.

// Verifie si l'allocation dynamique de memoire a echoue.
// Return NULL si a echoue.

// Initialise les joueurs
// Initialise les jetons ainsi que le plateau.
// Affiche le tableau vide (debut de partie).
// Retourne un pointeur vers la partie creee.
Partie *creerPartie(char nomJoueur1[], char nomJoueur2[]){
    Partie *nouvellepartie = malloc(sizeof(Partie));

    if (nouvellepartie == NULL){
        printf("Erreur d'allocation de memoire.\n");
        return NULL ;
    }

    strcpy((*nouvellepartie).joueurs[0].nom, nomJoueur1);
    strcpy((*nouvellepartie).joueurs[1].nom, nomJoueur2);
    
    (*nouvellepartie).joueurs[0].jeton = 1;
    (*nouvellepartie).joueurs[1].jeton = 2 ;
    (*nouvellepartie).joueurCourant = 0; 

    initialiserGrille(nouvellepartie);
    afficherGrille(nouvellepartie);

    return nouvellepartie ;
}

// Libere la memoire allouee - prevents fuite de memoire.
void detruirePartie(Partie *partie){
    free(partie);
}

// Runs the game
// Breaks if someone wins, but remembers the winner avec (*partie).joueurCourant
// Which after will be used to declarer who won and calculer score
// if none wins, changes player and hits again
void jouerPartie(Partie *partie) {

    while (1) {

        jouerTour(partie);

        if (joueurAGagne(partie)) {
            printf("%s remporte la victoire \n", (*partie).joueurs[(*partie).joueurCourant].nom);
            break;
        }

        if (grillePleine(partie)) {
            printf("Match nul \n");
            break;
        }

        changerJoueur(partie);
    }
}