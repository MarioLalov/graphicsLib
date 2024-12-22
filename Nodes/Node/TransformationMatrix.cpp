#include "TransformationMatrix.h"
#include <iostream>
#include <cmath>
// (a b c) (j k l)   (aj+bm ak+bn al+bo+c)
// (d e f) (m n o) = (dj+em dk+en dl+oe+f)
// (0 0 1) (0 0 1)   (0     0           1)

static auto roundFloat(float f, uint16_t decimalPoint = 7) -> float
{
    static auto ROUNDING_BASE = std::pow(10.0f, decimalPoint);
    return std::round(f*ROUNDING_BASE) / ROUNDING_BASE;
}

auto TransformationMatrix::operator*(const TransformationMatrix& rhs) const -> TransformationMatrix
{
    const auto& lhs = *this;
    
    TransformationMatrix result;
    // multiply scaling and rotating part
    for (size_t i = 0; i < 2; i++) 
    {
        for (size_t j = 0; j < 3; j++) 
        {
            result.m_matrix[i][j] = 0;

            for (size_t k = 0; k < 2; k++) 
            {
                result.m_matrix[i][j] += roundFloat(lhs.m_matrix[i][k] * rhs.m_matrix[k][j]);
            }
        }
    }

    // add translation part
    result.m_matrix[0][2] += lhs.m_matrix[0][2];
    result.m_matrix[1][2] += lhs.m_matrix[1][2];

    return result;
}

// (a b c)(g)   (ag+bh+c)
// (d e f)(h) = (dg+eh+f)
// (0 0 1)(1)   (1      )

auto TransformationMatrix::operator*(const sf::Vector2f& rhs) const -> sf::Vector2f
{
    const auto& lhs = *this;

    sf::Vector2f result;
    result.x = lhs.m_matrix[0][0]*rhs.x + lhs.m_matrix[0][1]*rhs.y + lhs.m_matrix[0][2];
    result.y = lhs.m_matrix[1][0]*rhs.x + lhs.m_matrix[1][1]*rhs.y + lhs.m_matrix[1][2];

    return result;
}

void TransformationMatrix::addTranslation(const sf::Vector2f& translation)
{
    this->m_matrix[0][2] += translation.x;
    this->m_matrix[1][2] += translation.y;
}

void TransformationMatrix::removeTranslation(const sf::Vector2f& translation)
{
    this->m_matrix[0][2] -= translation.x;
    this->m_matrix[1][2] -= translation.y;
}

void TransformationMatrix::addScale(const sf::Vector2f& scale)
{
    TransformationMatrix scalation;
    scalation.m_matrix[0][0] = scale.x;
    scalation.m_matrix[1][1] = scale.y;

    m_matrix = (scalation*(*this)).m_matrix;
}

void TransformationMatrix::removeScale(const sf::Vector2f& scale)
{
    TransformationMatrix deScalation;
    deScalation.m_matrix[0][0] = (1.0f/scale.x);
    deScalation.m_matrix[1][1] = (1.0f/scale.y);

    m_matrix = (deScalation*(*this)).m_matrix;
}

void TransformationMatrix::addRotation(float angle)
{
    TransformationMatrix rotation;
    rotation.m_matrix[0][0] = std::cos(angle);
    rotation.m_matrix[0][1] = -std::sin(angle);
    rotation.m_matrix[1][0] = std::sin(angle);
    rotation.m_matrix[1][1] = std::cos(angle);

    m_matrix = (rotation*(*this)).m_matrix;
}

void TransformationMatrix::removeRotation(float angle)
{
    TransformationMatrix rotation;
    rotation.m_matrix[0][0] = std::cos(angle);
    rotation.m_matrix[0][1] = std::sin(angle);
    rotation.m_matrix[1][0] = -std::sin(angle);
    rotation.m_matrix[1][1] = std::cos(angle);

    m_matrix = (rotation*(*this)).m_matrix;
}

auto TransformationMatrix::getInverse() -> TransformationMatrix
{
    return {};
}

auto TransformationMatrix::getRotation() const -> float
{
    const auto& v = (*this)*sf::Vector2f(1, 0);

    float angle;
    if(v.x == 0)
    {
        angle = (v.y > 0 ? 1 : -1) * M_PI/2;
    }
    else
    {
        angle = std::atan(v.y/v.x);
    }

    return roundFloat(angle);
}

void TransformationMatrix::print() const
{
    for(const auto& row : m_matrix)
    {
        for(const auto& col : row)
        {
            std::cout << col << ", ";
        }

        std::cout << std::endl;
    }
}