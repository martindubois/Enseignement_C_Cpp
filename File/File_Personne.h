
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File/File_Personne.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== File ===============================================================
#include "Personne.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    Personne * mDernier;
    Personne * mPremier;
}
File_Personne;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void       File_Personne_Ajouter    (File_Personne * aPersonnes, Personne * aPersonne);
extern void       File_Personne_Ajouter_2  (File_Personne * aPersonnes, Personne * aPersonne);
extern void       File_Personne_Initialiser(File_Personne * aPersonnes);
extern Personne * File_Personne_Retirer    (File_Personne * aPersonnes);
