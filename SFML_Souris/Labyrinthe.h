
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/Labyrinthe.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct Labyrinthe
{
    struct Labyrinthe * mSuivant;

    sf::Texture * mTexture;
}
Labyrinthe;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern Labyrinthe * Labyrinthe_LireFichier(unsigned int aIndice);

extern bool Labyrinthe_Executer(Labyrinthe * aLabyrinthe);
extern void Labyrinthe_Liberer (Labyrinthe * aLabyrinthe);

extern sf::Vector2u Labyrinthe_ObtenirTaille(Labyrinthe * aLabyrinthe);
