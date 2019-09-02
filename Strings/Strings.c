
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_C++
// Fichier  Strings/Strings.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Constantes
/////////////////////////////////////////////////////////////////////////////

static const char BEAU_NOMS[] = "Blais Dubois Gauthier Morin Richard";

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void AssemblerPrenomEtNom(const char * aPrenom, const char * aNom, char * aSortie, unsigned int aSortie_Longueur);

// Point d'entre
/////////////////////////////////////////////////////////////////////////////

int main()
{
    unsigned int lAge   ;
    char         lLigne      [128];
    char       * lPrenom;
    char         lPrenomEtNom[128];
    char       * lNom   ;

    printf("Entrez votre age, votre prenom et votre nom\n");

    if (NULL == gets_s(lLigne, sizeof(lLigne))) // gets( lLigne )
    //          ------ Nouveau
    {
        return 1;
    }

    printf("Vous avec entrez \"%s\"\n", lLigne);
    // Nouveau               --  --

    switch (sscanf(lLigne, "%u %[^\n\r\t]", &lAge, lPrenomEtNom))
    // Nouveau                  ---------
    {
    case EOF:
    case 0  :
        lAge = 100;
        // no break
    case 1 :
        strcpy_s(lPrenomEtNom, sizeof(lPrenomEtNom), "Stupide Personnage"); // strcpy( lPrenomEtNom, "Stupide Personnage" )
        // ----- Nouveau
        break;

    case 2 : break;

    default: assert( 0 );
    }

    lNom = strchr(lPrenomEtNom, ' ');
    //     ------ Nouveau

    if (NULL == lNom)
    {
        lPrenom = NULL;
    }
    else
    {
        size_t lLongueur   ;
        char   lSortie[128];

        *lNom = '\0';
        lNom++;

        lPrenom = lPrenomEtNom;

        printf("Votre prenom est %s\n", lPrenom);

        if (0 == strcmp("Martin", lPrenom))
        //       ------ Nouveau
        {
            printf("C'est un joli prenom\n");
        }

        lLongueur = strlen(lPrenom);

        printf("Il compte %u lettres\n", lLongueur);

        printf("Votre nom est %s\n", lNom);

        if (NULL != strstr(BEAU_NOMS, lNom))
        {
            printf("C'est un beau nom\n");
        }

        lLongueur = strlen(lNom);

        printf("Il compte %u lettres\n", lLongueur);

        printf("Vos initiales sont %c%c\n", lPrenom[0], lNom[0]);

        AssemblerPrenomEtNom(lPrenom, lNom, lSortie, sizeof(lSortie));

        printf("(%s)\n", lSortie);
    }
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void AssemblerPrenomEtNom(const char * aPrenom, const char * aNom, char * aSortie, unsigned int aSortie_Longueur)
{
    strcpy_s(aSortie, aSortie_Longueur, aPrenom); // strcpy( aSortie, aPrenom );
    strcat_s(aSortie, aSortie_Longueur, " "    ); // strcat( aSortie, " "     );
    // ----- Nouveau
    strcat_s(aSortie, aSortie_Longueur, aNom   );
}
