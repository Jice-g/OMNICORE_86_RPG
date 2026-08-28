// #include "pch.h"
#include <iostream>
#include <array>
#include <string>
#include <Omnicore/Domain/Actor.hpp>

using namespace Omnicore::Domain;

int main()
{
    std::cout << "=== Création du personnage : Guern Dorack ===\n\n";

    // 1. Création de l'acteur (UUID auto = 1)
    Actor guern("Guern Dorack", e_Controller::PLAYER);

    // 2. Tags (3 max)
    std::array<std::string, 3> tags = {
        "PJ",
        "Guerrier",
        "" // 3e vide
    };
    guern.SetTags(tags);

    // 3. Description (16 lignes max)
    std::array<std::string, 16> desc = {
        "Je suis Guern Dorack, fils des terres du Nord.",
        "J'ai combattu dans les fosses de Ferhild.",
        "Je ne crains ni la douleur, ni la mort.",
        "", "", "", "", "", "", "", "", "", "", "", "", ""
    };
    guern.SetDescription(desc);

    // 4. Morphologie
    Morphology morph;
    morph.species = "Humain";
    morph.sizeModifier = 0;
    morph.massModifier = +1;
    guern.SetMorphology(morph);

    // 5. Blessures
    guern.AddInjury("Cicatrice_oeil", e_InjurySeverity::MODEREE);
    guern.AddInjury("Cote_felee", e_InjurySeverity::LEGERE);

    // 6. Présentation friendly
    std::cout << "Bonjour, je suis " << guern.Name() << ".\n";
    std::cout << "Mon matricule est : " << guern.InstanceID() << ".\n";

    // Tags
    std::cout << "Je suis : ";
    for (const auto& t : guern.Tags())
        if (!t.empty())
            std::cout << "'" << t << "' ";
    std::cout << "\n";

    // Description
    std::cout << "À propos de moi :\n";
    for (const auto& line : guern.Description())
        if (!line.empty())
            std::cout << "  - " << line << "\n";

    // Morphologie
    const Morphology& m = guern.GetMorphology();
    std::cout << "Morphologie : " << m.species
        << " (Taille " << m.sizeModifier
        << ", Corpulence " << m.massModifier << ")\n";

    // Blessures
    std::cout << "Blessures :\n";
    for (const auto& inj : guern.GetInjuries())
        std::cout << "  * " << inj.Tag() << " ("
        << static_cast<int>(inj.Severity()) << ")\n";

    return 0;
}
