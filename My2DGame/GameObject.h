#pragma once
#include "SFML/System/Vector2.hpp"
#include <memory>

class BoxCollider; //ëOï˚êÈåæ

class GameObject
{
private:
	sf::Vector2f _pos;
	std::shared_ptr<BoxCollider> _collider;
	bool _isMovable;

public:
	GameObject(sf::Vector2f pos, sf::Vector2f size, bool isMovable);
	~GameObject();
	void Move(sf::Vector2f delta);
	void SetPosition(sf::Vector2f pos);
	void Release();
	sf::Vector2f GetPosition() const;
	std::shared_ptr<BoxCollider> GetCollider() const;
	bool IsMoveAble() const { return _isMovable; }
};

inline sf::Vector2f GameObject::GetPosition() const { return _pos; }
inline std::shared_ptr<BoxCollider> GameObject::GetCollider() const { return _collider; }

