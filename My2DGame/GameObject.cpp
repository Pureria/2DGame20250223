#include "GameObject.h"
#include "BoxCollider.hpp"

GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size, bool isMovable)
{
	_pos = pos;
	_collider = new BoxCollider(pos, size, *this);
	_isMovable = isMovable;
}

GameObject::~GameObject()
{
	if (_collider != nullptr)
	{
		delete _collider;
		_collider = nullptr;
	}
}

void GameObject::Move(sf::Vector2f delta)
{
	_pos += delta;
	_collider->SetPosition(_pos);
}

void GameObject::SetPosition(sf::Vector2f pos)
{
	_pos = pos;
	_collider->SetPosition(_pos);
}

void GameObject::Release()
{
	if (_collider != nullptr)
	{
		delete _collider;
		_collider = nullptr;
	}

	delete this;
}