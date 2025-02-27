#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "PhysicsManager.h"

BoxCollider::BoxCollider(sf::Vector2f centerPos, sf::Vector2f size, GameObject* owner)
{
	_centerPos = centerPos;
	_size = size;
	_owner = owner;
	_nextHandlerID = 0;
	_SetPositionCallbackID = 0;
}

BoxCollider::~BoxCollider()
{	
}

void BoxCollider::Initialize()
{
	//コライダーマネージャーに自分を追加
	PhysicsManager::Instance().AddCollider(shared_from_this());
	
	//オーナーのSetPosition関数にSetPositionを登録
	_SetPositionCallbackID = _owner->AddSetPositionCallback([this](sf::Vector2f pos) {this->SetCenterPosition(pos); });
}

void BoxCollider::DebugDraw()
{
}

void BoxCollider::Update()
{
}

void BoxCollider::SetCenterPosition(sf::Vector2f pos)
{
	_centerPos = pos;
}

bool BoxCollider::IsColliding(BoxCollider& other) const
{
	std::array<sf::Vector2f, 4> vertices = GetRotatedVertices();
	std::array<sf::Vector2f, 4> otherVertices = other.GetRotatedVertices();

	//SATを使用してOBB同士の衝突判定
	//各オブジェクトの辺の法線を計算
	std::array<sf::Vector2f, 4> axes = {
		sf::Vector2f(1, 0),
		sf::Vector2f(0, 1),
		sf::Vector2f(-1, 0),
		sf::Vector2f(0, -1)
	};

	for(const auto& axis : axes)
	{
		//各頂点を投影
		float minA = std::numeric_limits<float>::max();
		float maxA = std::numeric_limits<float>::lowest();
		for(const auto& vertex : vertices)
		{
			float projection = vertex.x * axis.x + vertex.y * axis.y;
			minA = std::min(minA, projection);
			maxA = std::max(maxA, projection);
		}

		float minB = std::numeric_limits<float>::max();
		float maxB = std::numeric_limits<float>::lowest();
		for (const auto& vertex : otherVertices)
		{
			float projection = vertex.x * axis.x + vertex.y * axis.y;
			minB = std::min(minB, projection);
			maxB = std::max(maxB, projection);
		}

		//重なりをチェック
		if (maxA < minB || maxB < minA)
		{
			//重なっていない
			return false;
		}

		//一番移動量が少ない方向を求める
		float overlapA = maxB - minA;
		float overlapB = maxA - minB;
		float overlap = std::min(overlapA, overlapB);
	}

	return true;
}

//AABBでの衝突判定
sf::Vector2f BoxCollider::CalculatePushOut(const BoxCollider& other)
{
	//AABBでの衝突判定
	sf::Vector2f otherPos = other.GetCenterPosition();
	sf::Vector2f otherSize = other.GetSize();
	
	//自分の位置と相手の位置を比較して当たっているか判定
	float overlapX = std::min(_centerPos.x + _size.x, otherPos.x + otherSize.x) -
						std::max(_centerPos.x, otherPos.x);

	float overlapY = std::min(_centerPos.y + _size.y, otherPos.y + otherSize.y) -
						std::max(_centerPos.y, otherPos.y);

	if (overlapX == overlapY) {
		return sf::Vector2f(overlapX, 0);
	}

	//X軸とY軸の重なり具合を比較して、どちらを押し戻すか決める
	if (overlapX < overlapY)
	{
		//X軸の重なり具合がY軸より小さい場合
		//X軸の重なり具合を元に押し戻す方向を決める
		if (_centerPos.x < otherPos.x)
		{
			//自分が左にある場合
			return sf::Vector2f(-overlapX, 0);
		}
		else
		{
			//自分が右にある場合
			return sf::Vector2f(overlapX, 0);
		}
	}
	else
	{
		//Y軸の重なり具合がX軸より小さい場合
		//Y軸の重なり具合を元に押し戻す方向を決める
		if (_centerPos.y < otherPos.y)
		{
			//自分が上にある場合
			return sf::Vector2f(0, -overlapY);
		}
		else
		{
			//自分が下にある場合
			return sf::Vector2f(0, overlapY);
		}
	}
}

//OBBでの衝突判定
bool BoxCollider::CalculatePenetrationOBB(const BoxCollider& other, sf::Vector2f& penetration) const
{
	//それぞれOBBの回転軸を取得
	std::vector<sf::Vector2f> axes = GetSeparatingAxes(other);
	float minOverlap = std::numeric_limits<float>::max();
	sf::Vector2f bestAxis;

	//各軸で投影して重なり具合を計算
	for(const auto& axis: axes)
	{
		float minA, maxA, minB, maxB;
		ProjectOntoAxis(axis, minA, maxA);
		other.ProjectOntoAxis(axis, minB, maxB);

		//重なり具合を計算
		if(maxA < minB || maxB < minA)
		{			
			return false; //重なっていない
		}

		//オーバーラップ量を計算
		float overlap = std::min(maxA, maxB) - std::max(minA, minB);
		if(overlap < minOverlap)
		{
			minOverlap = overlap;
			bestAxis = axis;
		}
	}

	//最もオーバーラップが小さい軸を押し出しベクトルとする
	penetration = bestAxis * minOverlap;
	return true;
}

std::vector<sf::Vector2f> BoxCollider::GetSeparatingAxes(const BoxCollider& other) const
{
	std::vector<sf::Vector2f> axes;

	//自身のOBBの軸を取得
	axes.push_back(RotateVector(sf::Vector2f(1, 0), _owner->GetRotation()));
	axes.push_back(RotateVector(sf::Vector2f(0, 1), _owner->GetRotation()));

	//相手のOBBの軸を取得
	axes.push_back(RotateVector(sf::Vector2f(1, 0), other._owner->GetRotation()));
	axes.push_back(RotateVector(sf::Vector2f(0, 1), other._owner->GetRotation()));

	return axes;
}

void BoxCollider::ProjectOntoAxis(const sf::Vector2f& axis, float& min, float& max) const
{
	std::vector<sf::Vector2f> corners = GetTransformedCorners();
	min = max = DotProduct(corners[0], axis);

	for(int i = 1; i < 4; i++)
	{
		float projection = DotProduct(corners[i], axis);
		min = std::min(min, projection);
		max = std::max(max, projection);
	}
}

float BoxCollider::DotProduct(const sf::Vector2f& a, const sf::Vector2f& b) const { return a.x * b.x + a.y * b.y; }

std::vector<sf::Vector2f> BoxCollider::GetTransformedCorners() const
{
	std::vector<sf::Vector2f> corners;
	sf::Vector2f center = _owner->GetCenterPosition();
	sf::Vector2f halfSize = _size * 0.5f;
	float rotation = _owner->GetRotation();

	corners.push_back(RotateVector(sf::Vector2f(-halfSize.x, -halfSize.y), rotation) + center);
	corners.push_back(RotateVector(sf::Vector2f(halfSize.x, -halfSize.y), rotation) + center);
	corners.push_back(RotateVector(sf::Vector2f(halfSize.x, halfSize.y), rotation) + center);
	corners.push_back(RotateVector(sf::Vector2f(-halfSize.x, halfSize.y), rotation) + center);

	return corners;
}

sf::Vector2f BoxCollider::RotateVector(const sf::Vector2f& vec, float angle) const
{
	float rad = angle * 3.14159265f / 180.0f;
	float cosA = std::cos(rad);
	float sinA = std::sin(rad);

	return sf::Vector2f(
		vec.x * cosA - vec.y * sinA,
		vec.x * sinA + vec.y * cosA
	);
}



void BoxCollider::OnCollision(GameObject* other)
{
	//コールバック関数を呼び出す
	for (auto& handler : _collisionHandlers)
	{
		handler.second(_owner, other);
	}
}

int BoxCollider::AddCollisionHandler(CollisionCallback callback)
{
	int id = _nextHandlerID++;
	_collisionHandlers[id] = callback;
	return id;
}

void BoxCollider::RemoveCollisionHandler(int id)
{
	auto it = _collisionHandlers.find(id);
	if (it != _collisionHandlers.end()) {
		_collisionHandlers.erase(it);
	}
	else {
		// IDが見つからなかった場合のログ出力（デバッグ用）
		DebugManager::LogWarning("Attempted to remove non-existent collision handler with ID " + std::to_string(id));
	}
}

void BoxCollider::Release()
{
	//コライダーマネージャーから自分を削除
	PhysicsManager::Instance().RemoveCollider(shared_from_this());

	//オーナーのSetPosition関数に登録したコールバックを削除
	_owner->RemoveSetPositionCallback(_SetPositionCallbackID);
}

std::array<sf::Vector2f, 4> BoxCollider::GetRotatedVertices() const
{
	//OBBの四隅を計算
	//この時点では回転していない状態
	sf::Vector2f size = _size * 0.5f;
	std::array<sf::Vector2f, 4> vertives = {
		_centerPos + sf::Vector2f(-size.x, size.y),
		_centerPos + sf::Vector2f(size.x, size.y),
		_centerPos + sf::Vector2f(-size.x, -size.y),
		_centerPos + sf::Vector2f(size.x, -size.y)
	};

	//OBBを回転させる計算
	float angle = _owner->GetRotation();
	for (auto& vertex : vertives)
	{
		/*
		回転行列を使って回転させる
		回転行列 : |cosθ, -sinθ|
		          |sinθ, cosθ |	*/
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);
		vertex = sf::Vector2f(
			vertex.x * cosA - vertex.y * sinA,
			vertex.x * sinA + vertex.y * cosA
		);
	}

	return vertives;
}