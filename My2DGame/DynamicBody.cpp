#pragma once
#include "DynamicBody.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Timer.h"

DynamicBody::DynamicBody(float gravityScale, GameObject* owner) :
	_owner(owner),
	_gravityScale(gravityScale),
	_isStatic(false),
	_mass(1.0f),
	_inertia(1.0f),
	_angularVelocity(0.0f),
	_torque(0){}

DynamicBody::DynamicBody(float gravityScale, GameObject* owner, bool isStatic) :
	_owner(owner),
	_gravityScale(gravityScale),
	_isStatic(isStatic),
	_mass(1.0f),
	_inertia(1.0f),
	_angularVelocity(0.0f),
	_torque(0){}

DynamicBody::DynamicBody(float gravityScale, GameObject* owner, bool isStatic, float mass, float inertia) :
	_owner(owner),
	_gravityScale(gravityScale),
	_isStatic(isStatic),
	_mass(mass),
	_inertia(inertia),
	_angularVelocity(0.0f),
	_torque(0){}

DynamicBody::~DynamicBody() = default;

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
	sf::Vector2f pos = _owner->GetCenterPosition();
	float dt = Timer::Instance().DeltaTime();
	//重力を加算
	AddForce(sf::Vector2f(0, GRAVITY * _gravityScale));

	//速度の更新
	_velocity += _acceleration * dt;
	pos += _velocity * dt;
	_owner->SetCenterPosition(pos);
	_acceleration = sf::Vector2f(0, 0);

	//角速度の更新
	float angularAcceleration = _torque / _inertia; //角加速度
	_angularVelocity += angularAcceleration * dt;
	float angle = GetRadian(_owner->GetRotation()); //角度をラジアンに変換
	angle += _angularVelocity * dt;
	_owner->SetRotation(GetDegrees(angle)); //角度を度に変換
	_torque = 0;
}

void DynamicBody::Release()
{
	//ダイナミックボディマネージャーから自分を削除
	PhysicsManager::Instance().RemoveDynamicBody(shared_from_this());
}

void DynamicBody::AddForce(const sf::Vector2f& force)
{
	_acceleration += force;
}