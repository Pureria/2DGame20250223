#include "GameApp.h"

GameApp::GameApp()
{
	rectangle = nullptr;
	_isDebugRender = false;
}

GameApp::~GameApp()
{
	Release();
}

bool GameApp::Awake()
{
	return true;
}

bool GameApp::Start()
{
	//ŽlŠpŒ`‚ðì¬
	rectangle = new Rectangle(sf::Vector2f(300, 100));
	rectangle->SetPosition(sf::Vector2f(0, 0));
	rectangle->SetFillColor(sf::Color::Red);

	return true;
}

bool GameApp::Update()
{
	sf::Vector2f pos = rectangle->GetPosition();
	pos.x += 0.05f;
	if (pos.x > 800)
	{
		pos.x = 0;
		rectangle->SetFillColor(sf::Color::Yellow);
	}

	pos.y += 0.05f;
	if (pos.y > 600)
	{
		pos.y = 0;
		rectangle->SetFillColor(sf::Color::Red);
	}

	rectangle->SetPosition(pos);

	return true;
}

bool GameApp::LateUpdate()
{
	return true;
}

bool GameApp::Render()
{
	WindowManager::Instance().GetWindow().clear(sf::Color::Blue);

	rectangle->Render();

	return true;
}

bool GameApp::RederDebug()
{
	return true;
}

bool GameApp::Release()
{
	if (rectangle != nullptr)
	{
		rectangle->Release();
		rectangle = nullptr;
	}
	return true;
}