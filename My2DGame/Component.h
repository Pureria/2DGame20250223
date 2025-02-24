#pragma once

//コンポーネントの基底クラス
class Component
{
public:
	virtual ~Component() = default;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void DebugDraw() = 0;
};