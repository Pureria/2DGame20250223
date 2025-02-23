#pragma once
//#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "Rectangle.h"

class GameApp
{
private:
	Rectangle* rectangle = nullptr;
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

