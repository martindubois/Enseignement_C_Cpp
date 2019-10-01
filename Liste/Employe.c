
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  Liste/Employe.c

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

Employe * Employe_Allouer()
{
    Employe * lEmploye = malloc(sizeof(Employe));

    assert(NULL != lEmploye);

    memset(lEmploye, 0, sizeof(Employe));

    return lEmploye;
}

Employe * Employe_Lire(FILE * aFichier)
{
    char lLigne[256];

    assert(NULL != aFichier);

    while (NULL != fgets(lLigne, sizeof(lLigne), aFichier))
    {
        Employe * lEmploye = Employe_Allouer();

        if (9 == sscanf_s(lLigne, "%s %s %u-%u-%u %u-%u-%u %[^\n\r\t]",
             lEmploye->mNom   , sizeof(lEmploye->mNom   ),
             lEmploye->mPrenom, sizeof(lEmploye->mPrenom),
            &lEmploye->mNaissance.mAnnee,
            &lEmploye->mNaissance.mMois ,
            &lEmploye->mNaissance.mJour ,
            &lEmploye->mDebut.mAnnee,
            &lEmploye->mDebut.mMois ,
            &lEmploye->mDebut.mJour ,
             lEmploye->mPoste, sizeof(lEmploye->mPoste)))
        {
            return lEmploye;
        }

        Employe_Liberer(lEmploye);
    }

    return NULL;
}

void Employe_Afficher(const Employe * aEmploye)
{
    assert(NULL != aEmploye);

    printf("%s, %s\n", aEmploye->mNom, aEmploye->mPrenom);
    printf("%s\n"    , aEmploye->mPoste);
    printf("Naissance : %04u-%02u-%02u\n", aEmploye->mNaissance.mAnnee, aEmploye->mNaissance.mMois, aEmploye->mNaissance.mJour);
    printf("Debut     : %04u-%02u-%02u\n", aEmploye->mDebut    .mAnnee, aEmploye->mDebut    .mMois, aEmploye->mDebut    .mJour);
}

void Employe_Liberer(Employe * aEmploye)
{
    assert(NULL != aEmploye);

    free(aEmploye);
}
