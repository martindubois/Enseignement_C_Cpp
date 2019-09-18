
// Auteur   Martin Dubois, ing.
// Product  Enseignement/C_Cpp
// Fichier  SFML_Canon/SFML_Canon.cpp

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

    Jeu_Initialiser(&lJeu);

    sf::RenderWindow lWindow(sf::VideoMode(Jeu_GetLargeur(&lJeu), Jeu_GetHauteur(&lJeu)), "SFML Canon");

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

        Jeu_Avancer(&lJeu);

        lWindow.clear();

        Jeu_Afficher(&lJeu, &lWindow);

        lWindow.display();

        // Augmenter le temps de pause sur un ordinateur rapide
        sf::sleep(sf::milliseconds(0));
    }

    return 0;
}
