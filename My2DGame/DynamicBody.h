#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <cmath>

//#include "DynamicBodyManager.h"
#include "Component.h"

class GameObject; //ëOï˚êÈåæ
const float GRAVITY = 9.8f;

//AddÇ©SetÇ»ÇÃÇ©ÇãÊï Ç∑ÇÈenum
enum class ForceMode
{
	ADD,
	SET
};

class DynamicBody : public std::enable_shared_from_this<DynamicBody>, public Component
{
private:
	GameObject* _owner;
	float _gravityScale;
	float _drag;
	bool _isStatic;
	sf::Vector2f _velocity;

	void DragUpdate(float deltaTime);

public:
	DynamicBody(float gravityScale, GameObject* owner);
	DynamicBody(float gravityScale, GameObject* owner, bool isStatic);
	~DynamicBody();

	void Initialize() override;
	void DebugDraw() override;
	void Update() override;
	void Release() override;

	void SystemUpdate();

	void SetGravityScale(float gravityScale);
	void SetVelocity(sf::Vector2f velocity, ForceMode mode);
	void SetIsGravityEnabled(bool isStatic);
	void SetDrag(float drag);

	bool GetIsStatic() const;
	float GetGravityScale() const;
	float GetDrag() const;
	sf::Vector2f GetVelocity() const;
	GameObject* GetOwner();
};

inline float DynamicBody::GetGravityScale() const { return _gravityScale; }
inline sf::Vector2f DynamicBody::GetVelocity() const { return _velocity; }
inline GameObject* DynamicBody::GetOwner() { return _owner; }
inline bool DynamicBody::GetIsStatic() const { return _isStatic; }
inline float DynamicBody::GetDrag() const { return _drag; }