#include "ColliderManager.h"
#include "GameObject.h"
#include "BoxCollider.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::AddCollider(std::shared_ptr<BoxCollider> collider)
{
	_colliders.push_back(collider);
}

void ColliderManager::RemoveCollider(std::shared_ptr<BoxCollider> collider)
{
	_colliders.erase(std::remove(_colliders.begin(), _colliders.end(), collider), _colliders.end());
}

void ColliderManager::Update()
{
	// �Փ˔���
	// ��d���[�v�őS�ẴR���C�_�[�̑g�ݍ��킹���`�F�b�N
	for (size_t i = 0; i < _colliders.size(); i++)
	{
		for (size_t j = i + 1; j < _colliders.size(); j++)
		{
			if (_colliders[i]->IsColliding(*_colliders[j]))
			{
				HandleCollision(_colliders[i], _colliders[j]);
			}
		}
	}
}

bool ColliderManager::Release()
{
	return true;
}

void ColliderManager::HandleCollision(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB)
{
	// �����ɏՓˏ���������
	GameObject* objA = colliderA->GetOwner();
	GameObject* objB = colliderB->GetOwner();

	// �ǂ��炩��nullptr�Ȃ珈�����Ȃ�
	if (!objA || !objB) return;

	sf::Vector2f pushOut = colliderA->CalculatePushOut(*colliderB);

	//�ǂ̃I�u�W�F�N�g���������邩
	bool isMoveA = objA->IsMoveAble();
	bool isMoveB = objB->IsMoveAble();

	if (isMoveA && isMoveB)
	{
		// ������������ꍇ
		objA->AddPosition(pushOut / 0.5f);
		objB->AddPosition(-pushOut / 0.5f);
	}
	else if (isMoveA)
	{
		// A������������ꍇ
		objA->AddPosition(pushOut);
	}
	else if (isMoveB)
	{
		// B������������ꍇ
		objB->AddPosition(-pushOut);
	}
	// �ǂ�����������Ȃ��ꍇ�͉������Ȃ�

	// �Փˎ��̃R�[���o�b�N���Ăяo��
	colliderA->OnCollision(objB);
	colliderB->OnCollision(objA);
}