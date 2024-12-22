#pragma once

#include "SFML/Graphics.hpp"
#include "../../Nodes/Node/Node.h"

class DrawManager
{
public:
    void Draw(const std::shared_ptr<Node>& node, sf::RenderWindow& window);
};