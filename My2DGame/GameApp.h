#pragma once
//#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "FillRect.h"
#include "Rect.h"
#include "GameObject.h"
#include <memory>

class GameApp
{
private:
	FillRect* rec1 = nullptr;
	FillRect* rec2 = nullptr;
	FillRect* floorRec = nullptr;

	GameObject* obj1 = nullptr;
	GameObject* obj2 = nullptr;
	GameObject* floorObj = nullptr;

	bool _isDebugRender = false;

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

