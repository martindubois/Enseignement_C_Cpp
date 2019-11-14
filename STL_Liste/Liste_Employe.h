
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  STL_Liste/Liste_Employe.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C++ ================================================================
#include <list>

// ===== Liste ==============================================================
#include "Employe.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef std::list<Employe> Liste_Employe;

// Fonctions
/////////////////////////////////////////////////////////////////////////////

extern void      Liste_Employe_LireFichier   (Liste_Employe * aListe, const char * aNomFichier);
extern Employe * Liste_Employe_Rechercher_Nom(Liste_Employe * aListe, const char * aNom);
