
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File2/File_Personne.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== File ===============================================================
#include "File_Personne.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

Personne * File_Personne_Ajouter(File_Personne * aPersonnes)
{
    Personne   * lPersonne;
    unsigned int lProchain = (aPersonnes->mProchain + 1) % (sizeof(aPersonnes->mTableau) / sizeof(aPersonnes->mTableau[0]));

    assert(NULL != aPersonnes);

    if (aPersonnes->mPremier == lProchain)
    {
        // QUESTION #1 : Combien y a-t-il de personne dans la fille a ce
        //               moment precis ?
        lPersonne = NULL;
    }
    else
    {
        lPersonne = aPersonnes->mTableau + aPersonnes->mProchain;
        aPersonnes->mProchain = lProchain;

        // QUESTION #2 : Que contient la structure pointe par lPersonne a ce
        //               moment precis ?

        Personne_Initialiser(lPersonne);
    }

    return lPersonne;
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

    if (aPersonnes->mPremier == aPersonnes->mProchain)
    {
        lPersonne = NULL;
    }
    else
    {
        lPersonne = aPersonnes->mTableau + aPersonnes->mPremier;
        aPersonnes->mPremier = (aPersonnes->mPremier + 1) % (sizeof(aPersonnes->mTableau) / sizeof(aPersonnes->mTableau[0]));

        // QUESTION #3 : Cette fonctions retourne l'adresse d'une case du
        //               tableau. Est-ce que les donnees dans cette case du
        //               tableau resterons les meme pour toujours ?
    }

    return lPersonne;
}
