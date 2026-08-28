#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <span>
#include <cstdint>


#include <Omnicore/Domain/Entity.hpp>
#include <Omnicore/Domain/Attributes.hpp>


namespace Omnicore::Domain
{
    // ============================================================
    // ENUMS
    // ============================================================

    /// @enum e_Controller
    /// @brief Définit qui contrôle l'acteur.
    /// @details
    /// - PLAYER : contrôlé par un joueur humain  
    /// - GAME_MASTER : contrôlé par le MJ  
    /// - IA : contrôlé par l'intelligence artificielle  
    enum class e_Controller
    {
        PLAYER,
        GAME_MASTER,
        IA
    };

    /// @enum eInjurySeverity
    /// @brief Niveau de sévérité d'une blessure.
    /// @details
    /// - LEGERE : malus -1  
    /// - MODEREE : malus -2  
    /// - GRAVE : malus -4  
    /// - CRITIQUE : malus -8  
    enum class eInjurySeverity : uint8_t
    {
        LEGERE,
        MODEREE,
        GRAVE,
        CRITIQUE
    };

    // ============================================================
    // MORPHOLOGY
    // ============================================================

    /// @struct Morphology
    /// @brief Décrit la morphologie d’un acteur.
    /// @details
    /// - species : nom d’espèce (Humain, Elfe, Cyborg…)  
    /// - sizeModifier : modificateur de Taille  
    /// - massModifier : modificateur de Corpulence  
    /// pas d'encapsulation : variable strcuturée
    class Morphology
    {
    public:
        Morphology(std::string species, int sizemod = 0, int massmod = 0);
        /// @brief Constructeur par défaut.
        Morphology() = default;

        std::string Species() const;
        int SizeModifier() const;  
        int MassModifier() const;  

        void SetSpecies(std::string spe);
        void SetSizeMod(int sizemod);  //< Modificateur de taille [-6..+6] humain :[-1..+1]
        void SetMassMod(int massmod);  //< Modificateur de corpulence [-6..+6] humain :[-1..+1]

    private:
        std::string m_species;
        int m_sizeModifier;  
        int m_massModifier;  
    };

    // ============================================================
    // INJURY
    // ============================================================

    /// @class Injury
    /// @brief Représente une blessure reçue par un acteur.
    /// @details
    /// Une blessure possède :
    /// - un libellé (tag)  
    /// - une sévérité (eInjurySeverity)  
    /// - un malus automatique (penalty)  
    class Injury
    {
    public:
        /// @brief Constructeur par défaut.
        Injury() = default;

        /// @brief Constructeur complet.
        /// @param tag Libellé de la blessure.
        /// @param severity Niveau de sévérité.
        /// @details Le malus est automatiquement calculé.
        Injury(const std::string& tag, eInjurySeverity severity) noexcept;


        /// @brief Retourne le libellé de la blessure.
        const std::string& Tag() const noexcept;

        /// @brief Retourne la sévérité de la blessure.
        eInjurySeverity Severity() const noexcept;

        /// @brief Retourne la sévérité de la blessure sous forme de string.
        std::string SeverityStr() const noexcept;

        /// @brief Retourne le malus associé.
        int Penalty() const noexcept;

    private:
        std::string m_tag;                 ///< Libellé de la blessure.
        eInjurySeverity m_severity;       ///< Sévérité de la blessure.
        int m_penalty = -1;                ///< Malus associé.

        /// @brief Calcule le malus en fonction de la sévérité.
        /// @param s Sévérité.
        /// @return Malus entier.
        static int ComputePenalty(eInjurySeverity s) noexcept;
    };


    // ============================================================
    // ACTOR
    // ============================================================

    /// @class Actor
    /// @brief Représente un acteur du jeu (PJ, PNJ, créature).
    /// @details
    /// Un Actor possède :
    /// - un nom (hérité de Entity)  
    /// - des attributs de base (Attributes)  
    /// - des attributs dérivés (DerivedAttributes)  
    /// - une morphologie (Morphology)  
    /// - un contrôleur (joueur, MJ, IA)  
    /// - une puissance totale (Power)  
    /// - un niveau (Level)  
    /// - une liste de blessures (Injury)  
    class Actor : public Entity
    {
    public:

        /// @brief Constructeur par défaut.
        Actor() = default;

        /// @brief Constructeur avec nom et contrôleur.
        /// @param name Nom de l'acteur.
        /// @param controller Type de contrôleur.
        explicit Actor(const std::string& name, e_Controller controller);

        /// @brief Destructeur virtuel.
        virtual ~Actor() = default;

        // ------------------------------------------------------------
        // ACCESSEURS
        // ------------------------------------------------------------

        /// @brief Retourne le contrôleur de l'acteur.
        e_Controller Controller() const noexcept;

        /// @brief Retourne les attributs de base.
        const Attributes& GetAttributes() const noexcept;

        /// @brief Retourne les attributs dérivés.
        const DerivedAttributes& GetDerivedAttributes() const noexcept;

        /// @brief Retourne la morphologie de l'acteur.
        const Morphology& GetMorphology() const noexcept;

        /// @brief Retourne la puissance totale.
        int32_t Power() const noexcept;

        /// @brief Retourne le niveau total.
        int32_t Level() const noexcept;

        /// @brief Retourne la liste des blessures.
        /// @return Un span constant sur les blessures.
        /// <i> Si du code appelle GetInjuries(), garde le span, puis appelle AddInjury() derrière,
        /// le vector peut réallouer et le span devient un pointeur mort.
        /// L'usage de GetInjuries doit "appeler et consommer immédiatement"
        std::span<const Injury> GetInjuries() const noexcept;

        // ------------------------------------------------------------
        // SETTEURS
        // ------------------------------------------------------------

        /// @brief Modifie les attributs de base.
        void SetAttributes(int physique, int dexterite, int esprit, int perception,
                           int sociabilite, int chance, int pouvoir, int neuro);

        /// @brief Modifie le contrôleur.
        void SetController(e_Controller controller) noexcept;

        /// @brief Modifie la morphologie.
        void SetMorphology(const Morphology& m) noexcept;

        /// @brief Modifie la puissance totale.
        /// @details
        /// - Power doit rester >= somme des attributs  
        /// - Retourne false si la règle n’est pas respectée  
        bool SetPower(int32_t power) noexcept;

        /// @brief Ajoute une blessure.
        /// @return true si ajout réussi.
        /// <i> le vector peut avoir réalloué la mémoire
        bool AddInjury(const std::string& tag, eInjurySeverity severity) noexcept;

        /// @brief Supprime une blessure par index.
        /// @return true si suppression réussie.
        ///<i> le vector peut avoir réalloué la mémoire
        bool EraseInjury(int index) noexcept;

    protected:
        e_Controller m_controller = e_Controller::PLAYER;   ///< Contrôleur de l'acteur.
        Morphology m_morphology;                            ///< Morphologie.
        Attributes m_attributes;                            ///< Attributs de base.
        DerivedAttributes m_derivedAttributes;              ///< Attributs dérivés.
        int32_t m_power = 0;                                ///< Puissance totale.
        int32_t m_level = 0;                                ///< Niveau total.
        std::vector<Injury> m_injuries;                     ///< Blessures reçues.
    };
}
