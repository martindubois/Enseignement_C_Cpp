
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  STL_Liste/Employe.h

#pragma once

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    unsigned int mAnnee;
    unsigned int mMois ;
    unsigned int mJour ;
}
Employe_Date;

typedef struct Employe
{
    char mNom   [32];
    char mPrenom[32];

    Employe_Date mNaissance;
    Employe_Date mDebut    ;

    char mPoste[64];
}
Employe;

// Fonction
/////////////////////////////////////////////////////////////////////////////

extern bool Employe_Lire(FILE * aFichier, Employe * aEmploye);

extern void Employe_Afficher(const Employe * aEmploye);
