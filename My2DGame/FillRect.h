#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"

class FillRect
{
private:
	sf::RectangleShape* _rectangle;

public:
	FillRect(const sf::Vector2f& size);
	~FillRect();
	bool Render();
	bool Release();
	bool SetPosition(const sf::Vector2f& pos);
	bool SetSize(const sf::Vector2f& size);
	bool SetFillColor(const sf::Color& color);

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
};

inline sf::Vector2f FillRect::GetPosition() const { return _rectangle->getPosition(); }
inline sf::Vector2f FillRect::GetSize() const { return _rectangle->getSize(); }