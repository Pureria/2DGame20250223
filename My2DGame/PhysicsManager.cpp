#include "PhysicsManager.h"
#include "BoxCollider.h"
#include "DynamicBody.h"
#include "GameObject.h"

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Update()
{
    // 衝突判定
    // 二重ループで全てのコライダーの組み合わせをチェック
    for (size_t i = 0; i < _colliders.size(); i++)
    {
        for (size_t j = i + 1; j < _colliders.size(); j++)
        {
            if (_colliders[i]->IsColliding(*_colliders[j]))
            {
                HandleCollision(_colliders[i]->GetOwner(), _colliders[j]->GetOwner());
            }
        }
    }

    //ダイナミックボディの更新
    for (auto& dynamicBody : _dynamicBodies)
    {
        dynamicBody->SystemUpdate();
    }
}

void PhysicsManager::AddDynamicBody(std::shared_ptr<DynamicBody> dynamicBody)
{
    _dynamicBodies.push_back(dynamicBody);
}

void PhysicsManager::RemoveDynamicBody(std::shared_ptr<DynamicBody> dynamicBody)
{
    _dynamicBodies.erase(std::remove(_dynamicBodies.begin(), _dynamicBodies.end(), dynamicBody), _dynamicBodies.end());
}

void PhysicsManager::AddCollider(std::shared_ptr<BoxCollider> collider)
{
    _colliders.push_back(collider);
}

void PhysicsManager::RemoveCollider(std::shared_ptr<BoxCollider> collider)
{
    _colliders.erase(std::remove(_colliders.begin(), _colliders.end(), collider), _colliders.end());
}

bool PhysicsManager::Release()
{
    return true;
}

void PhysicsManager::HandleCollision(GameObject* objA, GameObject* objB)
{
    //TODO::衝突時の処理
}