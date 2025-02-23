#pragma once
#include "IColliderManager.cpp"
#include <vector>

class ColliderManager : public IColliderManager
{
private:
	std::vector<std::shared_ptr<BoxCollider>> _colliders;

	void HandleCollision(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB)
	{
		// ここに衝突処理を書く
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
};

