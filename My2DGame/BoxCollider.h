#pragma once
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <iostream>

class GameObject; //ëOï˚êÈåæ
using CollisionCallback = std::function<void(GameObject*, GameObject*)>;

class BoxCollider : public std::enable_shared_from_this<BoxCollider>
{
private:
	GameObject* _owner;
	sf::Vector2f _pos, _size;
	int _nextHandlerID;
	std::unordered_map <int, CollisionCallback> _collisionHandlers;

public:

	BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject* owner);
	~BoxCollider();
	void Initialize();
	void DebugDraw();
	void SetPosition(sf::Vector2f pos);
	void Release();
	void OnCollision(GameObject* other);
	int AddCollisionHandler(CollisionCallback callback);
	void RemoveCollisionHandler(int id);
	bool IsColliding(BoxCollider& other) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f CalculatePushOut(const BoxCollider& other);
	GameObject* GetOwner();
};

inline sf::Vector2f BoxCollider::GetPosition() const { return _pos; }
inline sf::Vector2f BoxCollider::GetSize() const { return _size; }
inline GameObject* BoxCollider::GetOwner() { return _owner; }