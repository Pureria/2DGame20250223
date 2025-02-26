#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "PhysicsManager.h"

BoxCollider::BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject* owner)
{
	_centerPos = pos;
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

bool BoxCollider::IsColliding(BoxCollider& other) const
{
	std::array<sf::Vector2f, 4> vertices = GetRotatedVertices();
	std::array<sf::Vector2f, 4> otherVertices = other.GetRotatedVertices();

	//SAT���g�p����OBB���m�̏Փ˔���
	//�e�I�u�W�F�N�g�̕ӂ̖@�����v�Z
	std::array<sf::Vector2f, 4> axes = {
		sf::Vector2f(1, 0),
		sf::Vector2f(0, 1),
		sf::Vector2f(-1, 0),
		sf::Vector2f(0, -1)
	};

	for(const auto& axis : axes)
	{
		//�e���_�𓊉e
		float minA = std::numeric_limits<float>::max();
		float maxA = std::numeric_limits<float>::lowest();
		for(const auto& vertex : vertices)
		{
			float projection = vertex.x * axis.x + vertex.y * axis.y;
			minA = std::min(minA, projection);
			maxA = std::max(maxA, projection);
		}

		float minB = std::numeric_limits<float>::max();
		float maxB = std::numeric_limits<float>::lowest();
		for (const auto& vertex : otherVertices)
		{
			float projection = vertex.x * axis.x + vertex.y * axis.y;
			minB = std::min(minB, projection);
			maxB = std::max(maxB, projection);
		}

		//�d�Ȃ���`�F�b�N
		if (maxA < minB || maxB < minA)
		{
			//�d�Ȃ��Ă��Ȃ�
			return false;
		}
	}

	return true;
}

sf::Vector2f BoxCollider::CalculatePushOut(const BoxCollider& other)
{
	//AABB�ł̏Փ˔���
	sf::Vector2f otherPos = other.GetCenterPosition();
	sf::Vector2f otherSize = other.GetSize();
	
	//�����̈ʒu�Ƒ���̈ʒu���r���ē������Ă��邩����
	float overlapX = std::min(_centerPos.x + _size.x, otherPos.x + otherSize.x) -
						std::max(_centerPos.x, otherPos.x);

	float overlapY = std::min(_centerPos.y + _size.y, otherPos.y + otherSize.y) -
						std::max(_centerPos.y, otherPos.y);

	if (overlapX == overlapY) {
		return sf::Vector2f(overlapX, 0);
	}

	//X����Y���̏d�Ȃ����r���āA�ǂ���������߂������߂�
	if (overlapX < overlapY)
	{
		//X���̏d�Ȃ���Y����菬�����ꍇ
		//X���̏d�Ȃ������ɉ����߂����������߂�
		if (_centerPos.x < otherPos.x)
		{
			//���������ɂ���ꍇ
			return sf::Vector2f(-overlapX, 0);
		}
		else
		{
			//�������E�ɂ���ꍇ
			return sf::Vector2f(overlapX, 0);
		}
	}
	else
	{
		//Y���̏d�Ȃ���X����菬�����ꍇ
		//Y���̏d�Ȃ������ɉ����߂����������߂�
		if (_centerPos.y < otherPos.y)
		{
			//��������ɂ���ꍇ
			return sf::Vector2f(0, -overlapY);
		}
		else
		{
			//���������ɂ���ꍇ
			return sf::Vector2f(0, overlapY);
		}
	}
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

std::array<sf::Vector2f, 4> BoxCollider::GetRotatedVertices() const
{
	//OBB�̎l�����v�Z
	//���̎��_�ł͉�]���Ă��Ȃ����
	sf::Vector2f size = _size * 0.5f;
	std::array<sf::Vector2f, 4> vertives = {
		_centerPos + sf::Vector2f(-size.x, size.y),
		_centerPos + sf::Vector2f(size.x, size.y),
		_centerPos + sf::Vector2f(-size.x, -size.y),
		_centerPos + sf::Vector2f(size.x, -size.y)
	};

	//OBB����]������v�Z
	float angle = _owner->GetRotation();
	for (auto& vertex : vertives)
	{
		/*
		��]�s����g���ĉ�]������
		��]�s�� : |cos��, -sin��|
		          |sin��, cos�� |	*/
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);
		vertex = sf::Vector2f(
			vertex.x * cosA - vertex.y * sinA,
			vertex.x * sinA + vertex.y * cosA
		);
	}

	return vertives;
}