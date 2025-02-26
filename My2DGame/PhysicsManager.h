#pragma once
#include <memory>

#include "Singleton.h"
#include <vector>

class BoxCollider;
class DynamicBody;
class GameObject;

class PhysicsManager : public Singleton<PhysicsManager>
{
private:
    std::vector<std::shared_ptr<BoxCollider>> _colliders;
    std::vector<std::shared_ptr<DynamicBody>> _dynamicBodies;
    
public:
    PhysicsManager();
    ~PhysicsManager();

    void Update();
    void AddDynamicBody(std::shared_ptr<DynamicBody> dynamicBody);
    void RemoveDynamicBody(std::shared_ptr<DynamicBody> dynamicBody);
    void AddCollider(std::shared_ptr<BoxCollider> collider);
    void RemoveCollider(std::shared_ptr<BoxCollider> collider);

    bool Release() override;
    void HandleCollision(GameObject* objA, GameObject* objB);
};
