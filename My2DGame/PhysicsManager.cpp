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
    sf::Vector2f penetration;
    // 衝突判定
    // 二重ループで全てのコライダーの組み合わせをチェック
    for (size_t i = 0; i < _colliders.size(); i++)
    {
        for (size_t j = i + 1; j < _colliders.size(); j++)
        {
            if (_colliders[i]->CalculatePenetrationOBB(*_colliders[j], penetration))
            {
                HandleCollision(_colliders[i]->GetOwner(), _colliders[j]->GetOwner(), penetration);
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

void PhysicsManager::HandleCollision(GameObject* objA, GameObject* objB, sf::Vector2f penetration)
{
    auto bodyA = objA->GetComponent<DynamicBody>();
    auto bodyB = objB->GetComponent<DynamicBody>();
    if(!bodyA || !bodyB) return;

    auto colliderA = objA->GetComponent<BoxCollider>();
    auto colliderB = objB->GetComponent<BoxCollider>();
    if(!colliderA || !colliderB) return;

    //押し出し処理
    float totalMass = bodyA->GetMass() + bodyB->GetMass();
    if (totalMass > 0)
    {
        // 片方がstaticの場合、もう片方のみ移動
        if (bodyA->GetIsStatic() && !bodyB->GetIsStatic())
        {
            objB->SetCenterPosition(objB->GetCenterPosition() + (penetration * -1.0f));
        }
        else if (!bodyA->GetIsStatic() && bodyB->GetIsStatic())
        {
            objA->SetCenterPosition(objA->GetCenterPosition() - (penetration * -1.0f));
        }
        else if (!bodyA->GetIsStatic() && !bodyB->GetIsStatic())
        {
            // 両方がdynamicの場合は、両方を押し出し
            objA->SetCenterPosition(objA->GetCenterPosition() - penetration * (bodyB->GetMass() / totalMass));
            objB->SetCenterPosition(objB->GetCenterPosition() + penetration * (bodyA->GetMass() / totalMass));
        }
    }

    /*********************************衝突したオブジェクトの反発**********************/
    //衝突時の情報を取得
    sf::Vector2f contactPoint = (objA->GetCenterPosition() + objB->GetCenterPosition()) * 0.5f; //衝突点
    //衝突時の法線ベクトルを求める
    sf::Vector2f normal = objB->GetCenterPosition() - objA->GetCenterPosition();
    normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y); //正規化

    //弾性係数と質量の取得
    float elasticity = (bodyA->GetElasticity() + bodyB->GetElasticity()) * 0.5f; //弾性係数の平均
    float massA = bodyA->GetMass(), massB = bodyB->GetMass(); //質量

    //相対速度
    sf::Vector2f relativeVelocity = bodyB->GetVelocity() - bodyA->GetVelocity();//２つのオブジェクトの速度差（相対速度）

    //角速度と慣性モーメントの取得
    float angularVelocityA = bodyA->GetAngularVelocity();
    float angularVelocityB = bodyB->GetAngularVelocity();
    float inertiaA = bodyA->GetInertia();
    float inertiaB = bodyB->GetInertia();

    //接触点での速度の計算
    sf::Vector2f rA = contactPoint - objA->GetCenterPosition();
    sf::Vector2f rB = contactPoint - objB->GetCenterPosition();
    sf::Vector2f velocityA = bodyA->GetVelocity() + sf::Vector2f(-rA.y * angularVelocityA, rA.x * angularVelocityA);
    sf::Vector2f velocityB = bodyB->GetVelocity() + sf::Vector2f(-rB.y * angularVelocityB, rB.x * angularVelocityB);
    relativeVelocity = velocityB - velocityA;
    
    //インパルスの大きさを計算
    float impulseMagunitude = -(1.0f + elasticity) * (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y);
    impulseMagunitude /= (1.0f / massA + 1.0f / massB + (rA.x * normal.y - rA.y * normal.x) * (rA.x * normal.y - rA.y * normal.x) / inertiaA + (rB.x * normal.y - rB.y * normal.x) * (rB.x * normal.y - rB.y * normal.x) / inertiaB); //インパルスの大きさ

    sf::Vector2f impulse = impulseMagunitude * normal; //大きさと方向を持つインパルス

    // インパルスを適用
    if (!bodyA->GetIsStatic())
    {
        bodyA->ApplyImpulse(-impulse, contactPoint);
        bodyA->ApplyAngularImpulse(-(rA.x * impulse.y - rA.y * impulse.x));
    }
    if (!bodyB->GetIsStatic())
    {
        bodyB->ApplyImpulse(impulse, contactPoint);
        bodyB->ApplyAngularImpulse(rB.x * impulse.y - rB.y * impulse.x);
    }
    /********************************************************************/

    //衝突時のコールバックを呼び出し
    colliderA->OnCollision(objB);
    colliderB->OnCollision(objA);
}