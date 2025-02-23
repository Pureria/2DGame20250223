#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"

class Rectangle
{
private:
	sf::RectangleShape* _rectangle;

public:
	Rectangle(const sf::Vector2f& size);
	~Rectangle();
	bool Render();
	bool Release();
	bool SetPosition(const sf::Vector2f& pos);
	bool SetSize(const sf::Vector2f& size);
	bool SetFillColor(const sf::Color& color);

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
};

inline sf::Vector2f Rectangle::GetPosition() const { return _rectangle->getPosition(); }
inline sf::Vector2f Rectangle::GetSize() const { return _rectangle->getSize(); }