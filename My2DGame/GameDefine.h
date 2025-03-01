#pragma once
#include <cmath>

namespace My2D
{
    struct Vector2
    {
        float x, y;

        
        Vector2 operator+(const Vector2& other) const { return Vector2{ x + other.x, y + other.y }; }
        Vector2 operator-(const Vector2& other) const { return Vector2{ x - other.x, y - other.y }; }
        Vector2 operator*(const float& scalar) const { return Vector2{ x * scalar, y * scalar }; }
        Vector2 operator/(const float& scalar) const { return Vector2{ x / scalar, y / scalar }; }
        Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
        Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
        Vector2& operator*=(const float& scalar) { x *= scalar; y *= scalar; return *this; }
        Vector2& operator/=(const float& scalar) { x /= scalar; y /= scalar; return *this; }
        bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
        bool operator!=(const Vector2& other) const { return x != other.x || y != other.y; }
        Vector2& operator=(const Vector2& other) { x = other.x; y = other.y; return *this; }
        
        Vector2() : x(0), y(0) {};
        Vector2(float x, float y) : x(x), y(y) {};
        
        float dot(const Vector2& other) const { return x * other.x + y * other.y; }
        float cross(const Vector2& other) const { return x * other.y - y * other.x; }
        float magnitude() const { return std::sqrt(x * x + y * y); }
        operator sf::Vector2f() const { return sf::Vector2f(x, y); }
    };
}