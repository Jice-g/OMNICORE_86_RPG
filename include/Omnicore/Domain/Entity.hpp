#pragma once

#include <iostream>
#include <string>
#include <array>
#include <span>
#include <cstdint>
#include <atomic>
#include <chrono>


namespace Omnicore::Domain
{

 constexpr auto MAX_ENTITY_DESCRIPT =16;
 constexpr auto MAX_ENTITY_TAGS = 3;

/* ------- MEDIA ASSET --------------- */
    
/// @enum MediaAssetFormat
/// @brief Identifie des types d'illustration média image ou son
/// @details
/// - jpg, png, gif, ico
/// > uint8_t pour un stockage binaire éventuel
    enum class MediaAssetFormat : uint8_t {
        jpg,
        png,
        gif,
        ico,
        none
    };


    /// @class MediaAsset
    /// @brief Illustration associée à une Entity, référencée via MediaAssetDatabase.
    /// @details
    /// - name   : identifiant unique, immuable (clé dans MediaAssetDatabase)
    /// - format : mutable via SetFormat() — changer l'image ne change pas l'identité de l'asset
    ///
    /// Value object immuable. Aucune connaissance de sa propre persistance :
    /// création suppression sont des responsabilités de MediaAssetDatabase, pas de MediaAsset.
    /// Aucune méthode de chargement (pas de load()/open()) — délégué à AssetRepository (phase Persistence).
    class MediaAsset
    {

    public:

        /// @brief Constructeur standard avec nom et format
        /// @param name : nom du asset
        /// @param format : format de l'image
        /// @details
        /// Utilisé quand on connait le nom et le format
        /// On ne peut renseigner que le nom, le format sera 'none'
        /// Car changer le format n'oblige pas créer une autre instance
        /// comme c'est le cas avec le nom (qui est la clé dans la base MediaAssetDatabase)
        /// un format 'none', c'est une instance "non-hydratée', le AssetRepository ne chargera pas d'image
        /// il mettra une icone par défaut type 'fa-image-broken' (idem quand on ne la retrouve pas ou rencontre un problème)
        explicit MediaAsset(std::string name, MediaAssetFormat format = MediaAssetFormat::none);

        /// @brief Constructeur de "duplication" (recyclage d'illustration existante).
        /// @param asset : MediaAsset source, dont le format est repris tel quel.
        /// @param newname : nom du nouvel asset.
        /// @details
        /// On peut directement réutiliser un Media en changeant le nom.
        /// Ce n'est pas formellement un 'copy constructor' mais une surcharge pour duplication
        /// Ceci est conforme avec Rappel : std::unordered_map avec clé name(string) et MediaAsset en objet collecté
        MediaAsset(MediaAsset const& asset, std::string newname);

        const std::string& Name() const noexcept;
        MediaAssetFormat Format() const noexcept;

        /// @brief Duplication déléguée à la classe elle-même (this)
        /// @param newname : nom du nouvel asset.
        /// <i> cpp : initialisation : m_name(std::move(newname)), m_format(asset.Format())
        [[nodiscard]]
        MediaAsset DuplicateAs(std::string newname) const noexcept;

        void SetFormat(MediaAssetFormat format);

    private:
        std::string m_name;
        MediaAssetFormat  m_format;

    };        


/// @class Entity
/// @brief Représente une entity en jeu (PJ, PNJ, créature, ustencil, arme, armure, bourse...).
/// @details
/// Une Entity possède :
/// - un nom 
/// - un compteur d'instances static
/// - un identifiant unique génré avec objCounter
/// - une description (16 lignes max)
/// - des étiquettes (tags) : 3ax 3.
/// - une puissance totale
    class Entity
    {
    public:
        /// @brief Constructeur par défaut.
        Entity() = default;                     // 	Génère une méthode spéciale automatiquement Constructeur ("pré-hydratation").

        /// @brief Constructeur avec nom.
        /// @param name Nom de l'acteur.
        explicit Entity(std::string name);      // Pas de conversion implicite du Constructeurs à un seul argument.

        // Hydratation depuis une sauvegarde (InstanceId déjà existant, ne JAMAIS le régénérer)
        explicit Entity(std::string instanceId, std::string name);

        /// @brief Destructeur virtuel.
        virtual ~Entity() = default;            // Sans destructeur virtuel par défaut le comportement risque d'être indéfini.


        /// @brief Génère l'instanceId à partir de system_clock
        /// @return Valeur affecté à m_instanceID
        /// @details
        /// - m_instanceId = incrémentation de objectCounter + nombre de millisecondes depuis l’époque Unix (1/1/1970).
        static std::string GenerateInstanceId(uint64_t* counter);

                                               
        /// @brief Retourne l'immatriculation non modifiables (const)
        /// @return Valeur de m_instanceID.
        [[nodiscard]]                           // La valeur doit être utilisée, sinon l'appel n'a aucun intéret
        std::string InstanceID() const noexcept;

        /// @brief Retourne le nom de l'entité non modifiables (const)
        /// @return Référence constante vers m_name.
        [[nodiscard]]                           // La valeur doit être utilisée, sinon l'appel n'a aucun intéret
        const std::string& Name() const noexcept;

        /// @brief Retourne la description de l'entité non modifiables (const)
        /// @return Référence constante vers m_description.
        [[nodiscard]]
        std::span<const std::string> Description() const noexcept;

        /// @brief Retourne les étiquettes de l'entité non modifiables (const)
        /// @return Référence constante vers m_tags.
        [[nodiscard]]
        std::span<const std::string> Tags() const noexcept;

        /// @brief le MediaAsset
        /// @return RPointeur vers l'objet MediaAsset
        [[nodiscard]]
        MediaAsset* Picture() const noexcept;


        /// @brief les setteurs permettent de définir ou redéfinir les attributs de l'entité :
        /// @details
        /// - le nom 
        /// - la description
        /// - les éttiquettes
       
        /// @param name Nom de l'acteur.
        void ResetName(const std::string& newname);
        
        /// @param description : description de l'acteur.
        void SetDescription(std::span<const std::string> description); ///<!> Qu'importe la longueur, il ne lira que les 16 premièrs lignes (voir cpp)
        
        /// @param tags Etiquettes de l'acteur.
        void SetTags(std::span<const std::string> m_tags); /// <!> Qu'importe la longueur, il ne lira que les 3 premières lignes (voir cpp)

        /// @param asset est un objet MediaAsset
        void SetPicture(MediaAsset* asset);

    protected :
        /// @brief compte le nombre d'entités instanciés.
        static std::uint64_t s_objectCounter;        ///< Le corps .cpp des fonctions Constructeurs incrémente ce compteur static                                                  
                                                

    private:
        std::string m_instanceId;               ///< Immatriculation automatique de l'objet, à partir du compteur statique
                                                  ///< Généré une seule fois, puis figé pour la vie de l'objet  

        std::string m_name;                     ///< Tout objet à un nom
        std::array<std::string, MAX_ENTITY_DESCRIPT> m_description;  ///< Description de 16 lignes maximum
        std::array<std::string, MAX_ENTITY_TAGS> m_tags;      ///< Le modèle de donnée prévoit 3 éttiquettes possibles : catégorie, rôle, gabarit
        MediaAsset* m_picture=nullptr;   ///< lien vers une illustration


    };
}

/* Nota : std::span est une vue légère, non possédante, sur une séquence contiguë d’éléments.
Il remplace avantageusement les pointeurs nus et les tableaux C en apportant la sécurité (taille connue), la flexibilité (accepte vector, array, C-array, initializer_list), et la lisibilité.
Dans OmniCore, il permet de recevoir des descriptions ou tags de longueur variable tout en stockant un nombre fixe d’éléments dans l’objet.
*/