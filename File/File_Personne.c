
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File/File_Personne.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== File ===============================================================
#include "File_Personne.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

void File_Personne_Ajouter(File_Personne * aPersonnes, Personne * aPersonne)
{
    assert(NULL != aPersonnes);
    assert(NULL != aPersonne );

    if (NULL == aPersonnes->mPremier)
    {
        aPersonnes->mDernier = aPersonne;
        aPersonnes->mPremier = aPersonne;
    }
    else
    {
        assert(NULL != aPersonnes->mDernier);

        aPersonnes->mDernier->mSuivant = aPersonne;
        aPersonnes->mDernier           = aPersonne;
    }
}

void File_Personne_Initialiser(File_Personne * aPersonnes)
{
    assert(NULL != aPersonnes);

    memset(aPersonnes, 0, sizeof(File_Personne));
}

Personne * File_Personne_Retirer(File_Personne * aPersonnes)
{
    Personne * lPersonne;

    assert(NULL != aPersonnes);

    lPersonne = aPersonnes->mPremier;

    if (NULL != lPersonne)
    {
        assert(NULL != aPersonnes->mDernier);

        aPersonnes->mPremier = lPersonne->mSuivant;

        if (NULL == aPersonnes->mPremier)
        {
            aPersonnes->mDernier = NULL;
        }
    }

    return lPersonne;
}
