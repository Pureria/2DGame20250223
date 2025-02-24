#pragma once

//�R���|�[�l���g�̊��N���X
class Component
{
public:
	virtual ~Component() = default;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void DebugDraw() = 0;
};