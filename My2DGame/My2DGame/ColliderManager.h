#pragma once
#include "IColliderManager.cpp"
#include <vector>

class ColliderManager : public IColliderManager
{
private:
	std::vector<std::shared_ptr<BoxCollider>> _colliders;

	void HandleCollision(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB)
	{
		// �����ɏՓˏ���������
	}

public:
	void AddCollider(std::shared_ptr<BoxCollider> collider) override
	{
		_colliders.push_back(collider);
	}

	void RemoveCollider(std::shared_ptr<BoxCollider> collider) override
	{
		_colliders.erase(std::remove(_colliders.begin(), _colliders.end(), collider), _colliders.end());
	}

	void Update() override
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
};

