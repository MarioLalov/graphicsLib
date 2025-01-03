#include "Sprite.h"

auto Sprite::get_drawable_object() const -> std::shared_ptr<sf::Drawable>
{
    auto ptr =  std::make_shared<sf::Sprite>(m_sprite);

    const auto& globalPos = get_global_position();
    const auto& pivot = get_pivot();
    const auto& boxSize = get_box_size();

    const auto& origin = sf::Vector2f(globalPos.x + boxSize.x*pivot.x, globalPos.x + boxSize.y*pivot.y);
    ptr->setPosition(origin.x, origin.y);
    ptr->setOrigin(origin.x, origin.y);

    const auto& globalRotation = get_global_rotation();
    ptr->setRotation(globalRotation);

    const auto& globalScale = get_global_scale();
    ptr->setScale(globalScale.x, globalScale.y);

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
    m_boxSize = spriteTexture->getSize();
}