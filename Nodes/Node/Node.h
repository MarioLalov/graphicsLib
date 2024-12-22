#pragma once

#include <memory>
#include <vector>
#include <string>
#include "TransformationMatrix.h"

class Node : public std::enable_shared_from_this<Node>
{

using node_ptr = std::shared_ptr<Node>;

public:
    Node() = default;
    Node(const std::string &name) : m_name(name) {}
    // TODO: Add desturctor

public:
    virtual auto get_drawable_object() const -> std::shared_ptr<sf::Drawable>;
    
public:
    void set_pivot(const sf::Vector2f& pivot);
    void set_visibility(bool visibility);
    void set_box_size(const sf::Vector2f& boxSize);

    void set_position(const sf::Vector2f& position);
    void set_rotation(float angle);

public:
    void set_parent(const std::shared_ptr<Node> node);
    void add_child(const std::shared_ptr<Node> node);

public:
    auto get_name() const -> std::string;

    auto get_position() const -> sf::Vector2f;
    auto get_global_position() const -> sf::Vector2f;

    auto get_rotation() const -> float;
    auto get_global_rotation() const -> float;

    auto get_box_size() const -> sf::Vector2f;
    auto get_pivot() const -> sf::Vector2f;
    auto is_visible() const -> bool;

public:
    auto get_parent() const -> node_ptr;
    auto get_children() const -> const std::vector<node_ptr>&;
    auto get_child(const std::string& name) const -> node_ptr;

private:
    void updateTransformation(const TransformationMatrix& transformationToApply);
    auto builTransformationMatrix() const -> TransformationMatrix;

protected:
    bool m_visibility = true;

    sf::Vector2f m_boxSize{0.0f, 0.0f};

    sf::Vector2f m_pivot{0.0f, 0.0f};

    sf::Vector2f m_localPosition{0.0f, 0.0f};
    float m_localRotation{0.0f};

    TransformationMatrix m_transformationMatrix;

protected:
    std::string m_name = "";

    node_ptr m_parent = nullptr;
    std::vector<node_ptr> m_children;
};