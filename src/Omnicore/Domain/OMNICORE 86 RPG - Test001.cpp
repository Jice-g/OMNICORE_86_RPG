// OMNICORE 86 RPG V1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
/*
OmniCore
│
├── Domain
├── Rules
├── Persistence
├── Services
├── Generation
└── Core
*/

// #include "pch.h"
#include <iostream>
#include <string>
#include <Omnicore/Domain/Actor.hpp>   // si Morphology est dans Actor.hpp

using namespace Omnicore::Domain;

int main()
{
    std::cout << "=== Test Morphology ===\n\n";

    // 1. Création d'une Morphology
    Morphology morph;
    morph.species = "Humain";
    morph.sizeModifier = 0;
    morph.massModifier = +1;

    // 2. Affichage
    std::cout << "Espèce         : " << morph.species << "\n";
    std::cout << "Mod. Taille    : " << morph.sizeModifier << "\n";
    std::cout << "Mod. Corpulence: " << morph.massModifier << "\n";

    // 3. Vérification simple
    if (morph.sizeModifier >= -6 && morph.sizeModifier <= 6 &&
        morph.massModifier >= -6 && morph.massModifier <= 6)
    {
        std::cout << "\n[OK] Modificateurs dans les bornes [-6..+6]\n";
    }
    else
    {
        std::cout << "\n[ERREUR] Modificateurs hors bornes !\n";
    }

    // 4. Test via Actor (si tu as déjà les méthodes)
    Actor perso("Guern Dorack", e_Controller::PLAYER);
    perso.SetMorphology(morph);

    const Morphology& m2 = perso.GetMorphology();    

    std::cout << "\n=== Morphologie de " << perso.Name() << " === \n";
    std::cout << "Espèce         : " << m2.species << "\n";
    std::cout << "Mod. Taille    : " << m2.sizeModifier << "\n";
    std::cout << "Mod. Corpulence: " << m2.massModifier << "\n";

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
