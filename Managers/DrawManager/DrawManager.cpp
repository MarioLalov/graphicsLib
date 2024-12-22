#include "DrawManager.h"

void DrawManager::Draw(const std::shared_ptr<Node>& node, sf::RenderWindow& window)
{
    if(nullptr == node)
    {
        return;
    }

    if(!node->is_visible())
    {
        return;
    }

    if(auto drawableObject = node->get_drawable_object())
    {
        window.draw(*drawableObject);
    }

    for(const auto& child : node->get_children())
    {
        Draw(child, window);
    }
}