#include "ColliderManager.h"

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

void ColliderManager::HandleCollision(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB)
{
	// �����ɏՓˏ���������
}