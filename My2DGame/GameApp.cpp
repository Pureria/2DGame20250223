#include "GameApp.h"

GameApp::GameApp()
{
	rectangle = nullptr;
	_isDebugRender = false;
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
	WindowManager::Instance().GetWindow().clear(sf::Color::Blue);
	WindowManager::Instance().GetWindow().draw(*rectangle);

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