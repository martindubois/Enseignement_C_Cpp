
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Echelle/SFML_Echelle.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#define _USE_MATH_DEFINES

#include <assert.h>
#include <math.h>

// ===== SFML ===============================================================
#include <SFML/Graphics.hpp>

// Constantes
/////////////////////////////////////////////////////////////////////////////

#define CASE_HAUTEUR (65)
#define CASE_LARGEUR (80)

#define NOMBRE_COLONNE (10)
#define NOMBRE_ECHELLE ( 4)
#define NOMBRE_LIGNE   (10)

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void  AjusterSprite      (sf::Sprite * aSprite, unsigned int aBas_Colonne, unsigned int aBas_Ligne, unsigned int aHaut_Colonne, unsigned int aHaut_Ligne);
static void  DessinerGrille     (sf::RenderWindow * aWindow);
static void  InitialiserEchelles(sf::Sprite * aSprites, sf::Texture * aTexture);
static float RadianToDegre      (double aRadian);
static void  TraiterEvenements  (sf::RenderWindow * aWindow);

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    sf::Sprite       lSprites[NOMBRE_ECHELLE];
    sf::Texture      lTexture;
    sf::RenderWindow lWindow(sf::VideoMode(800, 800), "SFML Echelle");
    unsigned int     i;

    // QUESTION #1 - La seule utilisation de la variable "lTexture" dans la
    //               fonction "main" est d'obtenir son adresse pour la passer
    //               a la fonction "InitialiserEchelles". Pourquoi, le
    //               programmeur n'a-t-il pas simplement declarer la variable
    //               "lTexture" a l'interieur de la fonction
    //               "InitialiserEchelles" ?
    InitialiserEchelles(lSprites, &lTexture);

    // ===== Ajuster les echelles ===========================================

    AjusterSprite(lSprites + 0, 7, 7, 5, 3);
    AjusterSprite(lSprites + 1, 5, 9, 6, 7);
    AjusterSprite(lSprites + 2, 2, 9, 1, 8);
    AjusterSprite(lSprites + 3, 2, 7, 3, 0);

    // ===== La boucle principale ===========================================

    while (lWindow.isOpen())
    {
        TraiterEvenements(&lWindow);

        lWindow.clear(sf::Color::Green);

        DessinerGrille(&lWindow);

        for (i = 0; i < NOMBRE_ECHELLE; i++)
        {
            lWindow.draw(lSprites[i]);
        }

        lWindow.display();
    }
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void AjusterSprite(sf::Sprite * aSprite, unsigned int aBas_Colonne, unsigned int aBas_Ligne, unsigned int aHaut_Colonne, unsigned int aHaut_Ligne)
{
    unsigned int lBas_X ;
    unsigned int lBas_Y ;
    float        lDiff_X;
    float        lDiff_Y;
    unsigned int lHaut_X;
    unsigned int lHaut_Y;
    sf::Vector2u lSize  ;

    assert(NULL           != aSprite      );
    assert(NOMBRE_COLONNE > aBas_Colonne  );
    assert(NOMBRE_LIGNE   > aBas_Ligne    );
    assert(NOMBRE_COLONNE > aHaut_Colonne );
    assert(aBas_Ligne     > aHaut_Ligne   );

    lSize = aSprite->getTexture()->getSize();

    // QUESTION #2 - A quoi sert le "+ CASE_LARGEUR / 2" et le
    //               "+ CASE_HAUTEUR / 2" a la fin des lignes qui suivent ?

    lBas_X = aBas_Colonne * CASE_LARGEUR + CASE_LARGEUR / 2;
    lBas_Y = aBas_Ligne   * CASE_HAUTEUR + CASE_HAUTEUR / 2;

    lHaut_X = aHaut_Colonne * CASE_LARGEUR + CASE_LARGEUR / 2;
    lHaut_Y = aHaut_Ligne   * CASE_HAUTEUR + CASE_HAUTEUR / 2;

    // QUESTION #3 - Pourquoi utiliser "(float)(lBas_X) - (float)(lHaut_X)"
    //               et non "(float)(lBas_X - lHaut_X)" ?
    lDiff_X = (float)(lBas_X) - (float)(lHaut_X);
    lDiff_Y = (float)(lBas_Y) - (float)(lHaut_Y);

    // QUESTION #4 - A quoi sert le f dans "2.0f" ? "2.0f" est-il quivalent a
    //               "(float)(2.0)" ?
    // QUESTION #5 - Pourquoi modifier la position pour qu'elle corresponde
    //               au point a mi-chemin entre le haut et le bas ?
    aSprite->setPosition((float)(lBas_X + lHaut_X) / 2.0f, (float)(lBas_Y + lHaut_Y) / 2.0f);
    // QUESTION #6 - A quoi sert le "0.0f - " ?
    aSprite->setRotation(0.0f - RadianToDegre(atan2(lDiff_X, lDiff_Y)));
    // QUESTION #7 - Pourquoi le "Scale" en X est-il ajuste ?
    aSprite->setScale   (CASE_LARGEUR / (float)(lSize.x), sqrt( lDiff_X * lDiff_X + lDiff_Y * lDiff_Y ) / lSize.y);
}

void DessinerGrille(sf::RenderWindow * aWindow)
{
    sf::RectangleShape lRS;
    unsigned int       i  ;

    assert(NULL != aWindow);

    for (i = 1; i <= NOMBRE_LIGNE; i++)
    {
        lRS.setPosition(0, (float)(i * CASE_HAUTEUR));
        lRS.setSize(sf::Vector2f(CASE_LARGEUR * NOMBRE_COLONNE, 1));
        aWindow->draw(lRS);
    }

    for (i = 1; i < NOMBRE_COLONNE; i ++)
    {
        lRS.setPosition((float)(i * CASE_LARGEUR), 0);
        lRS.setSize(sf::Vector2f(1, CASE_HAUTEUR * NOMBRE_LIGNE));
        aWindow->draw(lRS);
    }
}

void InitialiserEchelles(sf::Sprite * aSprites, sf::Texture * aTexture)
{
    bool         lRet ;
    sf::Vector2u lSize;
    unsigned int i    ;

    assert(NULL != aSprites);
    assert(NULL != aTexture);

    lRet = aTexture->loadFromFile("C:\\_VC\\Enseignement\\C_Cpp\\SFML_Echelle\\Echelle.png");
    assert(lRet);

    lSize = aTexture->getSize();

    for (i = 0; i < NOMBRE_ECHELLE; i++)
    {
        aSprites[i].setTexture(*aTexture);

        aSprites[i].setOrigin((float)(lSize.x / 2), (float)(lSize.y / 2));
    }
}

float RadianToDegre(double aRadian)
{
    return (float)((aRadian / (2 * M_PI)) * 360.0);
}

void TraiterEvenements(sf::RenderWindow * aWindow)
{
    sf::Event lEvent;

    assert(NULL != aWindow);

    while (aWindow->pollEvent(lEvent))
    {
        switch (lEvent.type)
        {
        case sf::Event::Closed: aWindow->close(); break;
        }
    }
}
