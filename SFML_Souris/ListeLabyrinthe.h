
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/Liste_Labyrinthe.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "Labyrinthe.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    Labyrinthe * mDebut;
}
ListeLabyrinthe;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void ListeLabyrinthe_Executer    (ListeLabyrinthe * aListe);
extern void ListeLabyrinthe_Liberer     (ListeLabyrinthe * aListe);
extern void ListeLabyrinthe_LireFichiers(ListeLabyrinthe * aListe);

