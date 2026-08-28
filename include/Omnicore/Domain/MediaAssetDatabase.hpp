#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

#include <Omnicore/Domain/Entity.hpp>  // MediaAsset, MediaAssetFormat

namespace Omnicore::Domain
{

    /// @class MediaAssetDatabase
    /// @brief Catalogue des MediaAsset connus, indexé par name.
    /// @details
    /// Base passive (même esprit que SkillDatabase) : aucune méthode de
    /// chargement, aucune dépendance vers la persistance. Peuplée depuis
    /// l'extérieur par un futur MediaAssetRepository.
    ///
    /// - Aucune suppression automatique par comptage de référence : le
    ///   nettoyage des assets obsolètes est une action volontaire du MJ.
    /// - Aucun Rename() : renommer = MediaAsset::DuplicateAs() côté appelant,
    ///   puis Add() du résultat ; l'ancien reste en base tant qu'il n'est
    ///   pas explicitement retiré via Remove().
    /// - basePath et brokenAssetPath injectés au constructeur (résolus via
    ///   PlatformPaths/AppPaths — jamais codés en dur, jamais le CWD).
    class MediaAssetDatabase
    {
    public:
        /// @param basePath        dossier des illustrations (assets/MediaAssets)
        /// @param brokenAssetPath chemin de l'icône par défaut ('fa-image-broken'),
        ///                        utilisé quand un asset est en format 'none'
        ///                        (non-hydraté).
        MediaAssetDatabase(std::filesystem::path basePath, std::filesystem::path brokenAssetPath);

        /// @brief Ajoute un asset déjà construit au catalogue.
        /// @throws std::invalid_argument si asset.Name() existe déjà.
        void Add(MediaAsset asset);

        /// @brief Surcharge de confort : construit et ajoute en une étape.
        /// @throws std::invalid_argument si name existe déjà.
        void Add(std::string name, MediaAssetFormat format = MediaAssetFormat::none);

        /// @brief Retire un asset du catalogue (action volontaire, aucune
        ///        vérification d'usage par une Entity).
        /// @return true si l'entrée existait et a été supprimée.
        bool Remove(const std::string& name) noexcept;

        /// @brief Accès en lecture à un asset existant.
        /// @throws std::out_of_range si name est absent.
        [[nodiscard]]
        const MediaAsset& Get(const std::string& name) const;

        /// @brief Chemin physique de l'image associée à name.
        /// @details Si l'asset est en format 'none', retourne brokenAssetPath.
        /// @throws std::out_of_range si name est absent du catalogue.
        [[nodiscard]]
        std::filesystem::path Filepath(const std::string& name) const;

        [[nodiscard]]
        bool Contains(const std::string& name) const noexcept;

    private:
        std::filesystem::path m_basePath;
        std::filesystem::path m_brokenAssetPath;
        std::unordered_map<std::string, MediaAsset> m_assets;

        static std::string_view ToExtension(MediaAssetFormat format) noexcept;
    };

}