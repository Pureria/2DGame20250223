#include "GameApp.h"

GameApp::GameApp(sf::RenderWindow& win) :_window(win)
{
	_isDebugRender = false;
	//rectangle = new sf::RectangleShape(sf::Vector2f(300, 100));
}

GameApp::~GameApp()
{
}

bool GameApp::Awake()
{
	return true;
}

bool GameApp::Start()
{
	//ŽlŠpŒ`‚ðì¬
	rectangle = new sf::RectangleShape(sf::Vector2f(300, 100));
	rectangle->setFillColor(sf::Color::Red);
	rectangle->setPosition(0, 0);

	return true;
}

bool GameApp::Update()
{
	return true;
}

bool GameApp::LateUpdate()
{
	return true;
}

bool GameApp::Render()
{
	
	_window.draw(*rectangle);

	return true;
}

bool GameApp::RederDebug()
{
	return true;
}

bool GameApp::Release()
{
	delete rectangle;

	return true;
}