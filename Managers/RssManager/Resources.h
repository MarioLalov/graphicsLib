#pragma once

#include "SFML/Graphics.hpp"

struct Resource
{
};

struct Image : public Resource
{
    std::shared_ptr<sf::Texture> texture;
};

struct Video : public Resource
{

};

struct Sound : public Resource
{
};

