#pragma once

#include <nlohmann/json.hpp>
#include "../FactoryManager/FactoryManager.h"

class SceneManager
{
public:
    SceneManager(const FactoryManager& factoryManager) : m_factoryManager(factoryManager) {}

public:
    void Load(std::vector<std::string>& filesToLoadFrom);
    auto GetRootNode() -> std::shared_ptr<Node>;

private:
    void _loadRootNode(const nlohmann::json& jsonObject);
    
    void _buildNode(const nlohmann::json& jsonObject, std::shared_ptr<Node> node);
    auto _loadNode(const nlohmann::json& jsonObject) -> std::shared_ptr<Node>;

private:
    std::map<std::string, std::shared_ptr<Node>> m_loadedScenes{};
    std::string m_currentSelectedScene{};

    const FactoryManager& m_factoryManager;
};