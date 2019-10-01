
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  Tic-Tac-Toc_Travail/Tic-Tac-Toc.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// Constantes
/////////////////////////////////////////////////////////////////////////////

#define JOUEUR_NOMBRE  ( 2 )

static const char JOUEURS[JOUEUR_NOMBRE] = { 'O', 'X' };

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Afficher(const char aJeu[3][3]);
static int  Jouer(char aJeu[3][3], char aPos, char aJoueur);
static int  Verifier(const char aJeu[3][3], char aJoueur);

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

// Retour  Toujours 0
int main()
{
    unsigned int lCompteur = 0;
    unsigned int lJoueur = 0;

    char lJeu[3][3] =
    {
        { '1', '2', '3' },
        { '4', '5', '6' },
        { '7', '8', '9' },
    };

    Afficher(lJeu);

    while (9 > lCompteur)
    {
        char lPos[64];

        printf("C'est au tour du joueur %c de jouer! Entrez une position et appuyez sur ENTER\n", JOUEURS[lJoueur]);

        if (1 == scanf_s("%s", lPos, sizeof(lPos)))
        {
            if (1 == Jouer(lJeu, lPos[0], JOUEURS[lJoueur]))
            {
                Afficher(lJeu);

                lCompteur++;

                if (1 == Verifier(lJeu, JOUEURS[lJoueur]))
                {
                    printf("Le joueur %c est le gagnant\n", JOUEURS[lJoueur]);
                    return 0;
                }

                lJoueur = (lJoueur + 1) % JOUEUR_NOMBRE;
            }
        }
    }

    printf("Il n'y a pas de gagnant\n");
    return 0;
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// aJeu [---;R--] Le jeu
void Afficher(const char aJeu[3][3])
{
    unsigned int i;

    assert(NULL != aJeu);

    for (i = 0; i < 3; i++)
    {
        unsigned int j;

        for (j = 0; j < 3; j++)
        {
            printf(" %c ", aJeu[i][j]);

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
}

// aJeu [---;RW-] Le jeu
// aPos           La position choisi par le joueur
// aJoueur        Le joueur qui joue, 'O' ou 'X'
//
// Retour
//  0  La position n'est pas valide
//  1  Le coup est joue
int Jouer(char aJeu[3][3], char aPos, char aJoueur)
{
    unsigned int i;

    assert(NULL != aJeu);

    assert(('O' == aJoueur) || ('X' == aJoueur));

    for (i = 0; i < 3; i++)
    {
        unsigned int j;

        for (j = 0; j < 3; j++)
        {
            if (aPos == aJeu[i][j])
            {
                aJeu[i][j] = aJoueur;
                return 1;
            }
        }
    }

    return 0;
}

// aJeu [---;R--] Le jeu
// aJoueur        Le dernier joueur a avoir joue, 'O' ou 'X'
//
// Retour
//  0  Pas de gagnant
//  1  Le joueur a gagne
int Verifier(const char aJeu[3][3], char aJoueur)
{
    assert(NULL != aJeu);

    assert(('O' == aJoueur) || ('X' == aJoueur));

    if ((aJeu[0][0] == aJoueur) && (aJeu[0][1] == aJoueur) && (aJeu[0][2] == aJoueur)) return 1;
    if ((aJeu[0][0] == aJoueur) && (aJeu[1][1] == aJoueur) && (aJeu[2][2] == aJoueur)) return 1;
    if ((aJeu[0][0] == aJoueur) && (aJeu[1][0] == aJoueur) && (aJeu[2][0] == aJoueur)) return 1;
    if ((aJeu[0][1] == aJoueur) && (aJeu[1][1] == aJoueur) && (aJeu[2][1] == aJoueur)) return 1;
    if ((aJeu[0][2] == aJoueur) && (aJeu[1][1] == aJoueur) && (aJeu[2][0] == aJoueur)) return 1;
    if ((aJeu[0][2] == aJoueur) && (aJeu[1][2] == aJoueur) && (aJeu[2][2] == aJoueur)) return 1;
    if ((aJeu[1][0] == aJoueur) && (aJeu[1][1] == aJoueur) && (aJeu[1][2] == aJoueur)) return 1;
    if ((aJeu[2][0] == aJoueur) && (aJeu[2][1] == aJoueur) && (aJeu[2][2] == aJoueur)) return 1;

    return 0;
}
