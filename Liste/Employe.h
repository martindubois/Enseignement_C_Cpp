
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  Liste/Employe.h

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
    struct Employe * mSuivant;

    char mNom   [32];
    char mPrenom[32];

    Employe_Date mNaissance;
    Employe_Date mDebut    ;

    char mPoste[64];
}
Employe;

// Fonction
/////////////////////////////////////////////////////////////////////////////

extern Employe * Employe_Allouer();
extern Employe * Employe_Lire   (FILE * aFichier);

extern void Employe_Afficher(const Employe * aEmploye);
extern void Employe_Liberer (      Employe * aEmploye);
