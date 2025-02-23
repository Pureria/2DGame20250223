#pragma once
#include <SFML/System/Vector2.hpp>

class GameObject; //ëOï˚êÈåæ

class BoxCollider
{
private:
	GameObject* _owner;
	sf::Vector2f _pos, _size;

public:
	BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject& owner);
	~BoxCollider();
	void DebugDraw();
	void SetPosition(sf::Vector2f pos);
	bool IsColliding(BoxCollider& other) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;
	GameObject* GetOwner() { return _owner; }
};

inline sf::Vector2f BoxCollider::GetPosition() const { return _pos; }
inline sf::Vector2f BoxCollider::GetSize() const { return _size; }