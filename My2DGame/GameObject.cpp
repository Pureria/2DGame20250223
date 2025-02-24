#include "GameObject.h"
#include "BoxCollider.h"

GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size, bool isMovable):
	_pos(pos),
	_isMovable(isMovable)
{
	_collider = std::make_shared<BoxCollider>(pos, size, this);
	_collider->Initialize();
}

GameObject::~GameObject()
{
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
	_collider->Release();
	_collider.reset();
}