
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  File2/File2.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ===== File ===============================================================
#include "File_Personne.h"

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Ajouter (File_Personne * aPersonnes, const char * aPrenom);
static void Suivant (File_Personne * aPersonnes);
static void Terminer(File_Personne * aPersonnes);

// Point d'entre
/////////////////////////////////////////////////////////////////////////////

int main()
{
    bool          lContinuer = true;
    char          lLigne[128];
    File_Personne lPersonnes;

    File_Personne_Initialiser(&lPersonnes);

    while (lContinuer)
    {
        printf("Entrez une commande : ");

        if (NULL == fgets(lLigne, sizeof(lLigne), stdin))
        {
            printf("ERREUR  fgets a echoue\n");
            lContinuer = false;
        }
        else
        {
            char lCommande[128];
            char lPrenom  [128];

            // QUESTION #1 : Qu'arrivera-t-il si un utilisateur entre la
            //               commande "Ajouter" en specifiant un prenom et un
            // nom ?
            int lRet = sscanf_s(lLigne, "%s %s", lCommande, sizeof(lCommande), lPrenom, sizeof(lPrenom));

            if      ((2 == lRet) && (0 == _stricmp("Ajouter" , lCommande))) { Ajouter (&lPersonnes, lPrenom); }
            else if ((1 == lRet) && (0 == _stricmp("Suivant" , lCommande))) { Suivant (&lPersonnes); }
            else if ((1 == lRet) && (0 == _stricmp("Terminer", lCommande))) { Terminer(&lPersonnes); lContinuer = false; }
            else
            {
                // QUESTION #2 : Comment faire pour que ce code soit execute ?
                printf("ERREUR  La commande n'est pas valide\n");
            }
        }
    }

    return 0;
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void Ajouter(File_Personne * aPersonnes, const char * aPrenom)
{
    Personne * lPersonne;

    assert(NULL != aPersonnes);
    assert(NULL != aPrenom   );

    lPersonne = File_Personne_Ajouter(aPersonnes);
    if (NULL == lPersonne)
    {
        printf("La liste est pleine!\n");
    }
    else
    {
        Personne_SetPrenom(lPersonne, aPrenom);
    }
}

void Suivant(File_Personne * aPersonnes)
{
    Personne * lPersonne;

    assert(NULL != aPersonnes);

    lPersonne = File_Personne_Retirer(aPersonnes);
    if (NULL == lPersonne)
    {
        printf("La file est vide\n");
    }
    else
    {
        Personne_Afficher(lPersonne);
    }
}

void Terminer(File_Personne * aPersonnes)
{
    Personne * lPersonne;

    assert(NULL != aPersonnes);

    while (NULL != (lPersonne = File_Personne_Retirer(aPersonnes)))
    {
        Personne_Afficher(lPersonne);
    }
}
