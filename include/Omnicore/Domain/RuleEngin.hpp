#pragma once


#include "Attributes.hpp"
//#include "Skills.hpp"

namespace OmniCore::Domain
{
    class RuleEngine
    {
    public:
        // --- Attributs de base ---
        static int ComputeAttributePool(int activeAttributeCount) noexcept;   // PA = 2N + 1
        static bool ValidateAttributes(const Attributes& a, int expectedPool) noexcept;

        // --- Attributs dérivés ---
        static DerivedAttributes ComputeDerived(const Attributes& a,
            int morphT, int morphC,
            bool tacticalMode) noexcept;

        // --- Compétences ---
        // static bool ValidateSkillDistribution(const Skills& skills) noexcept;
        // static int ComputeLevel(const Skills& skills) noexcept;              // Niveau = somme des points

        // --- Jets & hasard ---
        static int ResolveAction(int d6, int d8,
            int attribute, int skill, int specialization,
            int modifiers) noexcept;

        static bool IsFumble(int d6, int d8) noexcept;
    };
}
