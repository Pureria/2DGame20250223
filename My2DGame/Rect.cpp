#include "Rect.h"

Rect::Rect(const sf::Vector2f& size)
{
	_size = size;
	_lineSize = 1.0f;
	//上
	sf::Vector2f s = sf::Vector2f(size.x, _lineSize);
	_rectangle[0] = new sf::RectangleShape(s);

	//下
	s = sf::Vector2f(size.x, _lineSize);
	_rectangle[1] = new sf::RectangleShape(s);

	//左
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[2] = new sf::RectangleShape(s);

	//右
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[3] = new sf::RectangleShape(s);
}

Rect::Rect(const sf::Vector2f& size, const float& lineSize)
{
	_size = size;
	_lineSize = lineSize;
	//上
	sf::Vector2f s = sf::Vector2f(size.x, _lineSize);
	_rectangle[0] = new sf::RectangleShape(s);
	//下
	s = sf::Vector2f(size.x, _lineSize);
	_rectangle[1] = new sf::RectangleShape(s);
	//左
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[2] = new sf::RectangleShape(s);
	//右
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[3] = new sf::RectangleShape(s);
}

Rect::~Rect()
{
	for (int i = 0; i < 4; i++)
	{
		if (_rectangle[i] != nullptr)
		{
			delete _rectangle[i];
			_rectangle[i] = nullptr;
		}
	}
}

bool Rect::Render()
{
	/*
	for (int i = 0; i < 4; i++)
	{
		WindowManager::Instance().GetWindow().draw(*_rectangle[i]);
	}
	*/

	WindowManager::Instance().GetWindow().draw(*_rectangle[0]);
	WindowManager::Instance().GetWindow().draw(*_rectangle[1]);
	WindowManager::Instance().GetWindow().draw(*_rectangle[2]);
	WindowManager::Instance().GetWindow().draw(*_rectangle[3]);
	return true;
}

bool Rect::Release()
{
	for (int i = 0; i < 4; i++)
	{
		if (_rectangle[i] != nullptr)
		{
			delete _rectangle[i]; //動的に割り当てられたメモリを解放
			_rectangle[i] = nullptr; //ポインタをnullptrに
		}
	}
	return true;
}

bool Rect::SetPosition(const sf::Vector2f& pos)
{
	sf::Vector2f p = pos;
	//上
	_rectangle[0]->setPosition(p);
	//下
	p.y = pos.y + _size.y - _lineSize;
	_rectangle[1]->setPosition(p);
	//左
	p = pos;
	_rectangle[2]->setPosition(p); 
	//右
	p.x = pos.x + _size.x - _lineSize;
	_rectangle[3]->setPosition(p);

	return true;
}

bool Rect::SetSize(const sf::Vector2f& size)
{
	//上
	sf::Vector2f s = sf::Vector2f(size.x, _lineSize);
	_rectangle[0]->setSize(s);
	//下
	s = sf::Vector2f(size.x, _lineSize);
	_rectangle[1]->setSize(s);
	//左
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[2]->setSize(s);
	//右
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[3]->setSize(s);
	return true;
}

bool Rect::SetLineSize(const float& lineSize)
{
	_lineSize = lineSize;
	SetSize(_size);
	return true;
}

bool Rect::SetColor(const sf::Color& color)
{
	for (int i = 0; i < 4; i++)
	{
		_rectangle[i]->setFillColor(color);
	}
	return true;
}