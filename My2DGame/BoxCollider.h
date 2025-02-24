#pragma once
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <memory>

class GameObject; //ëOï˚êÈåæ

class BoxCollider : public std::enable_shared_from_this<BoxCollider>
{
private:
	GameObject* _owner;
	sf::Vector2f _pos, _size;

public:
	BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject* owner);
	~BoxCollider();
	void Initialize();
	void DebugDraw();
	void SetPosition(sf::Vector2f pos);
	void Release();
	bool IsColliding(BoxCollider& other) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f CalculatePushOut(const BoxCollider& other);
	GameObject* GetOwner();
};

inline sf::Vector2f BoxCollider::GetPosition() const { return _pos; }
inline sf::Vector2f BoxCollider::GetSize() const { return _size; }
inline GameObject* BoxCollider::GetOwner() { return _owner; }