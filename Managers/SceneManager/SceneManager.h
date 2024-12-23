#pragma once

#include <nlohmann/json.hpp>
#include "../FactoryManager/FactoryManager.h"

class SceneManager
{
public:
    SceneManager(const FactoryManager& factoryManager) : m_factoryManager(factoryManager) {}

public:
    void Load(std::vector<std::string>& filesToLoadFrom);

public:
    auto GetCurrentRoot() -> std::shared_ptr<Node>;
    bool SelectScene(const std::string& sceneName);

private:
    void _loadRootNode(const nlohmann::json& jsonObject);
    
    void _buildNode(const nlohmann::json& jsonObject, std::shared_ptr<Node> node);
    auto _loadNode(const nlohmann::json& jsonObject) -> std::shared_ptr<Node>;

private:
    std::map<std::string, std::shared_ptr<Node>> m_loadedScenes{};

    std::shared_ptr<Node>* m_curentSelectedScene = nullptr;

    const FactoryManager& m_factoryManager;
};