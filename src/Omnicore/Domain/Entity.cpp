

#include <Omnicore/Domain/Entity.hpp>


namespace Omnicore::Domain
{

/*****************************  MediaAsset *******************************************/


    MediaAsset::MediaAsset(std::string name, MediaAssetFormat format) :
        m_name(std::move(name)),
        m_format(format)
    {

    }

    MediaAsset::MediaAsset(MediaAsset const& asset, std::string newname) : m_name(std::move(newname)), m_format(asset.Format())
    {

    }

    const std::string& MediaAsset::Name() const noexcept
    {
        return m_name;
    }

    MediaAssetFormat MediaAsset::Format() const noexcept
    {
        return m_format;
    }

    void MediaAsset::SetFormat(MediaAssetFormat format)
    {
        m_format = format;
    }

    [[nodiscard]]
    MediaAsset MediaAsset::DuplicateAs(std::string newname) const noexcept
    {
        return MediaAsset(*this, std::move(newname));
    }


/******************************** Entity **********************************************/

    std::uint64_t  Entity::s_objectCounter = 0;   // compteur en mémoire, réinitialisé à chaque lancement.


    Entity::Entity(std::string name): m_instanceId(GenerateInstanceId(&s_objectCounter)), m_name(std::move(name)) // move évitera la copie de (name) entre les constructeurs
    {
        m_description.fill("");
        m_tags.fill("");
    }

    Entity::Entity(std::string instanceId, std::string name) : m_instanceId(std::move(instanceId)), m_name(std::move(name))
    {
        m_description.fill("");
        m_tags.fill("");
    }


    std::string Entity::GenerateInstanceId(uint64_t* counter)
    {
        // Rappel : epoch est l'origine Unix 01/01/1970
        auto now = std::chrono::system_clock::now();
        auto epoch = std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch() ).count();

        return std::to_string(++(*counter)) + "_" + std::to_string(epoch);
    }




    /// <@brief : accesseurs const
    /// 
    /// @return la propriété concernée : m_instanceID, m_name, m_description, m_tags

    std::string Entity::InstanceID() const noexcept     // Un getteur est trivial et ne doit jamais lancer d’exception.
    {
        return m_instanceId;
    }

    const std::string& Entity::Name() const noexcept
    {
        return m_name;
    }

    std::span<const std::string> Entity::Description() const noexcept
    {
        return m_description;
    }

    std::span<const std::string> Entity::Tags() const noexcept
    {
        return m_tags;
    }

    MediaAsset* Entity::Picture() const noexcept
    {
        return m_picture;
    }



    /// <@brief : setteur 
    /// 

    void Entity::ResetName(const std::string& newname)           // voir si noexcept est recommandé ou pas
    {
        m_name = newname;
    }

    void Entity::SetDescription(std::span<const std::string> description)
    {
        const size_t count = std::min(description.size(), m_description.size());

        for (size_t i = 0; i < count; ++i)
            m_description[i] = description[i];

        for (size_t i = count; i < m_description.size(); ++i)   // nettoyage des lignes non utilisées
            m_description[i].clear();
    }

    void Entity::SetTags(std::span<const std::string> tags)
    {
        const size_t count = std::min(tags.size(), m_tags.size());

        for (size_t i = 0; i < count; ++i)
            m_tags[i] = tags[i];

        for (size_t i = count; i < m_tags.size(); ++i)          // nettoyage des lignes non utilisées
            m_tags[i].clear();                                  
    }

    void Entity::SetPicture(MediaAsset* asset)
    {
        m_picture = asset;
    };

}


/* Nota : 'noexcept' indique qu’une fonction ne lancera jamais d’exception.  
Cela permet au compilateur d’optimiser le code, améliore la sûreté, et clarifie l’intention.
À utiliser sur les fonctions triviales (getters, setters, destructeurs, moves), mais pas sur les fonctions susceptibles d’échouer.*/