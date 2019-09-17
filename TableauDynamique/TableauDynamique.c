
// Autheur  Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  TableauDynamique/TableauDynamique.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>
#include <stdlib.h>

// ===== Window =============================================================
#include <Windows.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define NOMBRE_ITERATION  (100000)

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Ajouter(int * * aTableau, unsigned int * aNombre, int aAjout);

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    FILETIME           lDebut;
    unsigned long long lDiff_100ns;
    double             lDiff_us;
    FILETIME           lFin  ;
    unsigned int       lNombre  = 0;
    int              * lTableau = NULL;
    
    unsigned int i;

    srand(1970);

    GetSystemTimePreciseAsFileTime(&lDebut);

    for (i = 0; i < NOMBRE_ITERATION; i++)
    {
        Ajouter(&lTableau, &lNombre, rand());
    }

    GetSystemTimePreciseAsFileTime(&lFin);

    lDiff_100ns  = lFin.dwHighDateTime;
    lDiff_100ns -= lDebut.dwHighDateTime;

    lDiff_100ns <<= 32;
    
    lDiff_100ns += lFin  .dwLowDateTime;
    lDiff_100ns -= lDebut.dwLowDateTime;

    lDiff_us  = (double)( lDiff_100ns );
    lDiff_us /= 10.0;

    printf("Temps d'execution total : %f us = %f ms = %f s\n", lDiff_us, lDiff_us / 1000, lDiff_us / 1000000);
    printf("Temps d'execution par iteration : %f us\n", lDiff_us / NOMBRE_ITERATION);
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void Ajouter(int * * aTableau, unsigned int * aNombre, int aAjout)
{
    unsigned int i;

    int * lNouveau = malloc(sizeof(int) * ((*aNombre) + 1));

    if (NULL == (*aTableau))
    {
        lNouveau[0] = aAjout;
    }
    else
    {
        for (i = 0; i < (*aNombre); i++)
        {
            if ((*aTableau)[i] >= aAjout)
            {
                break;
            }

            lNouveau[i] = (*aTableau)[i];
        }

        lNouveau[i] = aAjout;

        for (; i < (*aNombre); i++)
        {
            lNouveau[i + 1] = (*aTableau)[i];
        }

        free(*aTableau);
    }

    (*aTableau) = lNouveau;
    (*aNombre)++;
}
