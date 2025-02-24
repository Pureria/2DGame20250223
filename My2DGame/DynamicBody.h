#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>

class GameObject; //ëOï˚êÈåæ

class DynamicBody : public std::enable_shared_from_this<DynamicBody>
{
private:
	GameObject* _owner;
	float _gravityScale;
	bool _isGrounded;
	bool _isGravityEnabled;
	sf::Vector2f _velocity;

public:
	DynamicBody(float gravityScale, GameObject* owner);
	DynamicBody(float gravityScale, GameObject* owner, bool isGravity);
	~DynamicBody();
	void DebugDraw();
	void Update();
	void Release();

	void SetGravityScale(float gravityScale);
	void SetVelocity(sf::Vector2f velocity);
	void SetIsGrounded(bool isGrounded);
	void SetIsGravityEnabled(bool isGravity);

	bool GetIsGrounded() const;
	bool GetIsGravityEnabled() const;
	float GetGravityScale() const;
	sf::Vector2f GetVelocity() const;
	GameObject* GetOwner();
};

inline float DynamicBody::GetGravityScale() const { return _gravityScale; }
inline sf::Vector2f DynamicBody::GetVelocity() const { return _velocity; }
inline GameObject* DynamicBody::GetOwner() { return _owner; }
inline bool DynamicBody::GetIsGrounded() const { return _isGrounded; }
inline bool DynamicBody::GetIsGravityEnabled() const { return _isGravityEnabled; }