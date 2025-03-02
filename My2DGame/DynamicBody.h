#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <cmath>

//#include "DynamicBodyManager.h"
#include "Component.h"

class GameObject; //前方宣言
const float GRAVITY = 9.8f;
const float PI = 3.14159265f;
const float Damping = 0.98f;

class DynamicBody : public std::enable_shared_from_this<DynamicBody>, public Component
{
private:
	bool _isStatic; //静的かどうか
	
	GameObject* _owner;
	sf::Vector2f _velocity;
	sf::Vector2f _acceleration;
	
	float _mass; //質量
	float _inertia; //慣性モーメント
	float _angularVelocity; //角速度
	float _torque; //トルク

	float _gravityScale;
	
	float GetRadian(float degrees) const;
	float GetDegrees(float radian) const;
public:
	DynamicBody(float gravityScale, GameObject* owner);
	DynamicBody(float gravityScale, GameObject* owner, bool isStatic);
	DynamicBody(float gravityScale, GameObject* owner, bool isStatic, float mass, float inertia);
	~DynamicBody() override;

	void Initialize() override;
	void DebugDraw() override;
	void Update() override;
	void SystemUpdate();
	void Release() override;
	
	GameObject* GetOwner();
	sf::Vector2f GetVelocity() const;
	
	//慣性モーメントの取得
	//矩形の慣性モーメントの計算
	static float CalculateRectangleInteria(float mass, float width, float height) {return (1 / 12.0f) * mass * (width * width + height * height);}

	//テスト用関数
	void ApplyTorque(float torque);

	void AddForce(const sf::Vector2f& force);
};

inline GameObject* DynamicBody::GetOwner() { return _owner; }
inline sf::Vector2f DynamicBody::GetVelocity() const { return _velocity; }

//ラジアンの取得
inline float DynamicBody::GetRadian(float degrees) const
{
	//0～2πに変換
	while (degrees < 0) degrees += 360;
	while (degrees >= 360) degrees -= 360;
	float angle = degrees * PI / 180.0f;
	return angle;
}

//角度の取得
inline float DynamicBody::GetDegrees(float radian) const
{
	float angle = radian * 180.0f / PI;
	//0～360度に変換
	while (angle < 0) angle += 360;
	while (angle >= 360) angle -= 360;	
	return angle;
}

//トルクの適用
inline void DynamicBody::ApplyTorque(float torque)
{
	_torque += torque;
}