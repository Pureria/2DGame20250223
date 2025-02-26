#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <cmath>

//#include "DynamicBodyManager.h"
#include "Component.h"

class GameObject; //�O���錾
const float GRAVITY = 9.8f;

//Add��Set�Ȃ̂�����ʂ���enum
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
	float _angularDrag; //�p���x�̌�����
	float _angularVelocity; //�p���x(�x/�b)
	float _momentOfInertia; //�������[�����g
	float _mass; //����
	float _elasticity; //�e���W��
	bool _isStatic;
	sf::Vector2f _velocity;

	void DragUpdate(float deltaTime);
	void AngularDragUpdate(float deltaTime);

public:
	DynamicBody(float gravityScale, GameObject* owner);
	DynamicBody(float gravityScale, GameObject* owner, bool isStatic);
	~DynamicBody();

	void Initialize() override;
	void DebugDraw() override;
	void Update() override;
	void Release() override;

	void SystemUpdate();
	void ApplyImpulse(sf::Vector2f impulse, sf::Vector2f contactPoint);

	void SetGravityScale(float gravityScale);
	void SetVelocity(sf::Vector2f velocity, ForceMode mode);
	void SetAngularVelocity(float velocity, ForceMode mode); //�p���x�̐ݒ�
	void SetIsGravityEnabled(bool isStatic);
	void SetDrag(float drag);
	void SetAngularDrag(float drag); //�p���x�̌������̐ݒ�
	void SetElasticity(float elasticity);
	void SetMass(float mass);

	bool GetIsStatic() const;
	float GetGravityScale() const;
	float GetDrag() const;
	float GetAngularVelocity() const; //�p���x�̎擾
	float GetAngularDrag() const; //�p���x�̌������̎擾
	float GetElasticity() const;
	float GetMass() const;
	sf::Vector2f GetVelocity() const;
	GameObject* GetOwner();
};

inline float DynamicBody::GetGravityScale() const { return _gravityScale; }
inline sf::Vector2f DynamicBody::GetVelocity() const { return _velocity; }
inline float DynamicBody::GetAngularVelocity() const { return _angularVelocity; }
inline float DynamicBody::GetAngularDrag() const { return _angularDrag; }
inline GameObject* DynamicBody::GetOwner() { return _owner; }
inline bool DynamicBody::GetIsStatic() const { return _isStatic; }
inline float DynamicBody::GetDrag() const { return _drag; }
inline float DynamicBody::GetElasticity() const { return _elasticity; }
inline float DynamicBody::GetMass() const { return _mass; }