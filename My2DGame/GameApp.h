#pragma once
//#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "Rectangle.h"
#include "GameObject.h"
#include <memory>

class GameApp
{
private:
	Rectangle* rec1 = nullptr;
	Rectangle* rec2 = nullptr;

	std::shared_ptr<GameObject> obj1 = nullptr;
	std::shared_ptr<GameObject> obj2 = nullptr;

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

