
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  SFML_Canon/Jeu.h

#pragma once

// Constants
/////////////////////////////////////////////////////////////////////////////

#define NOMBRE_DE_JOUEUR  (2)
#define NOMBRE_DE_POUDRE  (4)

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef enum
{
    ETAT_EN_VOL,
    ETAT_GAGNE ,
    ETAT_JOUER ,
}
Jeu_Etat;

typedef struct
{
    sf::Sprite        mCanon_Sprites[NOMBRE_DE_JOUEUR];
    sf::Texture       mCanon_Texture;
    Jeu_Etat          mEtat         ;
    sf::Image         mFond_Image   ;
    sf::Sprite        mFond_Sprite  ;
    sf::Vector2u      mFond_Taille  ;
    sf::Texture       mFond_Texture ;
    sf::Font          mFont         ;
    unsigned int      mJoueur       ;
    sf::Text          mMessage      ;
    unsigned int      mPoudre       ;
    sf::Sprite        mPoudre_Sprite;
    sf::Texture       mPoudre_Textures[NOMBRE_DE_POUDRE];
    sf::CircleShape   mProjectil    ;
    double            mProjectil_VitesseX_pix_f;
    double            mProjectil_VitesseY_pix_f;
}
Jeu;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void Jeu_Afficher(Jeu * aJeu, sf::RenderWindow * aWindow);

extern void Jeu_Avancer(Jeu * aJeu);

extern unsigned int Jeu_GetHauteur(Jeu * aJeu);
extern unsigned int Jeu_GetLargeur(Jeu * aJeu);

extern void Jeu_Initialiser(Jeu * aJeu);

extern void Jeu_TraiterTouche(Jeu * aJeu, sf::Keyboard::Key aCode);
