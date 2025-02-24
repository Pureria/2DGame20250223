#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderManager.h"

BoxCollider::BoxCollider(sf::Vector2f pos, sf::Vector2f size, GameObject* owner)
{
	_pos = pos;
	_size = size;
	_owner = owner;
	
}

BoxCollider::~BoxCollider()
{	
}

void BoxCollider::Initialize()
{
	//コライダーマネージャーに自分を追加
	ColliderManager::Instance().AddCollider(shared_from_this());
}

void BoxCollider::DebugDraw()
{
}

void BoxCollider::SetPosition(sf::Vector2f pos)
{
	_pos = pos;
}

bool BoxCollider::IsColliding(BoxCollider& other) const
{
	//相手の位置とサイズを取得
	sf::Vector2f otherPos = other.GetPosition();
	sf::Vector2f otherSize = other.GetSize();

	//自分の位置と相手の位置を比較して当たっているか判定
	if (_pos.x < otherPos.x + otherSize.x &&	//自分の右端が相手の左端よりも左にある
		_pos.x + _size.x > otherPos.x &&		//自分の左端が相手の右端よりも右にある
		_pos.y < otherPos.y + otherSize.y &&	//自分の下端が相手の上端よりも上にある
		_pos.y + _size.y > otherPos.y)			//自分の上端が相手の下端よりも下にある
	{
		return true;
	}
	return false;
}

sf::Vector2f BoxCollider::CalculatePushOut(const BoxCollider& other)
{
	//AABBでの衝突判定
	sf::Vector2f otherPos = other.GetPosition();
	sf::Vector2f otherSize = other.GetSize();
	
	//自分の位置と相手の位置を比較して当たっているか判定
	float overlapX = std::min(_pos.x + _size.x, otherPos.x + otherSize.x) - 
						std::max(_pos.x, otherPos.x);

	float overlapY = std::min(_pos.y + _size.y, otherPos.y + otherSize.y) -
						std::max(_pos.y, otherPos.y);

	//X軸とY軸の重なり具合を比較して、どちらを押し戻すか決める
	if (overlapX < overlapY)
	{
		//X軸の重なり具合がY軸より小さい場合
		//X軸の重なり具合を元に押し戻す方向を決める
		if (_pos.x < otherPos.x)
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
		if (_pos.y < otherPos.y)
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

void BoxCollider::Release()
{
	//コライダーマネージャーから自分を削除
	ColliderManager::Instance().RemoveCollider(shared_from_this());
}