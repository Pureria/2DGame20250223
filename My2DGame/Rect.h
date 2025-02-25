#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"

class Rect
{
private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	float _lineSize;
	sf::Vector2f _linePos[4];
	sf::Color _color;
	sf::VertexArray _thickLines;

	void UpdateRect();
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