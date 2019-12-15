
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/Souris.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== SFML_Souris ========================================================
#include "Labyrinthe.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    unsigned int mX;
    unsigned int mY;
}
Souris_Position;

typedef struct
{
    Souris_Position * mPile;
    unsigned int      mPile_Hauteur;
}
Souris;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern bool Souris_Avancer    (Souris * aSouris, sf::Image * aImage);
extern void Souris_Initialiser(Souris * aSouris, sf::Image * aImage, Labyrinthe * aLabyrinthe);
extern void Souris_Liberer    (Souris * aSouris);
