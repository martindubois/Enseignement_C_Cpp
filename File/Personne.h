
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File/Personne.h

#pragma once

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct Personne
{
    struct Personne * mSuivant;

    char mPrenom[32];
}
Personne;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void       Personne_Afficher(const Personne * aPersonne);
extern Personne * Personne_Allouer ();
extern void       Personne_Liberer (      Personne * aPersonne);
