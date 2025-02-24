#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderManager.h"

BoxCollider::BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject* owner)
{
	_pos = pos;
	_size = size;
	_owner = owner;
	
}

BoxCollider::~BoxCollider()
{	
}

void BoxCollider::Initialize()
{
	//�R���C�_�[�}�l�[�W���[�Ɏ�����ǉ�
	ColliderManager::Instance().AddCollider(shared_from_this());
}

void BoxCollider::DebugDraw()
{
}

void BoxCollider::SetPosition(sf::Vector2f pos)
{
	_pos = pos;
}

bool BoxCollider::IsColliding(BoxCollider& other) const
{
	//����̈ʒu�ƃT�C�Y���擾
	sf::Vector2f otherPos = other.GetPosition();
	sf::Vector2f otherSize = other.GetSize();

	//�����̈ʒu�Ƒ���̈ʒu���r���ē������Ă��邩����
	if (_pos.x < otherPos.x + otherSize.x &&	//�����̉E�[������̍��[�������ɂ���
		_pos.x + _size.x > otherPos.x &&		//�����̍��[������̉E�[�����E�ɂ���
		_pos.y < otherPos.y + otherSize.y &&	//�����̉��[������̏�[������ɂ���
		_pos.y + _size.y > otherPos.y)			//�����̏�[������̉��[�������ɂ���
	{
		return true;
	}
	return false;
}

sf::Vector2f BoxCollider::CalculatePushOut(const BoxCollider& other)
{
	//AABB�ł̏Փ˔���
	sf::Vector2f otherPos = other.GetPosition();
	sf::Vector2f otherSize = other.GetSize();
	
	//�����̈ʒu�Ƒ���̈ʒu���r���ē������Ă��邩����
	float overlapX = std::min(_pos.x + _size.x, otherPos.x + otherSize.x) - 
						std::max(_pos.x, otherPos.x);

	float overlapY = std::min(_pos.y + _size.y, otherPos.y + otherSize.y) -
						std::max(_pos.y, otherPos.y);

	//X����Y���̏d�Ȃ����r���āA�ǂ���������߂������߂�
	if (overlapX < overlapY)
	{
		//X���̏d�Ȃ���Y����菬�����ꍇ
		//X���̏d�Ȃ������ɉ����߂����������߂�
		if (_pos.x < otherPos.x)
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
		if (_pos.y < otherPos.y)
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

void BoxCollider::Release()
{
	//�R���C�_�[�}�l�[�W���[���玩�����폜
	ColliderManager::Instance().RemoveCollider(shared_from_this());
}