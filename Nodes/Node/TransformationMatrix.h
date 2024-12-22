#pragma once

#include "SFML/Graphics.hpp"

class TransformationMatrix
{
public:
    TransformationMatrix() = default;

public:
    auto operator*(const TransformationMatrix& rhs) const -> TransformationMatrix;
    auto operator*(const sf::Vector2f& rhs) const -> sf::Vector2f;

    void addTranslation(const sf::Vector2f& translation);
    void removeTranslation(const sf::Vector2f& translation);

    void addScale(const sf::Vector2f& scale);
    void removeScale(const sf::Vector2f& scale);

    void addRotation(float angle);
    void removeRotation(float angle);

    auto getInverse() -> TransformationMatrix;

    auto getRotation() const -> float;

    void print() const;

private:
    std::array<std::array<float, 3>, 2> m_matrix = {{{1.0f, 0.0f, 0.0f},
                                                     {0.0f, 1.0f, 0.0f}}};
};