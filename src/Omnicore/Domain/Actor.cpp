

#include <Omnicore/Domain/Actor.hpp>

namespace Omnicore::Domain
{


    // ============================================================
    // MORPHOLOGY
    // ============================================================


    Morphology::Morphology(std::string species, int sizemod, int massmod) :
        m_species(std::move(species)),
        m_sizeModifier(sizemod),
        m_massModifier(massmod)
    { }

   std::string Morphology::Species()
       {
       return m_species;
       }

   int Morphology::SizeModifier()
   {
       return m_sizeModifier;
   }

   int Morphology::MassModifier()
   {
       return m_massModifier;
   }

   void Morphology::SetSpecies(std::string spe)
   {
       m_species = spe;
   }

   void Morphology::SetSizeMod(int sizemod)
   {
       if (abs(sizemod) <= 6) m_sizeModifier = sizemod;
   }

   void Morphology::SetMassMod(int sizemod)
   {
       if (abs(sizemod) <= 6) m_massModifier = sizemod;
   }


    // ============================================================
    // INJURY
    // ============================================================

    Injury::Injury(const std::string& tag, eInjurySeverity severity) noexcept
        : m_tag(tag)
        , m_severity(severity)
        , m_penalty(ComputePenalty(severity))
    {
    }

    const std::string& Injury::Tag() const noexcept
    {
        return m_tag;
    }

    eInjurySeverity Injury::Severity() const noexcept
    {
        return m_severity;
    }

    std::string Injury::SeverityStr() const noexcept
    {   
        std::string str;
        switch (m_severity)
        {
        case eInjurySeverity::LEGERE: return "LEGERE";
        case eInjurySeverity::MODEREE: return "MODEREE";
        case eInjurySeverity::GRAVE: return "GRAVE";
        case eInjurySeverity::CRITIQUE: return "CRITIQUE";
        default: return "INDEFINIE";
        }


    }

    int Injury::Penalty() const noexcept
    {
        return m_penalty;
    }

    int Injury::ComputePenalty(eInjurySeverity s) noexcept
    {
        switch (s)
        {
        case eInjurySeverity::LEGERE:   return -1;
        case eInjurySeverity::MODEREE:  return -2;
        case eInjurySeverity::GRAVE:    return -4;
        case eInjurySeverity::CRITIQUE: return -8;
        }
        return 0;
    }

    // ============================================================
    // ACTOR
    // ============================================================

    Actor::Actor(const std::string& name, e_Controller controller)
        : Entity(name), m_controller(controller)
    {
    }

    // --- GETTERS -------------------------------------------------

    e_Controller Actor::Controller() const noexcept
    {
        return m_controller;
    }

    const Attributes& Actor::GetAttributes() const noexcept
    {
        return m_attributes;
    }

    const DerivedAttributes& Actor::GetDerivedAttributes() const noexcept
    {
        return m_derivedAttributes;
    }

    const Morphology& Actor::GetMorphology() const noexcept
    {
        return m_morphology;
    }

    int32_t Actor::Power() const noexcept
    {
        return m_power;
    }

    int32_t Actor::Level() const noexcept
    {
        return m_level;
    }

    std::span<const Injury> Actor::GetInjuries() const noexcept
    {
        return std::span<const Injury>(m_injuries.data(), m_injuries.size());
        // info : Un span, c’est juste un pointeur + une taille (il ne copie rien, il ne possède rien, il ne libère rien).
    }

    // --- SETTERS -------------------------------------------------

    void Actor::SetAttributes(int physique, int dexterite, int esprit, int perception,
        int sociabilite, int chance, int pouvoir, int neuro)
    {
        m_attributes.Set(physique, dexterite, esprit, perception, sociabilite, chance, pouvoir, neuro);
    }

    void Actor::SetController(e_Controller controller) noexcept
    {
        m_controller = controller;
    }

    void Actor::SetMorphology(const Morphology& morpho) noexcept
    {
        m_morphology = morpho;
    }

    bool Actor::SetPower(int32_t power) noexcept
    {
        // Règle métier minimale : Power >= somme des attributs
        if (power < m_attributes.Sum())
            return false;

        m_power = power;
        return true;
    }

    bool Actor::AddInjury(const std::string& tag, eInjurySeverity severity) noexcept
    {
        try
        {
            m_injuries.emplace_back(tag, severity); //emplace_back 	ajoute un élément construit directement à la fin du vecteur.
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool Actor::EraseInjury(int index) noexcept
    {
        if (index < 0 || index >= static_cast<int>(m_injuries.size()))
            return false;

        m_injuries.erase(m_injuries.begin() + index);
        return true;
    }

} // namespace OmniCore::Domain
