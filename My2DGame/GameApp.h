#pragma once
//#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "FillRect.h"
#include "Rect.h"
#include "Timer.h"
#include "GameObject.h"
#include <memory>

class GameApp
{
private:
	bool _isDebugRender = false;

	//��
	GameObject* floor;
	Rect* floorRect;

	//�I�u�W�F�N�g1
	GameObject* obj1;
	Rect* obj1Rect;

public:
	GameApp();
	~GameApp();
	bool Awake();
	bool Start();
	bool Update();
	bool LateUpdate();
	bool Render();
	bool RederDebug();
	bool Release();

	bool IsDebugRender() const;
};

inline bool GameApp::IsDebugRender() const { return _isDebugRender; }

