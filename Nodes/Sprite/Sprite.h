#pragma once

#include "../Node/Node.h"

class Sprite : public Node
{
public:
    Sprite() = default;

public:
    auto get_drawable_object() const -> std::shared_ptr<sf::Drawable> override;

public:
    Sprite(const std::string& name);
    Sprite(const std::string& name, std::shared_ptr<sf::Texture> spriteTexture);

private:
    sf::Sprite m_sprite;

public:
    friend class FactoryManager;
};
