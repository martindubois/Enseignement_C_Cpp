
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File/Personne.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

// ===== File ===============================================================
#include "Personne.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

void Personne_Afficher(const Personne * aPersonne)
{
    assert(NULL != aPersonne);

    printf("%s\n", aPersonne->mPrenom);
}

Personne * Personne_Allouer()
{
    Personne * lPersonne = malloc(sizeof(Personne));
    assert(NULL != lPersonne);

    memset(lPersonne, 0, sizeof(Personne));

    return lPersonne;
}

void Personne_Liberer(Personne * aPersonne)
{
    assert(NULL != aPersonne);

    free(aPersonne);
}
