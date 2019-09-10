
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  SFML_Demo/SFML_Demo.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== SFML ===============================================================
#include <SFML/Graphics.hpp>

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    // ===== L'initialisation ===============================================

    // Un programme SFML debute par l'initialisation des variables qui seront
    // utilise par la suite. Souvent, des donnees comme des polices de
    // caracteres ou des images sont chargees a partire de fichiers.

    // Cette ligne cree une variable de type sf::RenderWindows. Cette
    // variable est associee a une fenetre dans laquelle il est possible
    // d'afficher des images ou des graphique.
    sf::RenderWindow lWindow(sf::VideoMode(800, 600), "SFML window");

    // ----- Item # 1 - Afficher du texte -----------------------------------

    // Pour afficher du texte, nous devons avoir un instance de sf::Font.
    sf::Font lFont;

    if (!lFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        printf("ERREUR sf::Font::loadFromFile(  ) a echoue\n");
        return __LINE__;
    }

    sf::Text lText("Hello SFML", lFont, 50);

    // ----- Item #2 - Afficher des images ----------------------------------

    sf::Texture lTexture;

    if (!lTexture.loadFromFile("C:\\_VC\\Enseignement\\C_Cpp\\SFML_Demo\\Personnage.jpg"))
    {
        printf("ERREUR sf::Texture::loadFromFile(  ) a echoue\n");
        return __LINE__;
    }

    sf::Sprite lSprite(lTexture);

    // ===== La boucle principale ===========================================
    while ( lWindow.isOpen() )
    {
        // La premiere partie de la boucle principale est le traitement des
        // evennement comme les cliques de l'utilisateur ou les touche du
        // clavier

        sf::Event lEvent;

        while ( lWindow.pollEvent( lEvent ) )
        {
            switch (lEvent.type)
            {
            case sf::Event::Closed: lWindow.close(); break;
            }
        }

        // La seconde partie de la boucle principale sont les mouvements.
        // Cette partie est utilise pour changer la position (ou d'autre
        // prorpietes des objets) qui doivent changer en fonction du temps.

        // ----- Item #2 - Afficher des images ------------------------------

        lSprite.setRotation(lSprite.getRotation() + 1);

        // La troisieme partie de la boucle principale est le code
        // d'affichage. Cette partie debute toujours par l'effacement de
        // la fenetre.
        lWindow.clear();

        // ----- Item # 1 - Afficher du texte -------------------------------
        lWindow.draw( lText );

        // ----- Item # 2 - Afficher des images -----------------------------
        lWindow.draw(lSprite);

        // La quatrieme est derniere partie de la boucle principale est le
        // signal d'afficher le nouveau "frame" a l'ecran.
        lWindow.display();
    }

    return 0;
}
