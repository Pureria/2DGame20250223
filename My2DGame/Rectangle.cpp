#include "Rectangle.h"

Rectangle::Rectangle(const sf::Vector2f& size)
{
	_rectangle = new sf::RectangleShape(size);
}

Rectangle::~Rectangle()
{
	if (_rectangle != nullptr)
	{
		delete _rectangle;
		_rectangle = nullptr;
	}
}

bool Rectangle::Render()
{
	WindowManager::Instance().GetWindow().draw(*_rectangle);

	return true;
}

bool Rectangle::Release()
{
	if (_rectangle != nullptr)
	{
		delete _rectangle; //���I�Ɋ��蓖�Ă�ꂽ�����������
		_rectangle = nullptr; //�|�C���^��nullptr��
	}

	delete this; //���g���폜

	return true;
}

bool Rectangle::SetPosition(const sf::Vector2f& pos)
{
	_rectangle->setPosition(pos);
	return true;
}

bool Rectangle::SetSize(const sf::Vector2f& size)
{
	_rectangle->setSize(size);
	return true;
}

bool Rectangle::SetFillColor(const sf::Color& color)
{
	_rectangle->setFillColor(color);
	return true;
}