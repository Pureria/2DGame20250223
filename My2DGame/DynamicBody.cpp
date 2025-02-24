#include "DynamicBody.h"
#include "GameObject.h"

DynamicBody::DynamicBody(float gravityScale, GameObject* owner) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isGravityEnabled(true),
	_isGrounded(false)
{
}

DynamicBody::DynamicBody(float gravityScale, GameObject* owner, bool isGravity) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isGravityEnabled(isGravity),
	_isGrounded(false)
{
}

DynamicBody::~DynamicBody()
{
}

void DynamicBody::DebugDraw()
{
}

void DynamicBody::Update()
{
	//重力を適用
	_velocity.y += 9.8f * _gravityScale;
	//オーナーの位置を更新
	sf::Vector2f pos = _owner->GetPosition();
	pos += _velocity;
	_owner->SetPosition(pos);
}

void DynamicBody::Release()
{
}

void DynamicBody::SetGravityScale(float gravityScale)
{
	_gravityScale = gravityScale;
}

void DynamicBody::SetVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;
}

void DynamicBody::SetIsGrounded(bool isGrounded)
{
	_isGrounded = isGrounded;
}

void DynamicBody::SetIsGravityEnabled(bool isGravity)
{
	_isGravityEnabled = isGravity;
}