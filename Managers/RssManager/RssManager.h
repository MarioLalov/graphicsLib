#pragma once

#include "Resources.h"
#include <nlohmann/json.hpp>

using resource_ptr = std::shared_ptr<Resource>;

class RssManager
{
public:
    void Load(std::vector<std::string>& filesToLoadFrom);
    auto GetImageTexture(const std::string& rssName) const -> std::shared_ptr<sf::Texture>;

private:
    auto _tryLoadImage(const nlohmann::json& jsonObject) -> bool;

private:
    std::map<std::string,resource_ptr> m_loadedRss;
};