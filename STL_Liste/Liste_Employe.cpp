
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  STL_Liste/Liste_Employe.cpp

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

    for (Liste_Employe::iterator lIt = aListe->begin(); lIt != aListe->end(); lIt++)
    {
        if (0 < strcmp(lIt->mNom, aEmploye->mNom))
        {
            aListe->insert(lIt, *aEmploye);
            return;
        }
    }

    aListe->push_back(*aEmploye);
}

void Liste_Employe_LireFichier(Liste_Employe * aListe, const char * aNomFichier)
{
    FILE * lFichier;

    assert(NULL != aListe     );
    assert(NULL != aNomFichier);

    if (0 == fopen_s(&lFichier, aNomFichier, "r"))
    {
        Employe lEmploye;

        while (Employe_Lire(lFichier, &lEmploye))
        {
            Liste_Employe_Ajouter(aListe, &lEmploye);
        }

        fclose(lFichier);
    }
}

Employe * Liste_Employe_Rechercher_Nom(Liste_Employe * aListe, const char * aNom)
{
    assert(NULL != aListe);
    assert(NULL != aNom  );

    for (Liste_Employe::iterator lIt = aListe->begin(); lIt != aListe->end(); lIt++)
    {
        int lResultat = strcmp(lIt->mNom, aNom);

        if (0 == lResultat)
        {
            return &(*lIt);
        }

        if (0 < lResultat)
        {
            break;
        }
    }

    return NULL;
}
