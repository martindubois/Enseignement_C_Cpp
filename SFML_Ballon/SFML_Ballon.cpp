
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Demo/SFML_Ballon.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== SFML ===============================================================
#include <SFML/Graphics.hpp>

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void Accel(float * aVitesse_pix_f, float aAccel_pix_f2);

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    // ===== L'initialisation ===============================================

    float lAccel_deg_f2 = 1.0;
    float lAccel_pix_f2 = 1.0;

    float lVitesseR_deg_f = 1.0;
    float lVitesseX_pix_f = 1.0;
    float lVitesseY_pix_f = 1.0;

    sf::RenderWindow lWindow(sf::VideoMode(800, 600), "SFML window");

    sf::Texture lTexture_Ballon;

    if (!lTexture_Ballon.loadFromFile("C:\\_VC\\Enseignement\\C_Cpp\\SFML_Ballon\\Ballon.jpg"))
    {
        printf("ERREUR sf::Texture::loadFromFile(  ) a echoue\n");
        return __LINE__;
    }

    sf::Sprite lSprite_Ballon(lTexture_Ballon);

    lSprite_Ballon.setOrigin( 308.0, 308.0 );
    lSprite_Ballon.setScale( 0.2f, 0.2f );

    sf::Texture lTexture_Terrain;

    if (!lTexture_Terrain.loadFromFile("C:\\_VC\\Enseignement\\C_Cpp\\SFML_Ballon\\Terrain.jpg"))
    {
        printf("ERREUR sf::Texture::loadFromFile(  ) a echoue\n");
        return __LINE__;
    }

    sf::Sprite lSprite_Terrain(lTexture_Terrain);

    // ===== La boucle principale ===========================================
    while (lWindow.isOpen())
    {
        sf::Event lEvent;

        while (lWindow.pollEvent(lEvent))
        {
            switch (lEvent.type)
            {
            case sf::Event::Closed: lWindow.close(); break;

            case sf::Event::KeyReleased:
                switch (lEvent.key.code)
                {
                case sf::Keyboard::Equal: Accel( & lVitesseX_pix_f,   lAccel_pix_f2 ); Accel( & lVitesseY_pix_f,   lAccel_pix_f2 ); break;
                case sf::Keyboard::Dash : Accel( & lVitesseX_pix_f, - lAccel_pix_f2 ); Accel( & lVitesseY_pix_f, - lAccel_pix_f2 ); break;

                case sf::Keyboard::A : lVitesseR_deg_f += lAccel_deg_f2; break;
                case sf::Keyboard::R : lVitesseR_deg_f -= lAccel_deg_f2; break;
                }
            }
        }

        sf::Vector2f lPosition = lSprite_Ballon.getPosition();

        lPosition.x += lVitesseX_pix_f;
        lPosition.y += lVitesseY_pix_f;

        lSprite_Ballon.setPosition( lPosition );

        lSprite_Ballon.setRotation(lSprite_Ballon.getRotation() + lVitesseR_deg_f);

        sf::Vector2u lLimites = lWindow.getSize();

        if ((0 > lPosition.x) || (lLimites.x < lPosition.x)) { lVitesseX_pix_f *= -1; }
        if ((0 > lPosition.y) || (lLimites.y < lPosition.y)) { lVitesseY_pix_f *= -1; }

        lWindow.clear(sf::Color(255, 255, 255, 255));

        lWindow.draw(lSprite_Terrain);
        lWindow.draw(lSprite_Ballon );

        lWindow.display();
    }

    return 0;
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

void Accel(float * aVitesse_pix_f, float aAccel_pix_f2)
{
    if (0 > (*aVitesse_pix_f))
    {
        aAccel_pix_f2 *= -1.0;
    }

    (*aVitesse_pix_f) += aAccel_pix_f2;
}
