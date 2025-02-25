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
		delete _rectangle; //���I�Ɋ��蓖�Ă�ꂽ�����������
		_rectangle = nullptr; //�|�C���^��nullptr��
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