
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  STL_File/Personne.c

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

    assert(!aPersonne->mPrenom.empty());

    // NOTE  Pour afficher un std::string avec printf il faut utilier un %s
    //       et il faut aussi usiliser la methode c_str pour obtenir
    //       l'adresse de la chaine de caractere en format C qui est gardee
    //       a l'interieure de l'instance de std::string.
    printf("%s\n", aPersonne->mPrenom.c_str());
}
