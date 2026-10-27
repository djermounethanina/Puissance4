#ifndef PUISSANCE4_H 
    #define PUISSANCE4_H 
    #define NB_LIGNES 6 
    #define NB_COLONNES 7 
    #define VIDE 0 
    #define TAILLE_NOM 30 

     
    typedef struct { 
        char nom[TAILLE_NOM]; 
        int jeton;  
    } Joueur;

    
    typedef struct { 
        int grille[NB_LIGNES][NB_COLONNES]; 
        Joueur joueurs[2]; 
        int joueurCourant; 
        int nombreJetons; 
    } Partie;

    void afficherRegles(void);
    int colonneValide(char colonne);
    int demanderColonne(Partie *partie); 
    void changerJoueur(Partie *partie); 
    void jouerTour(Partie *partie);
    void initialiserGrille(Partie *partie); //
    void afficherGrille(Partie *partie); // 
    int colonneLibre(Partie *partie, int colonne); 
    int placerJeton(Partie *partie, int colonne); 
    int alignementHorizontal(Partie *partie, int jeton); 
    int alignementVertical(Partie *partie, int jeton); 
    int alignementDiagonal(Partie *partie, int jeton ); //
    int joueurAGagne(Partie *partie); //
    int grillePleine(Partie *partie); //
    Partie *creerPartie(char nomJoueur1[], char nomJoueur2[]);
    void detruirePartie(Partie *partie); 
    void jouerPartie(Partie *partie);

 
#endif 