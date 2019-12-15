
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Souris/Labyrinthe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== SFML_Souris ========================================================
#include "Labyrinthe.h"
#include "Souris.h"

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static bool TraiterEvenements(sf::RenderWindow * aWindow);

// Fonctions
/////////////////////////////////////////////////////////////////////////////

Labyrinthe * Labyrinthe_LireFichier(unsigned int aIndice)
{
    Labyrinthe * lLabyrinthe = (Labyrinthe *)(malloc(sizeof(Labyrinthe)));
    char         lNomFichier[256];

    assert(NULL != lLabyrinthe);

    lLabyrinthe->mSuivant = NULL;
    lLabyrinthe->mTexture = new sf::Texture();

    assert(NULL != lLabyrinthe->mTexture);

    sprintf_s(lNomFichier, "C:\\_VC\\Enseignement\\C_Cpp\\SFML_Souris\\Labyrinthe_%02u.png", aIndice);

    if (!lLabyrinthe->mTexture->loadFromFile(lNomFichier))
    {
        Labyrinthe_Liberer(lLabyrinthe);
        lLabyrinthe = NULL;
    }

    return lLabyrinthe;
}

bool Labyrinthe_Executer(Labyrinthe * aLabyrinthe)
{
    bool             lContinuer = true;
    unsigned int     lFacteur   =    1;
    sf::Image        lImage  ;
    Souris           lSouris ;
    sf::Sprite       lSprite ;
    sf::Vector2u     lTaille ;
    sf::Texture      lTexture;

    assert(NULL != aLabyrinthe          );
    assert(NULL != aLabyrinthe->mTexture);

    lTaille = Labyrinthe_ObtenirTaille(aLabyrinthe);

    if      (( 64 >= lTaille.x) && ( 64 >= lTaille.y)) { lFacteur = 5; }
    else if ((128 >= lTaille.x) && (128 >= lTaille.y)) { lFacteur = 4; }
    else if ((256 >= lTaille.x) && (256 >= lTaille.y)) { lFacteur = 3; }

    sf::RenderWindow lWindow(sf::VideoMode(lTaille.x * lFacteur, lTaille.y * lFacteur), "SFML_Souris");

    lImage = aLabyrinthe->mTexture->copyToImage();

    lTexture.loadFromImage(lImage);

    lSprite.setScale  ((float)(lFacteur), (float)(lFacteur));
    lSprite.setTexture(lTexture);

    Souris_Initialiser(&lSouris, &lImage, aLabyrinthe);

    while (lWindow.isOpen())
    {
        bool lTrouver = Souris_Avancer(&lSouris, &lImage);

        lContinuer = TraiterEvenements(&lWindow);

        lTexture.loadFromImage(lImage);

        lWindow.clear();
        lWindow.draw(lSprite);
        lWindow.display();

        if (lTrouver)
        {
            sf::sleep(sf::seconds(3));
            lWindow.close();
        }
    }

    Souris_Liberer(&lSouris);

    return lContinuer;
}

void Labyrinthe_Liberer(Labyrinthe * aLabyrinthe)
{
    delete aLabyrinthe->mTexture;

    free(aLabyrinthe);
}

sf::Vector2u Labyrinthe_ObtenirTaille(Labyrinthe * aLabyrinthe)
{
    assert(NULL != aLabyrinthe          );
    assert(NULL != aLabyrinthe->mTexture);

    return aLabyrinthe->mTexture->getSize();
}

// Fonctions statique
/////////////////////////////////////////////////////////////////////////////

bool TraiterEvenements(sf::RenderWindow * aWindow)
{
    bool      lContinuer = true;
    sf::Event lEvent;

    assert(NULL != aWindow);

    while (aWindow->pollEvent(lEvent))
    {
        switch (lEvent.type)
        {
        case sf::Event::Closed:
            lContinuer = false;
            aWindow->close();
            break;
        }
    }

    return lContinuer;
}