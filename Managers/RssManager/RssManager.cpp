#include "RssManager.h"

#include <fstream>

namespace
{
    constexpr auto RSS_TYPE = "type";
    constexpr auto RSS_NAME = "name";

    namespace ImageType
    {
        constexpr auto TYPE_NAME = "image";
        constexpr auto FILE_NAME = "fileName";
        constexpr auto RECT = "rect";
    }
}

void RssManager::Load(std::vector<std::string>& filesToLoadFrom)
{
    for(const auto& file : filesToLoadFrom)
    {
        std::ifstream stream(file);
        nlohmann::json json = nlohmann::json::parse(stream);

        if(!json.is_array())
        {
            //TODO: Handle later
        }

        for(const auto& item : json.items())
        {
            _tryLoadImage(item.value());
        }  
    }
}

auto RssManager::GetImageTexture(const std::string& rssName) const -> std::shared_ptr<sf::Texture>
{
    std::shared_ptr<Image> rss;

    try
    {
        resource_ptr rssPtr = m_loadedRss.at(rssName);
        rss = std::static_pointer_cast<Image>(rssPtr);
    }
    catch(const std::exception& e)
    {
        return nullptr;
    }

    if(!rss)
    {
        return nullptr;
    }

    return rss->texture;
}

auto RssManager::_tryLoadImage(const nlohmann::json& jsonObject) -> bool
{
    if(ImageType::TYPE_NAME != jsonObject[RSS_TYPE])
    {
        return false;
    }

    if(!jsonObject.contains(RSS_NAME))
    {
        throw std::invalid_argument("Missing rss name, which is mandatory!");
    }

    if(!jsonObject.contains(ImageType::FILE_NAME))
    {
        throw std::invalid_argument("Missing fileName key, which is mandatory!");
    }

    if(!jsonObject[RSS_NAME].is_string())
    {
        throw std::invalid_argument("Incorrect rss name value!");
    }

    if(!jsonObject[ImageType::FILE_NAME].is_string())
    {
        throw std::invalid_argument("Incorrect fileName value!");
    }

    const std::string fileName = jsonObject[ImageType::FILE_NAME];
    const std::string rssName = jsonObject[RSS_NAME];

    auto rect = sf::IntRect();
    if(jsonObject.contains(ImageType::RECT) && 4 == jsonObject[ImageType::RECT].size())
    {
        rect.left = jsonObject[ImageType::RECT][0];
        rect.top = jsonObject[ImageType::RECT][1];
        rect.width = jsonObject[ImageType::RECT][2];
        rect.height = jsonObject[ImageType::RECT][3];
    }

    Image image;
    image.texture = std::make_shared<sf::Texture>();
    image.texture->loadFromFile(fileName, rect);
    m_loadedRss[rssName] = std::make_shared<Image>(image);

    return true;
}