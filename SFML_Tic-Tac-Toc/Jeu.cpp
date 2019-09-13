
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  SFML_Tic-Tac-Toc/Jeu.cpp

// Include
/////////////////////////////////////////////////////////////////////////////

// ===== SFML ===============================================================
#include <SFML/Graphics.hpp>

// ===== SFML_Tic-Tac-Toc ===================================================
#include "Jeu.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define FICHIER_FOND  "C:\\_VC\\Enseignement\\C_Cpp\\SFML_Tic-Tac-Toc\\Fond.jpg"
#define FICHIER_FONT  "C:\\Windows\\Fonts\\arial.ttf"

static const char * MESSAGES        [2] = { "C'est a O de jouer", "C'est a X de jouer" };
static const char * MESSAGES_GAGNANT[2] = { "Le gagnant est O"  , "Le gagnant est X"   };

static const char * NOMS_CASES[3][3] =
{
    { "1", "2", "3" },
    { "4", "5", "6" },
    { "7", "8", "9" },
};

static const char * NOMS_JOUEURS[2] = { "O", "X" };

static float POSITIONS_X[3] = { 130, 240, 350 };
static float POSITIONS_Y[3] = { 100, 220, 350 };

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void DebuterPartie(Jeu * aJeu);

static void Gagner(Jeu * aJeu, float aX, float aY, float aR);

static void InitialiserMarqueurs(Jeu * aJeu);

static void Jouer(Jeu * aJeu, unsigned int aIndex);

static void LireFichiers(Jeu * aJeu);

static bool VerifierCase(Jeu * aJeu, unsigned int aLigne, unsigned int aColonne, const char * aValeur);

static void VerifierGagnant(Jeu * aJeu);

// Fonctions
/////////////////////////////////////////////////////////////////////////////

void Jeu_Afficher(Jeu * aJeu, sf::RenderWindow * aWindow)
{
    unsigned int i, j;

    aWindow->draw(aJeu->mFond_Sprite);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            aWindow->draw(aJeu->mCases[i][j]);
        }
    }

    aWindow->draw(aJeu->mMessage);

    if (aJeu->mGagnant)
    {
        aWindow->draw(aJeu->mLigne);
    }

    if (aJeu->mNulle)
    {
        aWindow->draw(aJeu->mRond);
    }
}

void Jeu_Initialiser(Jeu * aJeu)
{
    unsigned int i, j;

    LireFichiers(aJeu);

    aJeu->mFond_Sprite.setScale(0.5, 0.5);
    aJeu->mFond_Sprite.setTexture(aJeu->mFond_Texture);

    aJeu->mMessage.setCharacterSize(50);
    aJeu->mMessage.setFont(aJeu->mFont);
    aJeu->mMessage.setPosition(50.0, 520.0);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            aJeu->mCases[i][j].setCharacterSize(50);
            aJeu->mCases[i][j].setFont(aJeu->mFont);
            aJeu->mCases[i][j].setPosition(POSITIONS_X[j], POSITIONS_Y[i]);
        }
    }

    InitialiserMarqueurs(aJeu);

    DebuterPartie(aJeu);
}

void Jeu_TraiterTouche(Jeu * aJeu, sf::Keyboard::Key aCode)
{
    switch (aCode)
    {
    case sf::Keyboard::Num1:
    case sf::Keyboard::Num2:
    case sf::Keyboard::Num3:
    case sf::Keyboard::Num4:
    case sf::Keyboard::Num5:
    case sf::Keyboard::Num6:
    case sf::Keyboard::Num7:
    case sf::Keyboard::Num8:
    case sf::Keyboard::Num9:
        Jouer(aJeu, aCode - sf::Keyboard::Num1);
        break;

    case sf::Keyboard::Numpad1:
    case sf::Keyboard::Numpad2:
    case sf::Keyboard::Numpad3:
    case sf::Keyboard::Numpad4:
    case sf::Keyboard::Numpad5:
    case sf::Keyboard::Numpad6:
    case sf::Keyboard::Numpad7:
    case sf::Keyboard::Numpad8:
    case sf::Keyboard::Numpad9:
        Jouer(aJeu, aCode - sf::Keyboard::Numpad1);
        break;

    case sf::Keyboard::Space:
        DebuterPartie(aJeu);
        break;
    }
}

// Fonction statiques
/////////////////////////////////////////////////////////////////////////////

void DebuterPartie(Jeu * aJeu)
{
    unsigned int i, j;

    aJeu->mCompteur =     0;
    aJeu->mGagnant  = false;
    aJeu->mJoueur   =     0;
    aJeu->mNulle    = false;

    aJeu->mMessage.setString(MESSAGES[aJeu->mJoueur]);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            aJeu->mCases[i][j].setFillColor(sf::Color(180, 180, 180, 255));
            aJeu->mCases[i][j].setString(NOMS_CASES[i][j]);
        }
    }
}

void Gagner(Jeu * aJeu, float aX, float aY, float aR)
{
    aJeu->mGagnant = true;
    aJeu->mLigne.setPosition(aX, aY);
    aJeu->mLigne.setRotation(aR);
    aJeu->mMessage.setString(MESSAGES_GAGNANT[aJeu->mJoueur]);
}

void InitialiserMarqueurs(Jeu * aJeu)
{
    aJeu->mLigne.setFillColor(sf::Color::Green);
    aJeu->mLigne.setSize     (sf::Vector2f(5, 350));

    aJeu->mRond.setFillColor       (sf::Color::Transparent);
    aJeu->mRond.setOutlineColor    (sf::Color::Red);
    aJeu->mRond.setOutlineThickness(4.0);
    aJeu->mRond.setPosition        (50.0, 50.0);
    aJeu->mRond.setRadius          (200.0);

}

void Jouer(Jeu * aJeu, unsigned int aIndex)
{
    unsigned int lLigne   = aIndex / 3;
    unsigned int lColonne = aIndex % 3;

    if ((!aJeu->mGagnant) && (!aJeu->mNulle) && VerifierCase(aJeu, lLigne, lColonne, NOMS_CASES[lLigne][lColonne]))
    {
        aJeu->mCases[lLigne][lColonne].setFillColor(sf::Color::Black);
        aJeu->mCases[lLigne][lColonne].setString(NOMS_JOUEURS[aJeu->mJoueur]);

        aJeu->mCompteur++;

        VerifierGagnant( aJeu );

        if ((!aJeu->mGagnant) && (9 <= aJeu->mCompteur))
        {
            aJeu->mMessage.setString("Partie nulle");
            aJeu->mNulle = true;
        }
   
        aJeu->mJoueur = (aJeu->mJoueur + 1) % 2;
    }
}

void LireFichiers(Jeu * aJeu)
{
    if (!aJeu->mFond_Texture.loadFromFile(FICHIER_FOND))
    {
        printf("ERREUR  sf::Texture::loadFromFile( \"%s\" ) a echoue\n", FICHIER_FOND);
        exit(__LINE__);
    }

    if (!aJeu->mFont.loadFromFile(FICHIER_FONT))
    {
        printf("ERREUR  sf::Font::loadFromFile( \"%s\" ) a echoue\n", FICHIER_FONT);
        exit(__LINE__);
    }
}

bool VerifierCase(Jeu * aJeu, unsigned int aLigne, unsigned int aColonne, const char * aValeur)
{
    const sf::String & lString = aJeu->mCases[aLigne][aColonne].getString();

    return (aValeur[0] == lString[0]);
}

void VerifierGagnant(Jeu * aJeu)
{
    const char * lNom = NOMS_JOUEURS[aJeu->mJoueur];

    if      (VerifierCase(aJeu, 0, 0, lNom) && VerifierCase(aJeu, 0, 1, lNom) && VerifierCase(aJeu, 0, 2, lNom))
    {
        Gagner(aJeu, POSITIONS_X[0] - 50, POSITIONS_Y[0] + 25, -90.0);
    }
    else if (VerifierCase(aJeu, 0, 0, lNom) && VerifierCase(aJeu, 1, 1, lNom) && VerifierCase(aJeu, 2, 2, lNom))
    {
        Gagner(aJeu, POSITIONS_X[0], POSITIONS_Y[0] + 25, -45.0);
    }
    else if (VerifierCase(aJeu, 0, 0, lNom) && VerifierCase(aJeu, 1, 0, lNom) && VerifierCase(aJeu, 2, 0, lNom))
    {
        Gagner(aJeu, POSITIONS_X[0] + 25, POSITIONS_Y[0] - 25, 0.0);
    }
    else if (VerifierCase(aJeu, 0, 1, lNom) && VerifierCase(aJeu, 1, 1, lNom) && VerifierCase(aJeu, 2, 1, lNom))
    {
        Gagner(aJeu, POSITIONS_X[1] + 25, POSITIONS_Y[0] - 25, 0.0);
    }
    else if (VerifierCase(aJeu, 0, 2, lNom) && VerifierCase(aJeu, 1, 1, lNom) && VerifierCase(aJeu, 2, 0, lNom))
    {
        Gagner(aJeu, POSITIONS_X[2] + 25, POSITIONS_Y[0] + 25, 45.0);
    }
    else if (VerifierCase(aJeu, 0, 2, lNom) && VerifierCase(aJeu, 1, 2, lNom) && VerifierCase(aJeu, 2, 2, lNom))
    {
        Gagner(aJeu, POSITIONS_X[2] + 25, POSITIONS_Y[0] - 25, 0.0);
    }
    else if (VerifierCase(aJeu, 1, 0, lNom) && VerifierCase(aJeu, 1, 1, lNom) && VerifierCase(aJeu, 1, 2, lNom))
    {
        Gagner(aJeu, POSITIONS_X[0] - 50, POSITIONS_Y[1] + 25, -90.0);
    }
    else if (VerifierCase(aJeu, 2, 0, lNom) && VerifierCase(aJeu, 2, 1, lNom) && VerifierCase(aJeu, 2, 2, lNom))
    {
        Gagner(aJeu, POSITIONS_X[0] - 50, POSITIONS_Y[2] + 25, -90.0);
    }
}
