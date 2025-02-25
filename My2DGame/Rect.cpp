#include "Rect.h"

Rect::Rect(const sf::Vector2f& size)
{
	_size = size;
	_lineSize = 1.0f;
	//��
	sf::Vector2f s = sf::Vector2f(size.x, _lineSize);
	_rectangle[0] = new sf::RectangleShape(s);

	//��
	s = sf::Vector2f(size.x, _lineSize);
	_rectangle[1] = new sf::RectangleShape(s);

	//��
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[2] = new sf::RectangleShape(s);

	//�E
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[3] = new sf::RectangleShape(s);
}

Rect::Rect(const sf::Vector2f& size, const float& lineSize)
{
	_size = size;
	_lineSize = lineSize;
	//��
	sf::Vector2f s = sf::Vector2f(size.x, _lineSize);
	_rectangle[0] = new sf::RectangleShape(s);
	//��
	s = sf::Vector2f(size.x, _lineSize);
	_rectangle[1] = new sf::RectangleShape(s);
	//��
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[2] = new sf::RectangleShape(s);
	//�E
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
			delete _rectangle[i]; //���I�Ɋ��蓖�Ă�ꂽ�����������
			_rectangle[i] = nullptr; //�|�C���^��nullptr��
		}
	}
	return true;
}

bool Rect::SetPosition(const sf::Vector2f& pos)
{
	sf::Vector2f p = pos;
	//��
	_rectangle[0]->setPosition(p);
	//��
	p.y = pos.y + _size.y - _lineSize;
	_rectangle[1]->setPosition(p);
	//��
	p = pos;
	_rectangle[2]->setPosition(p); 
	//�E
	p.x = pos.x + _size.x - _lineSize;
	_rectangle[3]->setPosition(p);

	return true;
}

bool Rect::SetSize(const sf::Vector2f& size)
{
	//��
	sf::Vector2f s = sf::Vector2f(size.x, _lineSize);
	_rectangle[0]->setSize(s);
	//��
	s = sf::Vector2f(size.x, _lineSize);
	_rectangle[1]->setSize(s);
	//��
	s = sf::Vector2f(_lineSize, size.y);
	_rectangle[2]->setSize(s);
	//�E
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