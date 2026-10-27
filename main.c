#include <stdio.h> 
#include "puissance4.h"



int main(){
    // Choix de rejouabilite
    char re='O' ;

    // Initialise les score a 0
    int scorej1=0;
    int scorej2=0;


    afficherRegles();

    // Declarer les tab that store the names of players
    // already set to 30 - 29 and the '/0'
    char nom1[TAILLE_NOM];
    char nom2[TAILLE_NOM];

    printf("Saisir le nom du joueur 1 : \n");
    scanf("%29s", nom1);

    printf("Saisir le nom du joueur 2 : \n");
    scanf("%29s", nom2);

    do{
    // Creation et initialisation d'une nouvelle partie allouee dynamiquement en memoire.
    Partie *partie = creerPartie(nom1,nom2);

    //plays.
    jouerPartie(partie);
    //stops playinig when someone wins or draw

    // hits winner score only when a player wins
    if ((*partie).joueurs[(*partie).joueurCourant].jeton ==  1 && joueurAGagne(partie)==1 ){ 
        scorej1++ ;
    }else if((*partie).joueurs[(*partie).joueurCourant].jeton ==  2 && joueurAGagne(partie)==1 ){
        scorej2++ ;
    }

    printf("--------- SCORE --------- \n" );
    printf("%s : %d     %s : %d\n",(*partie).joueurs[0].nom , scorej1 , (*partie).joueurs[1].nom , scorej2);
    printf("------------------------- \n"); 

    // libere memoire et puts back pointeur partie to NULL
    detruirePartie(partie);
    partie = NULL ;

    // Treats la rejouabilite
    printf("Voulez vous recommencer une autre partie ? \n O: oui   N: non \n");
    scanf(" %c", &re);

    }while(re == 'O' || re == 'o');
    
    return 0;
}