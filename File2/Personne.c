
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File2/Personne.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ===== File ===============================================================
#include "Personne.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

// QUESTION #1 : Pourquoi l'argument aPersonne est-il declare const ici alors
//               que ce n'est pas le cas pour les deux autres fonctions ?
void Personne_Afficher(const Personne * aPersonne)
{
    assert(NULL != aPersonne);

    printf("%s\n", aPersonne->mPrenom);
}

void Personne_Initialiser(Personne * aPersonne)
{
    assert(NULL != aPersonne);

    // QUESTION #2 : Quel est l'avantage d'utiliser un memset pour
    //               l'initialisation de la structure plutot que
    //               d'initialiser chacun des membre de la structure
    //               separement ?

    memset(aPersonne, 0, sizeof(Personne));
}

void Personne_SetPrenom(Personne * aPersonne, const char * aPrenom)
{
    assert(NULL != aPersonne);
    assert(NULL != aPrenom  );

    strcpy_s(aPersonne->mPrenom, sizeof(aPersonne->mPrenom), aPrenom, sizeof(aPersonne->mPrenom) - 1);
}
