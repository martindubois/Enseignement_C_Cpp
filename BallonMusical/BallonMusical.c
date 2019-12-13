
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  BallonMusical/BallonMusical.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct Joueur
{
    struct Joueur * mSuivant;

    const char * mNom;
    unsigned int mTemps_s;
}
Joueur;

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Jouer(Joueur * aJoueurCourant, unsigned int aTempsRestant_s);

static Joueur * ListeJoueurs_Creer();
static void     ListeJoueurs_Liberer(Joueur * aJoueurCourant);

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    Joueur     * lJoueurCourant = ListeJoueurs_Creer();
    unsigned int lTempsRestant_s;

    srand(2019);

    lTempsRestant_s = rand();

    Jouer(lJoueurCourant, lTempsRestant_s);

    ListeJoueurs_Liberer(lJoueurCourant);

    return 0;
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void Jouer(Joueur * aJoueurCourant, unsigned int aTempsRestant_s)
{
    Joueur     * lJoueurCourant  = aJoueurCourant ;
    unsigned int lTempsRestant_s = aTempsRestant_s;

    assert(NULL != aJoueurCourant);

    while (lTempsRestant_s >= lJoueurCourant->mTemps_s)
    {
        assert(NULL != lJoueurCourant->mNom    );
        assert(NULL != lJoueurCourant->mSuivant);

        printf("%s a le ballon\n", lJoueurCourant->mNom);

        lTempsRestant_s -= lJoueurCourant->mTemps_s;

        lJoueurCourant = lJoueurCourant->mSuivant;
    }

    printf("%s a perdu\n", lJoueurCourant->mNom);
}

Joueur * ListeJoueurs_Creer()
{
    Joueur * lArture = malloc(sizeof(Joueur));
    Joueur * lDonald = malloc(sizeof(Joueur));
    Joueur * lJustin = malloc(sizeof(Joueur));
    Joueur * lMartin = malloc(sizeof(Joueur));

    lArture->mNom = "Arture Laroche"; lArture->mTemps_s = 1;
    lDonald->mNom = "Donald Trump"  ; lDonald->mTemps_s = 4;
    lJustin->mNom = "Justin Trudeau"; lJustin->mTemps_s = 3;
    lMartin->mNom = "Martin Dubois" ; lMartin->mTemps_s = 2;

    lArture->mSuivant = lDonald;
    lDonald->mSuivant = lJustin;
    lJustin->mSuivant = lMartin;
    lMartin->mSuivant = lArture;

    return lArture;
}

void ListeJoueurs_Liberer(Joueur * aJoueurCourant)
{
    Joueur * lJoueurCourant = aJoueurCourant;

    do
    {
        Joueur * lJoueurTemporaire = lJoueurCourant;

        lJoueurCourant = lJoueurCourant->mSuivant;

        free(lJoueurTemporaire);
    }
    while (lJoueurCourant != aJoueurCourant);
}
