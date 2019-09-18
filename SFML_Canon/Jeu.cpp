
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  SFML_Canon/Jeu.cpp

// Include
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <math.h>

// ===== SFML ===============================================================
#include <SFML/Graphics.hpp>

// ===== SFML_Tic-Tac-Toc ===================================================
#include "Jeu.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define CANON_LONGUEUR_pix  (80)

#define FICHIER_CANON   "C:\\_VC\\Enseignement\\C_Cpp\\SFML_Canon\\Canon.png"
#define FICHIER_FOND    "C:\\_VC\\Enseignement\\C_Cpp\\SFML_Canon\\Fond.png"
#define FICHIER_FONT    "C:\\Windows\\Fonts\\arial.ttf"
#define FICHIER_POUDRE  "C:\\_VC\\Enseignement\\C_Cpp\\SFML_Canon\\Poudre%u.png"

static const char * MESSAGES        [NOMBRE_DE_JOUEUR] = { "C'est au tour du joueur 1", "C'est au tour du joueur 2" };
static const char * MESSAGES_GAGNANT[NOMBRE_DE_JOUEUR] = { "Le joueur 1 a gagne"      , "Le joueur 2 a gagne"       };

#define PI  (3.1416)

#define ROUGE_CIBLE   (237)
#define ROUGE_CIEL    (153)
#define ROUGE_JOUEUR  (163)
#define ROUGE_NUAGE   (255)

// Diminuer la valeur de VITESSE sur un ordinateur rapide
#define VITESSE_pix_f  (10.0)

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Canon_Baisser(Jeu * aJeu);
static void Canon_Monter (Jeu * aJeu);

static void DebuterPartie(Jeu * aJeu);
static void DebuterTour  (Jeu * aJeu);

static void Gagner(Jeu * aJeu);

static void LireFichiers(Jeu * aJeu);

static void Poudre_Ajouter(Jeu * aJeu);
static void Poudre_Retirer(Jeu * aJeu);

static void Tirer(Jeu * aJeu);

static sf::Vector2f TrouverPremierJoueur(Jeu * aJeu);
static sf::Vector2f TrouverSecondJoueur (Jeu * aJeu);

static void Verifier(Jeu * aJeu, sf::Vector2f aPosition);

// Fonctions
/////////////////////////////////////////////////////////////////////////////

// aJeu     [---;R--]
// aWindows [---;RW-] La fenetre dans laquelle afficher
void Jeu_Afficher(Jeu * aJeu, sf::RenderWindow * aWindow)
{
    assert(NULL != aJeu   );
    assert(NULL != aWindow);

    unsigned int i;

    aWindow->draw(aJeu->mFond_Sprite);

    for (i = 0; i < NOMBRE_DE_JOUEUR; i++)
    {
        aWindow->draw(aJeu->mCanon_Sprites[i]);
    }

    switch (aJeu->mEtat)
    {
    case ETAT_EN_VOL:
        aWindow->draw(aJeu->mProjectil);
        break;

    case ETAT_GAGNE:
        aWindow->draw(aJeu->mMessage);
        break;

    case ETAT_JOUER:
        aWindow->draw(aJeu->mMessage      );
        aWindow->draw(aJeu->mPoudre_Sprite);
        break;

    default: assert(false);
    }
}

// aJeu [---;RW-]
void Jeu_Avancer(Jeu * aJeu)
{
    assert(NULL != aJeu);

    sf::Vector2f lPosition;

    switch (aJeu->mEtat)
    {
    case ETAT_EN_VOL:
        lPosition = aJeu->mProjectil   .getPosition();

        if ((0 > lPosition.x) || (aJeu->mFond_Taille.x < lPosition.x) || (aJeu->mFond_Taille.y < lPosition.y))
        {
            // Le projectil a quitter la zone de jeu
            DebuterTour(aJeu);
        }
        else
        {
            Verifier(aJeu, lPosition);

            aJeu->mProjectil_VitesseY_pix_f += 0.03 * VITESSE_pix_f;

            aJeu->mProjectil.setPosition((float)(lPosition.x + aJeu->mProjectil_VitesseX_pix_f), (float)(lPosition.y + aJeu->mProjectil_VitesseY_pix_f));
        }
        break;

    case ETAT_GAGNE:
    case ETAT_JOUER:
        break;

    default: assert(false);
    }
}

// aJeu [---;R--]
unsigned int Jeu_GetHauteur(Jeu * aJeu)
{
    assert(NULL != aJeu);

    return aJeu->mFond_Taille.y;
}

// aJeu [---;R--]
unsigned int Jeu_GetLargeur(Jeu * aJeu)
{
    assert(NULL != aJeu);

    return aJeu->mFond_Taille.x;
}

// aJeu [---;RW-]
void Jeu_Initialiser(Jeu * aJeu)
{
    sf::Vector2f lPosition;
    sf::Vector2u lTaille;
    unsigned int i;

    assert(NULL != aJeu);

    LireFichiers(aJeu);

    aJeu->mFond_Image  = aJeu->mFond_Texture.copyToImage();
    aJeu->mFond_Taille = aJeu->mFond_Texture.getSize();

    aJeu->mFond_Sprite.setTexture(aJeu->mFond_Texture);

    aJeu->mMessage.setCharacterSize(50);
    aJeu->mMessage.setFillColor    (sf::Color::Red);
    aJeu->mMessage.setFont         (aJeu->mFont);
    aJeu->mMessage.setPosition     (10.0, 10.0);

    aJeu->mPoudre_Sprite.setPosition((float)(aJeu->mFond_Taille.x / 2.0), (float)(aJeu->mFond_Taille.y * 0.9));

    aJeu->mProjectil.setFillColor(sf::Color::Black);
    aJeu->mProjectil.setRadius   (5.0);

    lTaille = aJeu->mCanon_Texture.getSize();

    for (i = 0; i < NOMBRE_DE_JOUEUR; i++)
    {
        aJeu->mCanon_Sprites[i].setOrigin ((float)(lTaille.x / 2.0), (float)(lTaille.y * 0.75));
        aJeu->mCanon_Sprites[i].setTexture(aJeu->mCanon_Texture);
    }

    lPosition = TrouverPremierJoueur(aJeu);
    aJeu->mCanon_Sprites[0].setPosition(lPosition); // 50.0, 930.0);

    lPosition = TrouverSecondJoueur(aJeu);
    aJeu->mCanon_Sprites[1].setPosition(lPosition); // 970.0, 720.0);

    DebuterPartie(aJeu);
}

// aJeu [---;RW-]
// aCode          Le code de la touche
void Jeu_TraiterTouche(Jeu * aJeu, sf::Keyboard::Key aCode)
{
    assert(NULL != aJeu);

    switch (aJeu->mEtat)
    {
    case ETAT_EN_VOL:
        break;

    case ETAT_GAGNE:
        switch (aCode)
        {
        case sf::Keyboard::Space: DebuterPartie(aJeu); break;
        }
        break;

    case ETAT_JOUER:
        switch (aCode)
        {
        case sf::Keyboard::Down : Canon_Baisser(aJeu); break;
        case sf::Keyboard::Up   : Canon_Monter (aJeu); break;

        case sf::Keyboard::Right: Poudre_Ajouter(aJeu); break;
        case sf::Keyboard::Left : Poudre_Retirer(aJeu); break;

        case sf::Keyboard::Space: Tirer(aJeu); break;
        }
        break;

    default: assert(false);
    }
}

// Fonction statiques
/////////////////////////////////////////////////////////////////////////////

// aJeu [---;RW-]
void Canon_Baisser(Jeu * aJeu)
{
    float lRotation_deg;

    assert(NULL != aJeu);

    lRotation_deg = aJeu->mCanon_Sprites[aJeu->mJoueur].getRotation();

    switch (aJeu->mJoueur)
    {
    case 0: lRotation_deg++; break;
    case 1: lRotation_deg--; break;

    default: assert(false);
    }

    aJeu->mCanon_Sprites[aJeu->mJoueur].setRotation(lRotation_deg);
}

// aJeu [---;RW-]
void Canon_Monter(Jeu * aJeu)
{
    float lRotation_deg;

    assert(NULL != aJeu);

    lRotation_deg = aJeu->mCanon_Sprites[aJeu->mJoueur].getRotation();

    switch (aJeu->mJoueur)
    {
    case 0: lRotation_deg--; break;
    case 1: lRotation_deg++; break;

    default: assert(false);
    }

    aJeu->mCanon_Sprites[aJeu->mJoueur].setRotation(lRotation_deg);
}

// aJeu [---;RW-]
void DebuterPartie(Jeu * aJeu)
{
    assert(NULL != aJeu);

    aJeu->mCanon_Sprites[0].setRotation(45.0);

    aJeu->mCanon_Sprites[1].setRotation(-45.0);

    aJeu->mJoueur = 1;

    DebuterTour(aJeu);
}

// aJeu [---;RW-]
void DebuterTour(Jeu * aJeu)
{
    assert(NULL != aJeu);

    aJeu->mEtat   = ETAT_JOUER;
    aJeu->mJoueur = (aJeu->mJoueur + 1) % NOMBRE_DE_JOUEUR;
    aJeu->mPoudre = 0;

    aJeu->mMessage.setString(MESSAGES[aJeu->mJoueur]);

    aJeu->mPoudre_Sprite.setTexture(aJeu->mPoudre_Textures[aJeu->mPoudre]);
}

// aJeu [---;RW-]
void Gagner(Jeu * aJeu)
{
    assert(NULL != aJeu);

    assert(ETAT_GAGNE != aJeu->mEtat);

    aJeu->mEtat = ETAT_GAGNE;

    aJeu->mMessage.setString(MESSAGES_GAGNANT[aJeu->mJoueur]);
}

// aJeu [---;RW-]
void LireFichiers(Jeu * aJeu)
{
    unsigned int i;

    assert(NULL != aJeu);

    if (!aJeu->mCanon_Texture.loadFromFile(FICHIER_CANON))
    {
        printf("ERREUR  sf::Texture::loadFromFile( \"%s\" ) a echoue\n", FICHIER_CANON);
        exit(__LINE__);
    }

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

    for (i = 0; i < NOMBRE_DE_POUDRE; i++)
    {
        char lNomFichier[256];

        sprintf_s(lNomFichier, sizeof(lNomFichier), FICHIER_POUDRE, i + 1);

        if (!aJeu->mPoudre_Textures[i].loadFromFile(lNomFichier))
        {
            printf("ERREUR  sf::Font::loadFromFile( \"%s\" ) a echoue\n", lNomFichier);
            exit(__LINE__);
        }
    }
}

// aJeu [---;RW-]
void Poudre_Ajouter(Jeu * aJeu)
{
    assert(NULL != aJeu);

    assert(NOMBRE_DE_POUDRE > aJeu->mPoudre);

    if ((NOMBRE_DE_POUDRE - 1) > aJeu->mPoudre)
    {
        aJeu->mPoudre++;
        aJeu->mPoudre_Sprite.setTexture(aJeu->mPoudre_Textures[aJeu->mPoudre]);
    }
}

// aJeu [---;RW-]
void Poudre_Retirer(Jeu * aJeu)
{
    assert(NULL != aJeu);

    if (0 < aJeu->mPoudre)
    {
        aJeu->mPoudre--;
        aJeu->mPoudre_Sprite.setTexture(aJeu->mPoudre_Textures[aJeu->mPoudre]);
    }
}

// aJeu [---;RW-]
void Tirer(Jeu * aJeu)
{
    sf::Vector2f lPosition     ;
    double       lRotation_deg ;
    double       lRotation_rad ;
    double       lVitesse_pix_f;

    assert(NULL != aJeu);

    lPosition      = aJeu->mCanon_Sprites[aJeu->mJoueur].getPosition();
    lRotation_deg  = aJeu->mCanon_Sprites[aJeu->mJoueur].getRotation();
    lRotation_rad  = lRotation_deg * 2 * PI / 360;
    lVitesse_pix_f = (aJeu->mPoudre + 2.0) * 0.5 * VITESSE_pix_f;

    aJeu->mEtat = ETAT_EN_VOL;

    aJeu->mProjectil.setPosition((float)(lPosition.x + sin(lRotation_rad) * CANON_LONGUEUR_pix), (float)(lPosition.y - cos(lRotation_rad) * CANON_LONGUEUR_pix));

    aJeu->mProjectil_VitesseX_pix_f = lVitesse_pix_f * sin(lRotation_rad);
    aJeu->mProjectil_VitesseY_pix_f = lVitesse_pix_f * cos(lRotation_rad) * -1.0;
}

// aJeu [---;R--]
sf::Vector2f TrouverPremierJoueur(Jeu * aJeu)
{
    unsigned int x, y;

    assert(NULL != aJeu);

    for (x = 0; x < aJeu->mFond_Taille.x / 2; x++)
    {
        for (y = 0; y < aJeu->mFond_Taille.y; y++)
        {
            sf::Color lPixel = aJeu->mFond_Image.getPixel(x, y);

            if (ROUGE_JOUEUR == lPixel.r)
            {
                return sf::Vector2f((float)(x), (float)(y));
            }
        }
    }

    return sf::Vector2f((float)(aJeu->mFond_Taille.x * 0.1), (float)(aJeu->mFond_Taille.y * 0.9));
}

// aJeu [---;R--]
sf::Vector2f TrouverSecondJoueur(Jeu * aJeu)
{
    unsigned int x, y;

    assert(NULL != aJeu);

    for (x = aJeu->mFond_Taille.x - 1; x > aJeu->mFond_Taille.x / 2; x--)
    {
        for (y = 0; y < aJeu->mFond_Taille.y; y++)
        {
            sf::Color lPixel = aJeu->mFond_Image.getPixel(x, y);

            if (ROUGE_JOUEUR == lPixel.r)
            {
                return sf::Vector2f((float)(x), (float)(y));
            }
        }
    }

    return sf::Vector2f((float)(aJeu->mFond_Taille.x * 0.9), (float)(aJeu->mFond_Taille.y * 0.9));
}

// aJeu [---;RW-]
// aPosition      Position du projectil
void Verifier(Jeu * aJeu, sf::Vector2f aPosition)
{
    assert(NULL != aJeu);

    // Si la position en y est negative c'est que le projectil est haut dans
    // le ciel. Il est alors certain qu'il n'y a pas de colision.
    if (0 < aPosition.y)
    {
        sf::Color lPixel = aJeu->mFond_Image.getPixel((unsigned int)(aPosition.x), (unsigned int)(aPosition.y));

        // Nous utilisons uniquement la composante rouge de la couleur pour
        // la verification.
        switch (lPixel.r)
        {
        case ROUGE_CIEL :
        case ROUGE_NUAGE:
            break;

        case ROUGE_CIBLE:
            Gagner(aJeu);
            break;

        default: // Terre, ligne ou autre
            DebuterTour(aJeu);
        }
    }
}
