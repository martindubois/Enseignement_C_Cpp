
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/SFML_Souris.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "ListeLabyrinthe.h"

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    ListeLabyrinthe lLL;

    ListeLabyrinthe_LireFichiers(&lLL);

    ListeLabyrinthe_Executer(&lLL);

    ListeLabyrinthe_Liberer(&lLL);

    return 0;
}
