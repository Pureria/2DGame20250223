#include "FillRect.h"

FillRect::FillRect(const sf::Vector2f& size)
{
	_rectangle = new sf::RectangleShape(size);
}

FillRect::~FillRect()
{
	if (_rectangle != nullptr)
	{
		delete _rectangle;
		_rectangle = nullptr;
	}
}

bool FillRect::Render()
{
	WindowManager::Instance().GetWindow().draw(*_rectangle);

	return true;
}

bool FillRect::Release()
{
	if (_rectangle != nullptr)
	{
		delete _rectangle; //動的に割り当てられたメモリを解放
		_rectangle = nullptr; //ポインタをnullptrに
	}

	return true;
}

bool FillRect::SetPosition(const sf::Vector2f& pos)
{
	_rectangle->setPosition(pos);
	return true;
}

bool FillRect::SetSize(const sf::Vector2f& size)
{
	_rectangle->setSize(size);
	return true;
}

bool FillRect::SetFillColor(const sf::Color& color)
{
	_rectangle->setFillColor(color);
	return true;
}