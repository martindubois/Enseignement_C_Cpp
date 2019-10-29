
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  STL_File/STL_File.c

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

    // NOTE  Dans le fichier File.c du projet File, la fonction
    //       File_Personne_Initialiser est appelee ici. Dans ce projet, ce
    //       n'est pas necessaire car le constructeur de la classe std::list
    //       s'occupe de l'initialisation.

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

            int lRet = sscanf_s(lLigne, "%s %s", lCommande, sizeof(lCommande), lPrenom, sizeof(lPrenom));

            if      ((2 == lRet) && (0 == _stricmp("Ajouter" , lCommande))) { Ajouter (&lPersonnes, lPrenom); }
            else if ((1 == lRet) && (0 == _stricmp("Suivant" , lCommande))) { Suivant (&lPersonnes); }
            else if ((1 == lRet) && (0 == _stricmp("Terminer", lCommande))) { Terminer(&lPersonnes); lContinuer = false; }
            else
            {
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
    Personne lPersonne;

    assert(NULL != aPersonnes);
    assert(NULL != aPrenom   );

    lPersonne.mPrenom = aPrenom;

    // NOTE  Ici, nous ajoutons la structure de type Personne que nous avons
    //       initialise. Cette structure sera copiee dans la liste. Si la
    //       structure Personne contenant enormement de donnees, cette copie
    //       serait couteuse en temps de calcule et il pourrait devenir
    //       interessant d'utiliser une liste de pointeurs pour eviter ces
    //       copies.
    aPersonnes->push_back(lPersonne);
}

void Suivant(File_Personne * aPersonnes)
{
    assert(NULL != aPersonnes);

    if ( aPersonnes->empty()  )
    {
        printf("La file est vide\n");
    }
    else
    {
        // NOTE  La methode front permet d'acceder l'element situe au debut
        //       de la liste mais il ne retire pas cet element de la liste.
        //       Il faut appeler pop_front pour retirer l'element de la
        //       liste.
        Personne_Afficher( & aPersonnes->front() );
        aPersonnes->pop_front();
    }
}

void Terminer(File_Personne * aPersonnes)
{
    assert(NULL != aPersonnes);

    while ( ! aPersonnes->empty() )
    {
        Personne_Afficher( & aPersonnes->front() );
        aPersonnes->pop_front();
    }
}
