#include "Node.h"
#include <iostream>

auto Node::get_drawable_object() const -> std::shared_ptr<sf::Drawable>
{  
    return nullptr;
}

void Node::set_parent(const std::shared_ptr<Node> node)
{
    m_parent = node;
    m_parent->add_child(shared_from_this());

    m_transformationMatrix = m_parent->builTransformationMatrix();
}

void Node::add_child(const std::shared_ptr<Node> node)
{
    //TODO: check if node is already present
    m_children.push_back(node);
}

auto Node::builTransformationMatrix() const -> TransformationMatrix
{
    auto result = m_transformationMatrix;

    // add position translation
    result.addTranslation(m_localPosition);
    result.addScale(m_localScale);  
    result.addRotation(m_localRotation*(M_PI/180));

    return result;
}

void Node::updateTransformation(const TransformationMatrix& transformationToApply)
{
    // TODO: remove from callback to fix possible multicalls
    m_transformationMatrix = transformationToApply;
    std::cout << m_name << std::endl;
    m_transformationMatrix.print();
    std::cout << "------------------------" << std::endl << std::endl;

    if(m_children.empty())
    {
        return;
    }

    auto updatedTransformation = m_transformationMatrix;

    // add postiion translation
    updatedTransformation.addTranslation(m_localPosition);
    updatedTransformation.addScale(m_localScale);  
    updatedTransformation.addRotation(m_localRotation*(M_PI/180));

    // update for all children
    for(const auto& child : m_children)
    {
        child->updateTransformation(updatedTransformation);
    }
}

void Node::set_position(const sf::Vector2f& position)
{
    m_localPosition = position;
    updateTransformation(m_transformationMatrix);
}

void Node::set_scale(const sf::Vector2f& scale)
{
    m_localScale = scale;
    updateTransformation(m_transformationMatrix);
}

void Node::set_rotation(float angle)
{
    m_localRotation = angle;
    updateTransformation(m_transformationMatrix);
}

void Node::set_pivot(const sf::Vector2f& pivot)
{
    // return to 0.0 pivot position
    // m_transformationMatrix.removeTranslation({-m_pivot.x*m_boxSize.x, -m_pivot.y*m_boxSize.y});

    m_pivot = pivot;

    // apply new pivot positon
    // m_transformationMatrix.addTranslation({-m_pivot.x*m_boxSize.x, -m_pivot.y*m_boxSize.y});
}

void Node::set_visibility(bool visibility)
{
    m_visibility = visibility;
}

void Node::set_box_size(const sf::Vector2f& boxSize)
{
    m_boxSize = boxSize;
}

auto Node::get_name() const -> std::string
{
    return m_name;
}

auto Node::get_position() const -> sf::Vector2f
{
    return m_localPosition;
}

auto Node::get_global_position() const -> sf::Vector2f
{
    return m_transformationMatrix*m_localPosition;
}

auto Node::get_scale() const -> sf::Vector2f
{
    return m_localScale;
}

auto Node::get_global_scale() const -> sf::Vector2f
{
    return m_transformationMatrix*m_localScale;
}

auto Node::get_rotation() const -> float
{
    return m_localRotation;
}

auto Node::get_global_rotation() const -> float
{
    return (m_transformationMatrix.getRotation()*(180/M_PI)) + m_localRotation;
}

auto Node::get_box_size() const -> sf::Vector2f
{
    return m_boxSize;
}

auto Node::get_pivot() const -> sf::Vector2f
{
    return m_pivot;
}

auto Node::is_visible() const -> bool
{
    return m_visibility;
}

auto Node::get_parent() const -> node_ptr
{
    return m_parent;
}

auto Node::get_children() const -> const std::vector<node_ptr>&
{
    return m_children;
}

auto Node::get_child(const std::string& name) const -> node_ptr
{
    for(const auto& child : m_children)
    {
        if(child->get_name() == name)
        {
            return child;
        }
    }

    return nullptr;
}