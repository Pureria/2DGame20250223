#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(sf::Vector2f centerPos, sf::Vector2f size):
	_CenterPos(centerPos),
	_Size(size),
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
	_CenterPos += delta;
	for (auto& callback : _SetPositionCallbacks)
	{
		callback.second(_CenterPos);
	}
}

void GameObject::SetCenterPosition(sf::Vector2f pos)
{
	_CenterPos = pos;
	for (auto& callback : _SetPositionCallbacks)
	{
		callback.second(_CenterPos);
	}
}

void GameObject::SetSize(sf::Vector2f size)
{
	_Size = size;
}
