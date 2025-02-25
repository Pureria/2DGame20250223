#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"

class Rect
{
private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	float _lineSize;
	//sf::RectangleShape* _rectangle;
	//1 ��
	//2 ��
	//3 ��
	//4 �E
	sf::RectangleShape* _rectangle[4];

public:
	Rect(const sf::Vector2f& size);
	Rect(const sf::Vector2f& size, const float& lineSize);
	~Rect();
	bool Render();
	bool Release();
	bool SetPosition(const sf::Vector2f& pos);
	bool SetSize(const sf::Vector2f& size);
	bool SetLineSize(const float& lineSize);
	bool SetColor(const sf::Color& color);

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	float GetLineSize() const;
};

inline sf::Vector2f Rect::GetPosition() const { return _position; }
inline sf::Vector2f Rect::GetSize() const { return _size; }
inline float Rect::GetLineSize() const { return _lineSize; }