
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  Tic-Tac-Toc/Tic-Tac-Toc.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

// Retour  Toujours 0
int main()
{
    char lJeu[3][3] =
    {
        { '1', '2', '3' },
        { '4', '5', '6' },
        { '7', '8', '9' },
    };

    unsigned int i;

    for (i = 0; i < 3; i++)
    {
        unsigned int j;

        for (j = 0; j < 3; j++)
        {
            printf(" %c ", lJeu[i][j]);

            if (2 != j)
            {
                printf("|");
            }
        }

        printf("\n");

        if (2 != i)
        {
            printf("--- --- ---\n");
        }
    }

    printf("\n");

    return 0;
}
