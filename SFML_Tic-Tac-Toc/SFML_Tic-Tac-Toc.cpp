
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  SFML_Tic-Tac-Toc/SFML_Tic-Tac-Toc.cpp

// Include
/////////////////////////////////////////////////////////////////////////////

// ===== SFML ===============================================================
#include <SFML/Graphics.hpp>

// ===== SFML_Tic-Tac-Toc ===================================================
#include "Jeu.h"

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main()
{
    Jeu lJeu;

    sf::RenderWindow lWindow(sf::VideoMode(512, 600), "SFML Tic-Tac-Toc");

    Jeu_Initialiser( & lJeu );

    while (lWindow.isOpen())
    {
        sf::Event lEvent;

        while (lWindow.pollEvent(lEvent))
        {
            switch (lEvent.type)
            {
            case sf::Event::Closed     : lWindow.close(); break;
            case sf::Event::KeyReleased: Jeu_TraiterTouche(&lJeu, lEvent.key.code); break;
            }
        }

        lWindow.clear();

        Jeu_Afficher(&lJeu, &lWindow);

        lWindow.display();
    }

    return 0;
}
