
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  Liste/Liste_Employe.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Liste ==============================================================
#include "Liste_Employe.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

void Liste_Employe_Ajouter(Liste_Employe * aListe, Employe * aEmploye)
{
    assert(NULL != aListe  );
    assert(NULL != aEmploye);

    if (NULL == aListe->mPremier)
    {
        aListe->mPremier = aEmploye;
    }
    else if (0 < strcmp(aListe->mPremier->mNom, aEmploye->mNom))
    {
        aEmploye->mSuivant = aListe->mPremier;
        aListe  ->mPremier = aEmploye;
    }
    else
    {
        Employe * lCourant = aListe->mPremier;

        while (NULL != lCourant->mSuivant)
        {
            if (0 < strcmp(lCourant->mSuivant->mNom, aEmploye->mNom))
            {
                break;
            }

            lCourant = lCourant->mSuivant;
        }

        aEmploye->mSuivant = lCourant->mSuivant;
        lCourant->mSuivant = aEmploye;
    }
}

void Liste_Employe_Initialiser(Liste_Employe * aListe)
{
    assert(NULL != aListe);

    memset(aListe, 0, sizeof(Liste_Employe));
}

void Liste_Employe_Liberer(Liste_Employe * aListe)
{
    Employe * lCourant;

    assert(NULL != aListe);

    lCourant = aListe->mPremier;

    aListe->mPremier = NULL;

    while (NULL != lCourant)
    {
        Employe * lSuivant = lCourant->mSuivant;

        Employe_Liberer(lCourant);

        lCourant = lSuivant;
    }
}

void Liste_Employe_LireFichier(Liste_Employe * aListe, const char * aNomFichier)
{
    FILE * lFichier;

    assert(NULL != aListe     );
    assert(NULL != aNomFichier);

    if (0 == fopen_s(&lFichier, aNomFichier, "r"))
    {
        Employe * lEmploye;

        while (NULL != (lEmploye = Employe_Lire(lFichier)))
        {
            Liste_Employe_Ajouter(aListe, lEmploye);
        }

        fclose(lFichier);
    }
}

Employe * Liste_Employe_Rechercher_Nom(Liste_Employe * aListe, const char * aNom)
{
    Employe * lCourant;

    assert(NULL != aListe);
    assert(NULL != aNom  );
    
    lCourant = aListe->mPremier;

    while (NULL != lCourant)
    {
        int lResultat = strcmp(lCourant->mNom, aNom);

        if (0 == lResultat)
        {
            return lCourant;
        }

        if (0 < lResultat)
        {
            break;
        }

        lCourant = lCourant->mSuivant;
    }

    return NULL;
}
