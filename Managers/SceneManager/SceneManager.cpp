#include "SceneManager.h"

#include <fstream>

namespace
{
    constexpr auto TYPE = "type";
    constexpr auto NAME = "name";
    constexpr auto POSITION = "position";
    constexpr auto ROTATION = "rotation";
    constexpr auto SCALE = "scale";
    constexpr auto CHILDREN = "children";

    namespace SpriteProperites
    {
        constexpr auto IMAGE_RSS = "image_rss";
    }

    namespace NodeTypes
    {
        constexpr auto NODE = "node";
        constexpr auto SPRITE = "sprite";
    }
}

void SceneManager::Load(std::vector<std::string>& filesToLoadFrom)
{
    for(const auto& file : filesToLoadFrom)
    {
        std::ifstream stream(file);
        nlohmann::json json = nlohmann::json::parse(stream);

        if(json.is_array())
        {
            //TODO: Handle later
        }

        _loadRootNode(json);
    }
}

auto SceneManager::GetCurrentRoot() -> std::shared_ptr<Node>
{
    return *m_curentSelectedScene;
}

bool SceneManager::SelectScene(const std::string& sceneName)
{
    try
    {
        m_curentSelectedScene = &m_loadedScenes.at(sceneName);
    }
    catch(const std::out_of_range&)
    {
        return false;
    }

    return true;
}

void SceneManager::_loadRootNode(const nlohmann::json& jsonObject)
{
    //TODO: add generator for when the name is missing
    auto& rootNode = m_loadedScenes[jsonObject[NAME]];
    rootNode = _loadNode(jsonObject);

    _buildNode(jsonObject, rootNode);
}

void SceneManager::_buildNode(const nlohmann::json& jsonObject, std::shared_ptr<Node> node)
{
    if(jsonObject.contains(POSITION))
    {
        //TODO: add checks for invalid format
        const auto& pos = jsonObject[POSITION];
        node->set_position({pos[0], pos[1]});
    }

    if(jsonObject.contains(ROTATION))
    {
        //TODO: add checks for invalid format
        const auto& angle = jsonObject[ROTATION];
        node->set_rotation(angle);
    }

    if(jsonObject.contains(SCALE))
    {
        //TODO: add checks for invalid format
        const auto& scale = jsonObject[SCALE];
        node->set_scale({scale[0], scale[1]});
    }

    if(jsonObject.contains(CHILDREN))
    {
        const auto& children = jsonObject[CHILDREN];
        for(const auto& child : children)
        {
            auto childNode = _loadNode(child);
            childNode->set_parent(node);

            _buildNode(child, childNode);
        }
    }

}

auto SceneManager::_loadNode(const nlohmann::json& jsonObject) -> std::shared_ptr<Node>
{
    if(NodeTypes::NODE == jsonObject[TYPE])
    {
        const std::string nodeName = jsonObject[NAME];

        return m_factoryManager.CreateNode(nodeName);
    }
    else if(NodeTypes::SPRITE == jsonObject[TYPE])
    {
        const std::string nodeName = jsonObject[NAME];
        const std::string rssName = jsonObject[SpriteProperites::IMAGE_RSS];

        return m_factoryManager.CreateSprite(nodeName, rssName);
    }
    else
    {
        //TODO: handle error
        return nullptr;
    }

}