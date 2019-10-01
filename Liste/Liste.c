
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  Liste/Liste.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== Liste ==============================================================
#include "Liste_Employe.h"

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    Liste_Employe lListe;
    char          lReponse[256];

    Liste_Employe_Initialiser(&lListe);
    Liste_Employe_LireFichier(&lListe, "C:\\_VC\\Enseignement\\C_Cpp\\Liste\\Employes.txt");

    printf("Entrez le nom de l'employe recherche : ");
    if (1 == scanf_s("%s", lReponse, sizeof(lReponse)))
    {
        Employe * lEmploye = Liste_Employe_Rechercher_Nom(&lListe, lReponse);
        if (NULL == lEmploye)
        {
            printf("ERREUR  Aucun employe ne correspond\n");
        }
        else
        {
            Employe_Afficher(lEmploye);
        }
    }
    else
    {
        printf( "ERREUR UTILISATEUR  Reponse invalide!\n");
        return __LINE__;
    }

    Liste_Employe_Liberer(&lListe);

    return 0;
}
