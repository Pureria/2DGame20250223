#include "FillRect.h"

FillRect::FillRect(const sf::Vector2f& size)
{
	_CenterPosition = sf::Vector2f(0, 0);
	_size = size;
	_rotation = 0;
	_color = sf::Color::White;
	_thickLines.setPrimitiveType(sf::Triangles);

	UpdateRect();
}

FillRect::~FillRect()
{
}

bool FillRect::Render()
{
	WindowManager::Instance().GetWindow().draw(_thickLines);
	return true;
}

bool FillRect::Release()
{
	return true;
}

void FillRect::UpdateRect()
{
	_thickLines.clear();
	sf::Vector2f offset = _size * 0.5f;
	float cos = std::cos(_rotation);
	float sin = std::sin(_rotation);

	sf::Vector2f p1_tl = sf::Vector2f(_CenterPosition.x + offset.x - 1.0f, _CenterPosition.y - offset.y + 1.0f);
	sf::Vector2f p1_bl = sf::Vector2f(_CenterPosition.x + offset.x - 1.0f, _CenterPosition.y + offset.y - 1.0f);
	sf::Vector2f p2_tl = sf::Vector2f(_CenterPosition.x - offset.x + 1.0f, _CenterPosition.y - offset.y + 1.0f);
	sf::Vector2f p2_bl = sf::Vector2f(_CenterPosition.x - offset.x + 1.0f, _CenterPosition.y + offset.y - 1.0f);

	p1_tl = GetRotationPos(p1_tl, _rotation);
	p1_bl = GetRotationPos(p1_bl, _rotation);
	p2_tl = GetRotationPos(p2_tl, _rotation);
	p2_bl = GetRotationPos(p2_bl, _rotation);

	_thickLines.append(sf::Vertex(p1_tl, _color));
	_thickLines.append(sf::Vertex(p2_tl, _color));
	_thickLines.append(sf::Vertex(p2_bl, _color));

	_thickLines.append(sf::Vertex(p1_tl, _color));
	_thickLines.append(sf::Vertex(p2_bl, _color));
	_thickLines.append(sf::Vertex(p1_bl, _color));
}


bool FillRect::SetCenterPosition(const sf::Vector2f& pos)
{
	_CenterPosition = pos;
	UpdateRect();
	return true;
}

bool FillRect::SetSize(const sf::Vector2f& size)
{
	_size = size;
	UpdateRect();
	return true;
}

bool FillRect::SetColor(const sf::Color& color)
{
	_color = color;
	UpdateRect();
	return true;
}

bool FillRect::SetRotation(const float& rotation)
{
	_rotation = rotation;
	UpdateRect();
	return true;
}

sf::Vector2f FillRect::GetRotationPos(const sf::Vector2f& pos, const float& angle) const
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	return sf::Vector2f(
		(pos.x - _CenterPosition.x) * cos - (pos.y - _CenterPosition.y) * sin + _CenterPosition.x,
		(pos.x - _CenterPosition.x) * sin + (pos.y - _CenterPosition.y) * cos + _CenterPosition.y
	);
}