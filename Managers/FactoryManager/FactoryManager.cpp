#include "FactoryManager.h"

auto FactoryManager::CreateNode(const std::string& name) const -> std::shared_ptr<Node>
{
    return std::make_shared<Node>(name);   
}

auto FactoryManager::CreateSprite(const std::string& name, const std::string& rssName) const -> std::shared_ptr<Node>
{
    const auto texture = m_rssManager.GetImageTexture(rssName);
    if(texture)
    {
        return std::make_shared<Sprite>(name, texture);
    }
    else
    {
        return std::make_shared<Sprite>(name);
    }
}