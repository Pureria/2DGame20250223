#pragma once
#include "IColliderManager.cpp"
#include <vector>

class ColliderManager
{
private:
	std::vector<std::shared_ptr<BoxCollider>> _colliders;

	void HandleCollision(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB);

public:
	ColliderManager();
	~ColliderManager();
	void AddCollider(std::shared_ptr<BoxCollider> collider);
	void RemoveCollider(std::shared_ptr<BoxCollider> collider);
	void Update();
};

