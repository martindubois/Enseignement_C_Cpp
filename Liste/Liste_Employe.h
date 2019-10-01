
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  Liste/Liste_Employe.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Liste ==============================================================
#include "Employe.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    Employe * mPremier;
}
Liste_Employe;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void      Liste_Employe_Ajouter       (Liste_Employe * aListe, Employe * aEmploye);
extern void      Liste_Employe_Initialiser   (Liste_Employe * aListe);
extern void      Liste_Employe_Liberer       (Liste_Employe * aListe);
extern void      Liste_Employe_LireFichier   (Liste_Employe * aListe, const char * aNomFichier);
extern Employe * Liste_Employe_Rechercher_Nom(Liste_Employe * aListe, const char * aNom);
