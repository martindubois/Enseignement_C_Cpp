
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File2/File_Personne.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== File ===============================================================
#include "Personne.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    unsigned int mPremier ;
    unsigned int mProchain;

    Personne mTableau[8];
}
File_Personne;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern Personne * File_Personne_Ajouter    (File_Personne * aPersonnes);
extern void       File_Personne_Initialiser(File_Personne * aPersonnes);
extern Personne * File_Personne_Retirer    (File_Personne * aPersonnes);
