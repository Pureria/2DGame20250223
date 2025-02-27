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
    // �Փ˔���
    // ��d���[�v�őS�ẴR���C�_�[�̑g�ݍ��킹���`�F�b�N
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

    //�_�C�i�~�b�N�{�f�B�̍X�V
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
    auto bodyA = objA->GetComponent<DynamicBody>();
    auto bodyB = objB->GetComponent<DynamicBody>();
    if(!bodyA || !bodyB) return;

    auto colliderA = objA->GetComponent<BoxCollider>();
    auto colliderB = objB->GetComponent<BoxCollider>();
    if(!colliderA || !colliderB) return;

    sf::Vector2f penetration;
    if(!colliderA->CalculatePenetrationOBB(*colliderB, penetration)) return;

    //�����o������
    float totalMass = bodyA->GetMass() + bodyB->GetMass();
    if (totalMass > 0)
    {
        // �Е���static�̏ꍇ�A�����Е��݈̂ړ�
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
            // ������dynamic�̏ꍇ�́A�����������o��
            objA->SetCenterPosition(objA->GetCenterPosition() - penetration * (bodyB->GetMass() / totalMass));
            objB->SetCenterPosition(objB->GetCenterPosition() + penetration * (bodyA->GetMass() / totalMass));
        }
    }

    //�Փˎ��̖@���x�N�g�������߂�
    sf::Vector2f normal = objB->GetCenterPosition() - objA->GetCenterPosition();
    normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y); //���K��

    float elasticity = (bodyA->GetElasticity() + bodyB->GetElasticity()) * 0.5f;
    float massA = bodyA->GetMass(), massB = bodyB->GetMass();

    //���Α��x
    sf::Vector2f relativeVelocity = bodyB->GetVelocity() - bodyA->GetVelocity();
    float impulseMagunitude = -(1.0f + elasticity) * (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y);
    impulseMagunitude /= (1.0f / massA + 1.0f / massB);

    sf::Vector2f impulse = impulseMagunitude * normal;
    sf::Vector2f contactPoint = (objA->GetCenterPosition() + objB->GetCenterPosition()) * 0.5f;

    // �C���p���X��K�p
    if (!bodyA->GetIsStatic())
    {
        bodyA->ApplyImpulse(-impulse, contactPoint);
    }
    if (!bodyB->GetIsStatic())
    {
        bodyB->ApplyImpulse(impulse, contactPoint);
    }

    //�Փˎ��̃R�[���o�b�N���Ăяo��
    colliderA->OnCollision(objB);
    colliderB->OnCollision(objA);
}