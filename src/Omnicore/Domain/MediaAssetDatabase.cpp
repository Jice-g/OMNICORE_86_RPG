#include <Omnicore/Domain/MediaAssetDatabase.hpp>

#include <stdexcept>
#include <utility>

namespace Omnicore::Domain
{

    MediaAssetDatabase::MediaAssetDatabase(std::filesystem::path basePath, std::filesystem::path brokenAssetPath) :
        m_basePath(std::move(basePath)),
        m_brokenAssetPath(std::move(brokenAssetPath))
    {
    }

    void MediaAssetDatabase::Add(MediaAsset asset)
    {
        const std::string name = asset.Name(); // copie AVANT le move, sinon accès à un objet déplacé
        auto [it, inserted] = m_assets.emplace(name, std::move(asset));
        if (!inserted)
            throw std::invalid_argument("MediaAssetDatabase::Add — nom déjà utilisé : " + name);
    }

    void MediaAssetDatabase::Add(std::string name, MediaAssetFormat format)
    {
        Add(MediaAsset(std::move(name), format));
    }

    bool MediaAssetDatabase::Remove(const std::string& name) noexcept
    {
        return m_assets.erase(name) > 0;
    }

    const MediaAsset& MediaAssetDatabase::Get(const std::string& name) const
    {
        return m_assets.at(name); // std::out_of_range si absent
    }

    std::filesystem::path MediaAssetDatabase::Filepath(const std::string& name) const
    {
        const MediaAsset& asset = Get(name);

        if (asset.Format() == MediaAssetFormat::none)
            return m_brokenAssetPath;

        return m_basePath / (asset.Name() + std::string(ToExtension(asset.Format())));
    }

    bool MediaAssetDatabase::Contains(const std::string& name) const noexcept
    {
        return m_assets.contains(name);
    }

    std::string_view MediaAssetDatabase::ToExtension(MediaAssetFormat format) noexcept
    {
        switch (format)
        {
        case MediaAssetFormat::jpg:  return ".jpg";
        case MediaAssetFormat::png:  return ".png";
        case MediaAssetFormat::gif:  return ".gif";
        case MediaAssetFormat::ico:  return ".ico";
        case MediaAssetFormat::none: return "";
        }
        return "";
    }

}