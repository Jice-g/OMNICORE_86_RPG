
#include <Omnicore/Domain/Attributes.hpp>

namespace Omnicore::Domain
{
    // ============================================================
    // 1. ATTRIBUTES — Implémentation
    // ============================================================

    Attributes::Attributes(int physique, int dexterite, int esprit, int perception, int sociabilite, int chance,
        int pouvoir, int neuro) noexcept
        : m_physique(physique), m_dexterite(dexterite), m_esprit(esprit), m_perception(perception), m_sociabilite(sociabilite), m_chance(chance), m_pouvoir(pouvoir), m_neuro(neuro)
    {
        SetSum();
    }


    void Attributes::Set(int physique, int dexterite, int esprit, int perception, int sociabilite, int chance,
        int pouvoir, int neuro) noexcept
    {
        m_physique = physique;
        m_dexterite = dexterite;
        m_esprit = esprit;
        m_perception = perception;
        m_sociabilite = sociabilite;
        m_chance = chance;
        m_pouvoir = pouvoir;
        m_neuro = neuro;

        SetSum();
    }


    void Attributes::SetSum() noexcept
    {
        m_attSum = m_physique + m_dexterite + m_esprit + m_perception + m_sociabilite + m_chance
            + m_pouvoir + m_neuro;
    }


    // --- ACCESSEURS (codes du manuel) ---

    int Attributes::PHY() const noexcept { return m_physique; }
    int Attributes::DEX() const noexcept { return m_dexterite; }
    int Attributes::ESP() const noexcept { return m_esprit; }
    int Attributes::PER() const noexcept { return m_perception; }
    int Attributes::SOC() const noexcept { return m_sociabilite; }
    int Attributes::CHA() const noexcept { return m_chance; }
    int Attributes::POU() const noexcept { return m_pouvoir; }
    int Attributes::NEU() const noexcept { return m_neuro; }

    int Attributes::GetSum() const noexcept
    {
        return m_attSum;
    }



    // ============================================================
    // 2. DERIVED ATTRIBUTES — Implémentation
    // ============================================================

    DerivedAttributes::DerivedAttributes(int mnv, int dpl, int rfx, int dfp, int rp, int rm) noexcept :
        m_mnv(mnv), m_dpl(dpl), m_rfx(rfx), m_dfp(dfp), m_rp(rp), m_rm(rm)
    {
    }

    int DerivedAttributes::MNV() const noexcept { return m_mnv; }
    int DerivedAttributes::DPL() const noexcept { return m_dpl; }
    int DerivedAttributes::RFX() const noexcept { return m_rfx; }
    int DerivedAttributes::DFP() const noexcept { return m_dfp; }
    int DerivedAttributes::RP()  const noexcept { return m_rp; }
    int DerivedAttributes::RM()  const noexcept { return m_rm; }

} // namespace OmniCore::Domain
