
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/Souris.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== SFML_Souris ========================================================
#include "Souris.h"

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef enum
{
    ESSAYE ,
    FROMAGE,
    MURE   ,
    OK     ,
}
Resultat;

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ESSAYE_VERT (1)

#define FROMAGE_VERT (127)

#define SOURIS_BLEU  (232)
#define SOURIS_ROUGE (  0)
#define SOURIS_VERT  (162)

static const int DIRECTIONS[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

// Declaration des fonctions statique
/////////////////////////////////////////////////////////////////////////////

static void     Colorer(Souris * aSouris, sf::Image * aImage, sf::Color aColor);
static Resultat Essayer(Souris * aSouris, sf::Image * aImage, unsigned int aX, unsigned int aY);

// Fonctions
/////////////////////////////////////////////////////////////////////////////

bool Souris_Avancer(Souris * aSouris, sf::Image * aImage)
{
    unsigned int i, x, y;

    assert(NULL != aSouris);
    assert(NULL != aImage );

    x = aSouris->mPile[aSouris->mPile_Hauteur].mX;
    y = aSouris->mPile[aSouris->mPile_Hauteur].mY;

    for (i = 0; i < 4; i++)
    {
        switch (Essayer(aSouris, aImage, x + DIRECTIONS[i][0], y + DIRECTIONS[i][1]))
        {
        case ESSAYE:
        case MURE  :
            break;

        case FROMAGE:
            return true;

        case OK:
            return false;
        }
    }

    if (0 == aSouris->mPile_Hauteur)
    {
        printf("ATTENTION  Il n'y a pas de fromage accessible\n");
        return true;
    }

    Colorer(aSouris, aImage, sf::Color(255, ESSAYE_VERT, 0, 255));

    aSouris->mPile_Hauteur--;

    Colorer(aSouris, aImage, sf::Color(SOURIS_ROUGE, SOURIS_VERT, SOURIS_BLEU, 255));

    return false;
}

void Souris_Initialiser(Souris * aSouris, sf::Image * aImage, Labyrinthe * aLabyrinthe)
{
    sf::Vector2u lTaille;

    unsigned int x, y;

    assert(NULL != aSouris    );
    assert(NULL != aImage     );
    assert(NULL != aLabyrinthe);

    lTaille = Labyrinthe_ObtenirTaille(aLabyrinthe);

    aSouris->mPile         = (Souris_Position *)(malloc(sizeof(Souris_Position) * lTaille.x * lTaille.y));
    aSouris->mPile_Hauteur = 0;

    for (x = 0; x < lTaille.x; x++)
    {
        for (y = 0; y < lTaille.y; y++)
        {
            sf::Color lPixel = aImage->getPixel(x, y);

            if (SOURIS_VERT == lPixel.g)
            {
                aSouris->mPile[aSouris->mPile_Hauteur].mX = x;
                aSouris->mPile[aSouris->mPile_Hauteur].mY = y;
                return;
            }
        }
    }

    printf("ATTENTION  Le labyrinthe ne contient pas de souris\n");

    aSouris->mPile[aSouris->mPile_Hauteur].mX = lTaille.x / 2;
    aSouris->mPile[aSouris->mPile_Hauteur].mY = lTaille.y / 2;
}

void Souris_Liberer(Souris * aSouris)
{
    free(aSouris->mPile);
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void Colorer(Souris * aSouris, sf::Image * aImage, sf::Color aColor)
{
    assert(NULL != aSouris);
    assert(NULL != aImage );

    aImage->setPixel(aSouris->mPile[aSouris->mPile_Hauteur].mX, aSouris->mPile[aSouris->mPile_Hauteur].mY, aColor);
}

Resultat Essayer(Souris * aSouris, sf::Image * aImage, unsigned int aX, unsigned int aY)
{
    sf::Color lPixel;

    assert(NULL != aSouris);
    assert(NULL != aImage );
    
    lPixel = aImage->getPixel(aX, aY);

    switch (lPixel.g)
    {
    case            0: return MURE   ;
    case ESSAYE_VERT : return ESSAYE ;
    case FROMAGE_VERT: return FROMAGE;
    case          255: break;

    default: break;
    }

    Colorer(aSouris, aImage, sf::Color(255, ESSAYE_VERT, 255, 255));

    aSouris->mPile_Hauteur++;

    aSouris->mPile[aSouris->mPile_Hauteur].mX = aX;
    aSouris->mPile[aSouris->mPile_Hauteur].mY = aY;

    Colorer(aSouris, aImage, sf::Color(SOURIS_ROUGE, SOURIS_VERT, SOURIS_BLEU, 255));

    return OK;
}
