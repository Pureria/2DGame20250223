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
	_angularVelocity(0),
	_mass(1.0f),
	_elasticity(0.5f),
	_momentOfInertia(1.0f)
{	
}

DynamicBody::DynamicBody(float gravityScale, GameObject* owner, bool isStatic) :
	_owner(owner),
	_gravityScale(gravityScale),
	_velocity(0, 0),
	_isStatic(isStatic),
	_drag(1.0f),
	_angularDrag(1.0f),
	_angularVelocity(0),
	_mass(1.0f),
	_elasticity(0.5f),
	_momentOfInertia(1.0f)
{
}

DynamicBody::~DynamicBody()
{
}

void DynamicBody::Initialize()
{
	//�_�C�i�~�b�N�{�f�B�}�l�[�W���[�Ɏ�����ǉ�
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

	//�d�͂�K�p
	_velocity.y += (GRAVITY * _gravityScale) * deltaTime;
	
	//�I�[�i�[�̈ʒu���X�V
	sf::Vector2f pos = _owner->GetCenterPosition();
	pos += _velocity;
	_owner->SetCenterPosition(pos);

	//��]��K�p
	float rotation = _owner->GetRotation();
	rotation += _angularVelocity * deltaTime;
	_owner->SetRotation(rotation);

	//�h���b�O�̓K�p
	DragUpdate(deltaTime);
	AngularDragUpdate(deltaTime);
}

void DynamicBody::ApplyImpulse(sf::Vector2f impulse, sf::Vector2f contactPoint)
{
	_velocity += impulse;

	//�p���x�̌v�Z
	sf::Vector2f center = _owner->GetCenterPosition();
	sf::Vector2f r = contactPoint - center; //��]���S����̋���
	float torque = r.x * impulse.y - r.y * impulse.x; //�g���N = r x F
	_angularVelocity += torque / _momentOfInertia;
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
	//�_�C�i�~�b�N�{�f�B�}�l�[�W���[���玩�����폜
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

void DynamicBody::SetElasticity(float elasticity)
{
	_elasticity = elasticity;
}

void DynamicBody::SetMass(float mass)
{
	_mass = mass;
}