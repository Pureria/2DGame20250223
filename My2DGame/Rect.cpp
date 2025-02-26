#include "Rect.h"

Rect::Rect(const sf::Vector2f& size)
{
	_thickLines = sf::VertexArray(sf::Triangles);
	_size = size;
	_lineSize = 1.0f;

	//右上
	_linePos[0] = sf::Vector2f(0, 0);
	//右下
	_linePos[1] = sf::Vector2f(0, size.y);
	//左上
	_linePos[2] = sf::Vector2f(size.x, 0);
	//左下
	_linePos[3] = sf::Vector2f(size.x, size.y);

	UpdateRect();
}

Rect::Rect(const sf::Vector2f& size, const float& lineSize)
{
	_thickLines = sf::VertexArray(sf::Triangles);
	_size = size;
	_lineSize = lineSize;

	//右上
	_linePos[0] = sf::Vector2f(0, 0);
	//右下
	_linePos[1] = sf::Vector2f(0, size.y);
	//左上
	_linePos[2] = sf::Vector2f(size.x, 0);
	//左下
	_linePos[3] = sf::Vector2f(size.x, size.y);

	UpdateRect();
}

Rect::~Rect()
{
}

bool Rect::Render()
{
	WindowManager::Instance().GetWindow().draw(_thickLines);
	return true;
}

bool Rect::Release()
{
	return true;
}

void Rect::UpdateRect()
{
	_thickLines.clear();
	float cos = std::cos(_rotation);
	float sin = std::sin(_rotation);
	//右上
	_linePos[0] = sf::Vector2f(_position.x, _position.y);
	//右下
	_linePos[1] = sf::Vector2f(_position.x, _position.y + _size.y);
	//左上
	_linePos[2] = sf::Vector2f(_position.x + _size.x, _position.y);
	//左下
	_linePos[3] = sf::Vector2f(_position.x + _size.x, _position.y + _size.y);

	//右の線
	sf::Vector2f p1_tl = _linePos[0];
	sf::Vector2f p1_bl = _linePos[1];
	sf::Vector2f p2_tl = sf::Vector2f(_linePos[0].x + _lineSize, _linePos[0].y);
	sf::Vector2f p2_bl = sf::Vector2f(_linePos[1].x + _lineSize, _linePos[1].y);

	//回転
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

	//左の線
	p1_tl = sf::Vector2f(_linePos[2].x - _lineSize, _linePos[2].y);
	p1_bl = sf::Vector2f(_linePos[3].x - _lineSize, _linePos[3].y);
	p2_tl = _linePos[2];
	p2_bl = _linePos[3];

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

	//上の線
	p1_tl = _linePos[2];
	p1_bl = sf::Vector2f(_linePos[2].x, _linePos[2].y + _lineSize);
	p2_tl = _linePos[0];
	p2_bl = sf::Vector2f(_linePos[0].x, _linePos[0].y + _lineSize);

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

	//下の線
	p1_tl = sf::Vector2f(_linePos[3].x, _linePos[3].y - _lineSize);
	p1_bl = _linePos[3];
	p2_tl = sf::Vector2f(_linePos[1].x, _linePos[1].y - _lineSize);
	p2_bl = _linePos[1];

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

bool Rect::SetPosition(const sf::Vector2f& pos)
{
	_position = pos;
	UpdateRect();
	return true;
}

bool Rect::SetSize(const sf::Vector2f& size)
{
	_size = size;
	UpdateRect();

	return true;
}

bool Rect::SetLineSize(const float& lineSize)
{
	_lineSize = lineSize;
	UpdateRect();
	return true;
}

bool Rect::SetColor(const sf::Color& color)
{
	_color = color;
	return true;
}

bool Rect::SetRotation(const float& rotation)
{
	_rotation = rotation;
	return true;
}

sf::Vector2f Rect::GetRotationPos(const sf::Vector2f& pos, const float& angle) const
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	return sf::Vector2f(
		(pos.x - _position.x) * cos - (pos.y - _position.y) * sin + _position.x,
		(pos.x - _position.x) * sin + (pos.y - _position.y) * cos + _position.y
	);
}