#include "GameObject.h"

GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size, bool isMovable):
	_pos(pos),
	_isMovable(isMovable)
{
	_collider = std::make_shared<BoxCollider>(pos, size, this);
	_dynamicBody = std::make_shared<DynamicBody>(0.05f, this, !isMovable);

	_collider->Initialize();
	_dynamicBody->Initialize();
}

GameObject::~GameObject()
{
}

void GameObject::AddPosition(sf::Vector2f delta)
{
	_pos += delta;
	_collider->SetPosition(_pos);
}

void GameObject::SetPosition(sf::Vector2f pos)
{
	_pos = pos;
	_collider->SetPosition(_pos);
}

void GameObject::Move(sf::Vector2f dir, ForceMode mode)
{
	if (!_isMovable) return;
	_dynamicBody->SetVelocity(dir, mode);
}

void GameObject::Release()
{
	_collider->Release();
	_dynamicBody->Release();

	_collider.reset();
	_dynamicBody.reset();
}