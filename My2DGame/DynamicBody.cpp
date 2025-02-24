#include "DynamicBody.h"
#include "GameObject.h"

DynamicBody::DynamicBody(float gravityScale, GameObject* owner) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isStatic(false),
	_drag(1.0f)
{	
}

DynamicBody::DynamicBody(float gravityScale, GameObject* owner, bool isStatic) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isStatic(isStatic),
	_drag(1.0f)
{
}

DynamicBody::~DynamicBody()
{
}

void DynamicBody::Initialize()
{
	//ダイナミックボディマネージャーに自分を追加
	DynamicBodyManager::Instance().AddDynamicBody(shared_from_this());
}

void DynamicBody::DebugDraw()
{
}

void DynamicBody::Update()
{
	if (_isStatic) return;

	float deltaTime = Timer::Instance().DeltaTime();

	//重力を適用
	_velocity.y += (GRAVITY * _gravityScale) * deltaTime;
	//オーナーの位置を更新
	sf::Vector2f pos = _owner->GetPosition();
	pos += _velocity;
	_owner->SetPosition(pos);

	DragUpdate(deltaTime);
}

void DynamicBody::DragUpdate(float deltaTime)
{
	_velocity *= std::exp(-_drag * deltaTime);

}

void DynamicBody::Release()
{
	//ダイナミックボディマネージャーから自分を削除
	DynamicBodyManager::Instance().RemoveDynamicBody(shared_from_this());
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