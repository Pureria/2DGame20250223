#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "PhysicsManager.h"

BoxCollider::BoxCollider(sf::Vector2f centerPos, sf::Vector2f size, GameObject* owner)
{
	_centerPos = centerPos;
	_size = size;
	_owner = owner;
	_nextHandlerID = 0;
	_SetPositionCallbackID = 0;
}

BoxCollider::~BoxCollider()
{	
}

void BoxCollider::Initialize()
{
	//�R���C�_�[�}�l�[�W���[�Ɏ�����ǉ�
	PhysicsManager::Instance().AddCollider(shared_from_this());
	
	//�I�[�i�[��SetPosition�֐���SetPosition��o�^
	_SetPositionCallbackID = _owner->AddSetPositionCallback([this](sf::Vector2f pos) {this->SetCenterPosition(pos); });
}

void BoxCollider::DebugDraw()
{
}

void BoxCollider::Update()
{
}

void BoxCollider::SetCenterPosition(sf::Vector2f pos)
{
	_centerPos = pos;
}

//OBB�ł̏Փ˔���
bool BoxCollider::CalculatePenetrationOBB(const BoxCollider& other, sf::Vector2f& penetration) const
{
	//���ꂼ��OBB�̉�]�����擾
	std::vector<sf::Vector2f> axes = GetSeparatingAxes(other);
	float minOverlap = std::numeric_limits<float>::max();
	sf::Vector2f bestAxis;

	//�e���œ��e���ďd�Ȃ����v�Z
	for(const auto& axis: axes)
	{
		float minA, maxA, minB, maxB;
		ProjectOntoAxis(axis, minA, maxA);
		other.ProjectOntoAxis(axis, minB, maxB);

		//�d�Ȃ����v�Z
		if(maxA < minB || maxB < minA)
		{			
			return false; //�d�Ȃ��Ă��Ȃ�
		}

		//�I�[�o�[���b�v�ʂ��v�Z
		float overlap = std::min(maxA, maxB) - std::max(minA, minB);
		if(overlap < minOverlap)
		{
			minOverlap = overlap;
			bestAxis = axis;
		}
	}

	//�ł��I�[�o�[���b�v�����������������o���x�N�g���Ƃ���
	penetration = bestAxis * minOverlap;
	return true;
}

std::vector<sf::Vector2f> BoxCollider::GetSeparatingAxes(const BoxCollider& other) const
{
	std::vector<sf::Vector2f> axes;

	//���g��OBB�̎����擾
	axes.push_back(RotateVector(sf::Vector2f(1, 0), _owner->GetRotation()));
	axes.push_back(RotateVector(sf::Vector2f(0, 1), _owner->GetRotation()));

	//�����OBB�̎����擾
	axes.push_back(RotateVector(sf::Vector2f(1, 0), other._owner->GetRotation()));
	axes.push_back(RotateVector(sf::Vector2f(0, 1), other._owner->GetRotation()));

	return axes;
}

void BoxCollider::ProjectOntoAxis(const sf::Vector2f& axis, float& min, float& max) const
{
	std::vector<sf::Vector2f> corners = GetTransformedCorners();
	min = max = DotProduct(corners[0], axis);

	for(int i = 1; i < 4; i++)
	{
		float projection = DotProduct(corners[i], axis);
		min = std::min(min, projection);
		max = std::max(max, projection);
	}
}

float BoxCollider::DotProduct(const sf::Vector2f& a, const sf::Vector2f& b) const { return a.x * b.x + a.y * b.y; }

std::vector<sf::Vector2f> BoxCollider::GetTransformedCorners() const
{
	std::vector<sf::Vector2f> corners;
	sf::Vector2f center = _owner->GetCenterPosition();
	sf::Vector2f halfSize = _size * 0.5f;
	float rotation = _owner->GetRotation();

	corners.push_back(RotateVector(sf::Vector2f(-halfSize.x, -halfSize.y), rotation) + center);
	corners.push_back(RotateVector(sf::Vector2f(halfSize.x, -halfSize.y), rotation) + center);
	corners.push_back(RotateVector(sf::Vector2f(halfSize.x, halfSize.y), rotation) + center);
	corners.push_back(RotateVector(sf::Vector2f(-halfSize.x, halfSize.y), rotation) + center);

	return corners;
}

sf::Vector2f BoxCollider::RotateVector(const sf::Vector2f& vec, float angle) const
{
	float rad = angle * 3.14159265f / 180.0f;
	float cosA = std::cos(rad);
	float sinA = std::sin(rad);

	return sf::Vector2f(
		vec.x * cosA - vec.y * sinA,
		vec.x * sinA + vec.y * cosA
	);
}



void BoxCollider::OnCollision(GameObject* other)
{
	//�R�[���o�b�N�֐����Ăяo��
	for (auto& handler : _collisionHandlers)
	{
		handler.second(_owner, other);
	}
}

int BoxCollider::AddCollisionHandler(CollisionCallback callback)
{
	int id = _nextHandlerID++;
	_collisionHandlers[id] = callback;
	return id;
}

void BoxCollider::RemoveCollisionHandler(int id)
{
	auto it = _collisionHandlers.find(id);
	if (it != _collisionHandlers.end()) {
		_collisionHandlers.erase(it);
	}
	else {
		// ID��������Ȃ������ꍇ�̃��O�o�́i�f�o�b�O�p�j
		DebugManager::LogWarning("Attempted to remove non-existent collision handler with ID " + std::to_string(id));
	}
}

void BoxCollider::Release()
{
	//�R���C�_�[�}�l�[�W���[���玩�����폜
	PhysicsManager::Instance().RemoveCollider(shared_from_this());

	//�I�[�i�[��SetPosition�֐��ɓo�^�����R�[���o�b�N���폜
	_owner->RemoveSetPositionCallback(_SetPositionCallbackID);
}