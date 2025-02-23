#include "BoxCollider.hpp"
#include "GameObject.h"

BoxCollider::BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject& owner)
{
	_pos = pos;
	_size = size;
	_owner = &owner;
}

BoxCollider::~BoxCollider()
{
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
	if (_pos.x < otherPos.x + otherSize.x &&
		_pos.x + _size.x > otherPos.x &&
		_pos.y < otherPos.y + otherSize.y &&
		_pos.y + _size.y > otherPos.y)
	{
		return true;
	}
	return false;
}