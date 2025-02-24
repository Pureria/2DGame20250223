#pragma once
#include "SFML/System/Vector2.hpp"
#include <memory>
#include "BoxCollider.h"
#include "DynamicBody.h"

class GameObject
{
private:
	sf::Vector2f _pos;
	std::shared_ptr<BoxCollider> _collider;
	std::shared_ptr<DynamicBody> _dynamicBody;
	bool _isMovable; //“®‚©‚¹‚é‚©‚Ç‚¤‚©

public:
	GameObject(sf::Vector2f pos, sf::Vector2f size, bool isMovable);
	~GameObject();
	void AddPosition(sf::Vector2f delta);
	void SetPosition(sf::Vector2f pos);
	void Move(sf::Vector2f dir, ForceMode mode);
	void Release();
	sf::Vector2f GetPosition() const;
	std::shared_ptr<BoxCollider> GetCollider() const;
	std::shared_ptr<DynamicBody> GetDynamicBody() const;
	bool IsMoveAble() const { return _isMovable; }
};

inline sf::Vector2f GameObject::GetPosition() const { return _pos; }
inline std::shared_ptr<BoxCollider> GameObject::GetCollider() const { return _collider; }
inline std::shared_ptr<DynamicBody> GameObject::GetDynamicBody() const { return _dynamicBody; }