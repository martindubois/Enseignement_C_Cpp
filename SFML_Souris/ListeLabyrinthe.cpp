
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/Liste_Labyrinthe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== SFML_Souris ========================================================
#include "ListeLabyrinthe.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

void ListeLabyrinthe_Executer(ListeLabyrinthe * aListe)
{
    Labyrinthe * lCourant;
    
    assert(NULL != aListe);

    lCourant = aListe->mDebut;

    while (NULL != lCourant)
    {
        if (!Labyrinthe_Executer(lCourant))
        {
            break;
        }

        lCourant = lCourant->mSuivant;
    }
}

void ListeLabyrinthe_Liberer(ListeLabyrinthe * aListe)
{
    Labyrinthe * lCourant;
    
    assert(NULL != aListe);

    lCourant = aListe->mDebut;

    while (NULL != lCourant)
    {
        Labyrinthe * lSuivant = lCourant->mSuivant;

        Labyrinthe_Liberer(lCourant);

        if (aListe->mDebut == lSuivant)
        {
            lCourant = NULL;
        }
        else
        {
            lCourant = lSuivant;
        }
    }
}

void ListeLabyrinthe_LireFichiers(ListeLabyrinthe * aListe)
{
    Labyrinthe * lCourant   ;
    unsigned int lIndice = 0;
    Labyrinthe * lPrecedant = NULL;

    assert(NULL != aListe);

    while (NULL != (lCourant = Labyrinthe_LireFichier(lIndice)))
    {
        assert(NULL == lCourant->mSuivant);

        if (NULL == lPrecedant)
        {
            aListe->mDebut = lCourant;
        }
        else
        {
            lPrecedant->mSuivant = lCourant;
        }

        lIndice++;
        lPrecedant = lCourant;
    }

    lPrecedant->mSuivant = aListe->mDebut;
}
