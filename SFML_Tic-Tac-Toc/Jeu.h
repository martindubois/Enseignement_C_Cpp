
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  SFML_Tic-Tac-Toc/Jeu.h

#pragma once

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    sf::Text           mCases [3][3];
    unsigned int       mCompteur    ;
    sf::Sprite         mFond_Sprite ;
    sf::Texture        mFond_Texture;
    sf::Font           mFont        ;
    bool               mGagnant     ;
    unsigned int       mJoueur      ;
    sf::RectangleShape mLigne       ;
    sf::Text           mMessage     ;
    bool               mNulle       ;
    sf::CircleShape    mRond        ;
}
Jeu;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void Jeu_Afficher(Jeu * aJeu, sf::RenderWindow * aWindow);

extern void Jeu_Initialiser(Jeu * aJeu);

extern void Jeu_TraiterTouche(Jeu * aJeu, sf::Keyboard::Key aCode);
