#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size):
	_pos(pos),
	_nextSetPosCBID(0)
{ }

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	//コンポーネントのInitializeは追加時に呼び出されるため、ここでは何もしない
}

void GameObject::Update()
{
	for (auto& component : _Components)
	{
		component.second->Update();
	}
}

void GameObject::Render()
{
}

void GameObject::RenderDebug()
{
	for (auto& component : _Components)
	{
		component.second->DebugDraw();
	}
}

void GameObject::Release()
{
	for (auto& component : _Components)
	{
		component.second->Release();
	}
	_Components.clear();
}

int GameObject::AddSetPositionCallback(SetPositionCallback callback)
{
	int id = _nextSetPosCBID++;
	_SetPositionCallbacks[id] = callback;
	return id;
}

void GameObject::RemoveSetPositionCallback(int id)
{
	auto it = _SetPositionCallbacks.find(id);
	if (it != _SetPositionCallbacks.end())
	{
		_SetPositionCallbacks.erase(it);
	}
}

void GameObject::AddPosition(sf::Vector2f delta)
{
	_pos += delta;
	for (auto& callback : _SetPositionCallbacks)
	{
		callback.second(_pos);
	}
}

void GameObject::SetCenterPosition(sf::Vector2f pos)
{
	_pos = pos;
	for (auto& callback : _SetPositionCallbacks)
	{
		callback.second(_pos);
	}
}

/*  下は後で消す  */
/*

void GameObject::Move(sf::Vector2f dir, ForceMode mode)
{
	if (!_isMovable) return;
	_dynamicBody->SetVelocity(dir, mode);
}
*/