
// Auteur   Martin Dubois, ing.
// Produit  Enseignement/C_Cpp
// Fichier  Question/Question.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// Point d'entre
/////////////////////////////////////////////////////////////////////////////

// Retour  Cette fonction retourne toujours 0.
int main()
{
    unsigned int lAge;
    char         lNom[64];

    printf("Entrez votre nom et appuyer sur ENTER\n");

    if (1 != scanf_s("%s", lNom, sizeof(lNom)))
    {
        printf("Une erreur s'est produite\n");
    }

    printf("Entrer votre age et appuyer sur ENTER\n");

    if (1 != scanf_s("%u", &lAge))
    {
        printf("Une erreur s'est produite\n");
    }

    printf("Votre nom est %s\n", lNom);
    printf("Vous avez %u ans\n", lAge);

    return 0;
}
