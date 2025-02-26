#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"

class FillRect
{
private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	float _rotation;
	sf::Color _color;
	sf::VertexArray _thickLines;

	void UpdateRect();
	sf::Vector2f GetRotationPos(const sf::Vector2f& pos, const float& angle) const;
public:
	FillRect(const sf::Vector2f& size);
	~FillRect();
	bool Render();
	bool Release();
	
	bool SetPosition(const sf::Vector2f& pos);
	bool SetSize(const sf::Vector2f& size);
	bool SetRotation(const float& rotation);
	bool SetColor(const sf::Color& color);

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	float GetRotation() const;
};

inline sf::Vector2f FillRect::GetPosition() const { return _position; }
inline sf::Vector2f FillRect::GetSize() const { return _size; }
inline float FillRect::GetRotation() const { return _rotation; }