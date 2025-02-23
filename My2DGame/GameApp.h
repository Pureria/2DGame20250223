#pragma once
#include <SFML/Graphics.hpp>

class GameApp
{
private:
	sf::RenderWindow& _window;
	sf::RectangleShape* rectangle;
	bool _isDebugRender;

public:
	GameApp(sf::RenderWindow& win);
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

