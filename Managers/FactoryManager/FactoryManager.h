#pragma once
#include "../RssManager/RssManager.h"
#include "../../Nodes/Node/Node.h"
#include "../../Nodes/Sprite/Sprite.h"

class FactoryManager
{
public:
    FactoryManager(const RssManager& rssManager) : m_rssManager(rssManager) {}
    
public:
    auto CreateNode(const std::string& name) const -> std::shared_ptr<Node>;
    auto CreateSprite(const std::string& name, const std::string& rssName) const -> std::shared_ptr<Node>;

private:
    std::vector<std::shared_ptr<Node>> m_scenes;
    const RssManager& m_rssManager;
};