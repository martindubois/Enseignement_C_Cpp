
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  STL_File/Personne.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C++ ================================================================
#include <string>

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct Personne
{
    // NOTE  En utilisant un std::string, il n'y a plus de limitation de
    //       longeur pour le prenom.
    std::string mPrenom;
}
Personne;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void Personne_Afficher(const Personne * aPersonne);
