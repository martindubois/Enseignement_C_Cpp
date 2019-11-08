
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  Sudoku/Sudoku.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Afficher        (const char aTableau[9][9]);
static void Resoudre        (      char aTableau[9][9], unsigned int aLigne, unsigned int aColonne);
static bool Verifier        (const char aTableau[9][9]);
static bool Verifier_Bloc   (const char aTableau[9][9], unsigned int aLigne, unsigned int aColonne);
static bool Verifier_Colonne(const char aTableau[9][9],                      unsigned int aColonne);
static bool Verifier_Ligne  (const char aTableau[9][9], unsigned int aLigne);

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    char lTableau[9][9] =
    {
        { ' ', ' ', ' ',  ' ', ' ', '7',  '5', ' ', ' ' },
        { '7', ' ', ' ',  '1', ' ', ' ',  ' ', '4', ' ' },
        { '5', ' ', ' ',  ' ', ' ', ' ',  '2', ' ', ' ' },

        { ' ', ' ', '1',  '3', '9', ' ',  ' ', ' ', '8' },
        { '3', ' ', ' ',  '7', '8', '6',  ' ', ' ', '4' },
        { '8', ' ', ' ',  ' ', '4', '1',  '7', ' ', ' ' },

        { ' ', ' ', '8',  ' ', ' ', ' ',  ' ', ' ', '9' },
        { ' ', '5', ' ',  ' ', ' ', '3',  ' ', ' ', '1' },
        { ' ', ' ', '4',  '6', ' ', ' ',  ' ', ' ', ' ' },
    };

    assert(Verifier(lTableau));

    Resoudre(lTableau, 0, 0);
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void Afficher(const char aTableau[9][9])
{
    unsigned int i;
    unsigned int j;

    assert(NULL != aTableau);

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%c ", aTableau[i][j]);

            if (2 == (j % 3))
            {
                printf("  ");
            }
        }

        printf("\n");

        if (2 == (i % 3))
        {
            printf("\n");
        }
    }

    printf("\n");
}

void Resoudre(char aTableau[9][9], unsigned int aLigne, unsigned int aColonne)
{
    unsigned int lLigneSuivante   = aLigne  ;
    unsigned int lColonneSuivante = aColonne;

    char c;

    assert(NULL != aTableau );
    assert(   9 >  aLigne   );
    assert(   9 >  aColonne );

    do
    {
        if (8 <= lColonneSuivante)
        {
            lColonneSuivante = 0;
            lLigneSuivante++;
        }
        else
        {
            lColonneSuivante ++;
        }
    }
    while ((9 > lLigneSuivante) && (' ' != aTableau[lLigneSuivante][lColonneSuivante]));

    for (c = '1'; c <= '9'; c++)
    {
        aTableau[aLigne][aColonne] = c;

        if (Verifier(aTableau))
        {
            if (9 <= lLigneSuivante)
            {
                Afficher(aTableau);
            }
            else
            {
                Resoudre(aTableau, lLigneSuivante, lColonneSuivante);
            }
        }
    }

    aTableau[aLigne][aColonne] = ' ';
}

bool Verifier(const char aTableau[9][9])
{
    unsigned int i;
    unsigned int j;

    assert(NULL != aTableau);

    for (i = 0; i < 9; i++)
    {
        if (!Verifier_Ligne(aTableau, i))
        {
            return false;
        }

        if (!Verifier_Colonne(aTableau, i))
        {
            return false;
        }
    }

    for (i = 0; i < 9; i += 3)
    {
        for (j = 0; j < 9; j += 3)
        {
            if (!Verifier_Bloc(aTableau, i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool Verifier_Bloc(const char aTableau[9][9], unsigned int aLigne, unsigned int aColonne)
{
    unsigned int i;

    assert(NULL != aTableau);
    assert(   9 >  aLigne  );
    assert(   9 >  aColonne);

    for (i = 0; i < 3; i++)
    {
        unsigned int j;

        for (j = 0; j < 3; j++)
        {
            char c = aTableau[aLigne + i][aColonne + j];

            if (' ' != c)
            {
                unsigned int k;

                for (k = 0; k < 3; k++)
                {
                    unsigned int l;

                    for (l = 0; l < 3; l++)
                    {
                        if ((i != k) && (j != l) && (c == aTableau[aLigne + k][aColonne + l]))
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Verifier_Colonne(const char aTableau[9][9], unsigned int aColonne)
{
    unsigned int i;

    assert(NULL != aTableau);
    assert(   9 >  aColonne);

    for (i = 0; i < 8; i++)
    {
        char c = aTableau[i][aColonne];

        if (' ' != c)
        {
            unsigned int j;

            for (j = i + 1; j < 9; j++)
            {
                if (c == aTableau[j][aColonne])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Verifier_Ligne(const char aTableau[9][9], unsigned int aLigne)
{
    unsigned int i;

    assert(NULL != aTableau);
    assert(   9 >  aLigne  );

    for (i = 0; i < 8; i++)
    {
        char c = aTableau[aLigne][i];

        if (' ' != c)
        {
            unsigned int j;

            for (j = i + 1; j < 9; j++)
            {
                if (c == aTableau[aLigne][j])
                {
                    return false;
                }
            }
        }
    }

    return true;
}
