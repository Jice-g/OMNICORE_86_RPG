#pragma once


namespace Omnicore::Domain
{

    // ============================================================
    // ENUMS
    // ============================================================

    /// @enum e_Controller
    /// @brief Définit un comparateur d'attribut pour les Skills (voir Skills.
    /// @details
    /// - PHY, DEX, ESP, PER, SOC, CHA, POU, NEU
    enum eAttribute {
        PHY,
        DEX,
        ESP,
        PER,
        SOC,
        CHA,
        POU,
        NEU
    };



    // ============================================================
    // 1. ATTRIBUTES — Attributs de base (PHY, DEX, ESP, PER, SOC…)
    // ============================================================

    /// @class Attributes
    /// @brief Représente les huit attributs de base du système 8/6 CORE.
    ///
    /// Chaque attribut correspond à un code officiel du manuel :
    /// - PHY : Physique
    /// - DEX : Dextérité
    /// - ESP : Esprit
    /// - PER : Perception
    /// - SOC : Sociabilité
    /// - CHA : Chance
    /// - POU : Pouvoir
    /// - NEU : Neuro-connexion
    ///
    /// La classe conserve également la somme totale des attributs (m_attSum),
    /// utilisée pour le contrôle du pool d’attributs.
    class Attributes
    {
    public:

        /// @brief Constructeur par défaut (tous les attributs à 0).
        Attributes() = default;

        /// @brief Constructeur complet.
        /// @param physique Valeur initiale de PHY.
        /// @param dexterite Valeur initiale de DEX.
        /// @param esprit Valeur initiale de ESP.
        /// @param perception Valeur initiale de PER.
        /// @param sociabilite Valeur initiale de SOC.
        /// @param chance Valeur initiale de CHA.
        /// @param pouvoir Valeur initiale de POU.
        /// @param neuro Valeur initiale de NEU.
        /// 
        Attributes(int physique, int dexterite, int esprit, int perception, int sociabilite, int chance,
            int pouvoir, int neuro) noexcept;


        // --- ACCESSEURS (codes du manuel) ---

        /// @brief PHY : Physique (force, constitution, vigueur).
        int PHY() const noexcept;

        /// @brief DEX : Dextérité (agilité, coordination).
        int DEX() const noexcept;

        /// @brief ESP : Esprit (logique, intelligence, mémoire).
        int ESP() const noexcept;

        /// @brief PER : Perception (vigilance, intuition, sens).
        int PER() const noexcept;

        /// @brief SOC : Sociabilité (charisme, influence, empathie).
        int SOC() const noexcept;

        /// @brief CHA : Chance (hasard, synchronicité, destin).
        int CHA() const noexcept;

        /// @brief POU : Pouvoir (énergie, magie, psionique).
        int POU() const noexcept;

        /// @brief NEU : Neuro-connexion (implants, cyberespace).
        int NEU() const noexcept;

        /// @brief Retourne la somme interne des attributs.
        int Sum() const noexcept { return m_attSum; }


        /// @brief Assigne en une seule opération les huit attributs.
        /// @param physique Nouvelle valeur de PHY.
        /// @param dexterite Nouvelle valeur de DEX.
        /// @param esprit Nouvelle valeur de ESP.
        /// @param perception Nouvelle valeur de PER.
        /// @param sociabilite Nouvelle valeur de SOC.
        /// @param chance Nouvelle valeur de CHA.
        /// @param pouvoir Nouvelle valeur de POU.
        /// @param neuro Nouvelle valeur de NEU.
        void Set(int physique, int dexterite, int esprit, int perception, int sociabilite, int chance,
            int pouvoir, int neuro) noexcept;

    private:

        /// @brief Valeur de PHY.
        int m_physique = 0;

        /// @brief Valeur de DEX.
        int m_dexterite = 0;

        /// @brief Valeur de ESP.
        int m_esprit = 0;

        /// @brief Valeur de PER.
        int m_perception = 0;

        /// @brief Valeur de SOC.
        int m_sociabilite = 0;

        /// @brief Valeur de CHA.
        int m_chance = 0;

        /// @brief Valeur de POU.
        int m_pouvoir = 0;

        /// @brief Valeur de NEU.
        int m_neuro = 0;

        /// @brief Somme totale des huit attributs.
        int m_attSum = 0;

        /// @brief Recalcule la somme interne des attributs.
        void SetSum() noexcept;

        /// @brief Accède à la somme interne des attributs.
        int GetSum() const noexcept;
    };




    // ============================================================
    // 2. DERIVED ATTRIBUTES — Attributs dérivés (MNV, DPL, RFX…)
    // ============================================================

    /// @class DerivedAttributes
    /// @brief Représente les attributs dérivés calculés à partir des attributs de base.
    ///
    /// Codes officiels :
    /// - MNV : Manœuvre
    /// - DPL : Déplacement
    /// - RFX : Réflexes
    /// - DFP : Défense passive
    /// - RP  : Stress physique
    /// - RM  : Stress mental
    /// 
    class DerivedAttributes
    {
    public:

        /// @brief Constructeur par défaut.
        DerivedAttributes() = default;

        /// @brief Constructeur complet.
        /// @param mnv Valeur de MNV.
        /// @param dpl Valeur de DPL.
        /// @param rfx Valeur de RFX.
        /// @param dfp Valeur de DFP.
        /// @param sp Valeur de SP.
        /// @param sm Valeur de SM.
        /// 
        DerivedAttributes(int mnv, int dpl, int rfx, int dfp, int sp, int sm) noexcept;

        /// @brief MNV : Manœuvre.
        int MNV() const noexcept;

        /// @brief DPL : Déplacement.
        int DPL() const noexcept;

        /// @brief RFX : Réflexes.
        int RFX() const noexcept;

        /// @brief DFP : Défense passive.
        int DFP() const noexcept;

        /// @brief SP : Stress physique.
        int RP() const noexcept;

        /// @brief SM : Stress mental.
        int RM() const noexcept;

    private:

        int m_mnv = 0;
        int m_dpl = 0;
        int m_rfx = 0;
        int m_dfp = 0;
        int m_rp = 0;
        int m_rm = 0;
    };
}
