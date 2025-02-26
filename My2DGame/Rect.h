#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"

class Rect
{
private:
	sf::Vector2f _CenterPosition;
	sf::Vector2f _size;
	float _rotation;
	float _lineSize;
	sf::Vector2f _linePos[4];
	sf::Color _color;
	sf::VertexArray _thickLines;

	void UpdateRect();
	sf::Vector2f GetRotationPos(const sf::Vector2f& pos, const float& angle) const;
public:
	Rect(const sf::Vector2f& size);
	Rect(const sf::Vector2f& size, const float& lineSize);
	~Rect();
	bool Render();
	bool Release();
	
	bool SetCenterPosition(const sf::Vector2f& pos);
	bool SetSize(const sf::Vector2f& size);
	bool SetLineSize(const float& lineSize);
	bool SetColor(const sf::Color& color);
	bool SetRotation(const float& rotation);

	sf::Vector2f GetCenterPosition() const;
	sf::Vector2f GetSize() const;
	float GetLineSize() const;
	float GetRotation() const;
};

inline sf::Vector2f Rect::GetCenterPosition() const { return _CenterPosition; }
inline sf::Vector2f Rect::GetSize() const { return _size; }
inline float Rect::GetLineSize() const { return _lineSize; }
inline float Rect::GetRotation() const { return _rotation; }