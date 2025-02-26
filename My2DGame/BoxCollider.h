#pragma once
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>
#include <array>
#include <unordered_map>
#include "Component.h"

class GameObject; //ëOï˚êÈåæ
using CollisionCallback = std::function<void(GameObject*, GameObject*)>;

class BoxCollider : public std::enable_shared_from_this<BoxCollider>, public Component
{
private:
	GameObject* _owner;
	sf::Vector2f _centerPos, _size;
	int _nextHandlerID;
	int _SetPositionCallbackID;
	std::unordered_map <int, CollisionCallback> _collisionHandlers;

public:

	BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject* owner);
	~BoxCollider();

	void Initialize()override;
	void DebugDraw() override;
	void Update() override;
	void Release() override;

	void SetCenterPosition(sf::Vector2f pos);
	void OnCollision(GameObject* other);
	int AddCollisionHandler(CollisionCallback callback);
	void RemoveCollisionHandler(int id);
	bool IsColliding(BoxCollider& other) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetCenterPosition() const;
	sf::Vector2f CalculatePushOut(const BoxCollider& other);
	std::array<sf::Vector2f, 4> GetRotatedVertices() const;
	GameObject* GetOwner();
};

inline sf::Vector2f BoxCollider::GetCenterPosition() const { return _centerPos; }
inline sf::Vector2f BoxCollider::GetSize() const { return _size; }
inline GameObject* BoxCollider::GetOwner() { return _owner; }