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

bool ColliderManager::Release()
{
	return true;
}

void ColliderManager::HandleCollision(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB)
{
	// ここに衝突処理を書く
	GameObject* objA = colliderA->GetOwner();
	GameObject* objB = colliderB->GetOwner();

	// どちらかがnullptrなら処理しない
	if (!objA || !objB) return;

	sf::Vector2f pushOut = colliderA->CalculatePushOut(*colliderB);

	//どのオブジェクトが動かせるか
	bool isMoveA = objA->IsMoveAble();
	bool isMoveB = objB->IsMoveAble();

	if (isMoveA && isMoveB)
	{
		// 両方動かせる場合
		objA->AddPosition(pushOut / 0.5f);
		objB->AddPosition(-pushOut / 0.5f);
	}
	else if (isMoveA)
	{
		// Aだけ動かせる場合
		objA->AddPosition(pushOut);
	}
	else if (isMoveB)
	{
		// Bだけ動かせる場合
		objB->AddPosition(-pushOut);
	}
	// どちらも動かせない場合は何もしない

	// 衝突時のコールバックを呼び出す
	colliderA->OnCollision(objB);
	colliderB->OnCollision(objA);
}