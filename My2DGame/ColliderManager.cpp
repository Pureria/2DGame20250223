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
	// 衝突判定
	// 二重ループで全てのコライダーの組み合わせをチェック
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
	// ここに衝突処理を書く
}