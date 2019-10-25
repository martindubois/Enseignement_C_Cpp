
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File2/Personne.h

#pragma once

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct Personne
{
    char mPrenom[32];
}
Personne;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void Personne_Afficher   (const Personne * aPersonne);
extern void Personne_Initialiser(      Personne * aPersonne);
extern void Personne_SetPrenom  (      Personne * aPersonne, const char * aPrenom);
