#pragma once
#include "DynamicBody.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Timer.h"

DynamicBody::DynamicBody(float gravityScale, GameObject* owner) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isStatic(false),
	_drag(1.0f),
	_angularDrag(1.0f),
	_angularVelocity(0)
{	
}

DynamicBody::DynamicBody(float gravityScale, GameObject* owner, bool isStatic) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isStatic(isStatic),
	_drag(1.0f),
	_angularDrag(1.0f),
	_angularVelocity(0)
{
}

DynamicBody::~DynamicBody()
{
}

void DynamicBody::Initialize()
{
	//ダイナミックボディマネージャーに自分を追加
	PhysicsManager::Instance().AddDynamicBody(shared_from_this());
}

void DynamicBody::DebugDraw()
{
}

void DynamicBody::Update()
{	
}

void DynamicBody::SystemUpdate()
{
	if (_isStatic) return;

	const float deltaTime = static_cast<float>(Timer::Instance().DeltaTime());

	//重力を適用
	_velocity.y += (GRAVITY * _gravityScale) * deltaTime;
	
	//オーナーの位置を更新
	sf::Vector2f pos = _owner->GetPosition();
	pos += _velocity;
	_owner->SetPosition(pos);

	//回転を適用
	float rotation = _owner->GetRotation();
	rotation += _angularVelocity * deltaTime;
	_owner->SetRotation(rotation);

	//ドラッグの適用
	DragUpdate(deltaTime);
	AngularDragUpdate(deltaTime);
}

void DynamicBody::DragUpdate(float deltaTime)
{
	_velocity *= std::exp(-_drag * deltaTime);
}

void DynamicBody::AngularDragUpdate(float deltaTime)
{
	_angularVelocity *= std::exp(-_angularDrag * deltaTime);
}

void DynamicBody::Release()
{
	//ダイナミックボディマネージャーから自分を削除
	PhysicsManager::Instance().RemoveDynamicBody(shared_from_this());
}

void DynamicBody::SetGravityScale(float gravityScale)
{
	_gravityScale = gravityScale;
}

void DynamicBody::SetVelocity(sf::Vector2f velocity, ForceMode mode)
{
	if (mode == ForceMode::ADD)
	{
		_velocity += velocity;
	}
	else if (mode == ForceMode::SET)
	{
		_velocity = velocity;
	}
}

void DynamicBody::SetIsGravityEnabled(bool isGravity)
{
	_isStatic = isGravity;
}

void DynamicBody::SetDrag(float drag)
{
	_drag = drag;
}

void DynamicBody::SetAngularDrag(float drag)
{
	_angularDrag = drag;
}

void DynamicBody::SetAngularVelocity(float velocity, ForceMode mode)
{
	if (mode == ForceMode::ADD)
	{
		_angularVelocity += velocity;
	}
	else if (mode == ForceMode::SET)
	{
		_angularVelocity = velocity;
	}
}