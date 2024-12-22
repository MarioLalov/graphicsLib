#include "Sprite.h"

auto Sprite::get_drawable_object() const -> std::shared_ptr<sf::Drawable>
{
    auto ptr =  std::make_shared<sf::Sprite>(m_sprite);
    const auto& globalPos = get_global_position();
    ptr->setPosition(globalPos.x, globalPos.y);

    return ptr;
}

Sprite::Sprite(const std::string& name)
{
    m_name = name;
}

Sprite::Sprite(const std::string& name, std::shared_ptr<sf::Texture> spriteTexture)
{
    m_name = name;
    m_sprite.setTexture(*spriteTexture);
}