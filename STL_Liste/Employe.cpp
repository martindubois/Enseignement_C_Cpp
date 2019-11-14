
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  STL_Liste/Employe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

// ===== Liste ==============================================================
#include "Employe.h"

// Fonctions
/////////////////////////////////////////////////////////////////////////////

bool Employe_Lire(FILE * aFichier, Employe * aEmploye)
{
    char lLigne[256];

    assert(NULL != aFichier);

    while (NULL != fgets(lLigne, sizeof(lLigne), aFichier))
    {
        if (9 == sscanf_s(lLigne, "%s %s %u-%u-%u %u-%u-%u %[^\n\r\t]",
            aEmploye->mNom   , sizeof(aEmploye->mNom   ),
            aEmploye->mPrenom, sizeof(aEmploye->mPrenom),
            &aEmploye->mNaissance.mAnnee,
            &aEmploye->mNaissance.mMois,
            &aEmploye->mNaissance.mJour,
            &aEmploye->mDebut.mAnnee,
            &aEmploye->mDebut.mMois,
            &aEmploye->mDebut.mJour,
            aEmploye->mPoste, sizeof(aEmploye->mPoste)))
        {
            return true;
        }
    }

    return false;
}

void Employe_Afficher(const Employe * aEmploye)
{
    assert(NULL != aEmploye);

    printf("%s, %s\n", aEmploye->mNom, aEmploye->mPrenom);
    printf("%s\n", aEmploye->mPoste);
    printf("Naissance : %04u-%02u-%02u\n", aEmploye->mNaissance.mAnnee, aEmploye->mNaissance.mMois, aEmploye->mNaissance.mJour);
    printf("Debut     : %04u-%02u-%02u\n", aEmploye->mDebut.mAnnee, aEmploye->mDebut.mMois, aEmploye->mDebut.mJour);
}
