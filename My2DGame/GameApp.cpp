#include "GameApp.h"
#include "BoxCollider.h"
#include "DynamicBody.h"

GameApp::GameApp()
{
	_isDebugRender = true;
}

GameApp::~GameApp()
{
}

bool GameApp::Awake()
{
	_fillRect = new FillRect(sf::Vector2f(100, 100));
	_fillRect->SetCenterPosition(sf::Vector2f(100, 100));
	_fillRect->SetColor(sf::Color::Red);
	_fillRect->SetRotation(0.0f);

	_rect = new Rect(sf::Vector2f(100, 100));
	_rect->SetCenterPosition(sf::Vector2f(400, 300));
	_rect->SetColor(sf::Color::Green);
	_rect->SetRotation(0.0f);
	_rect->SetLineSize(5.0f);
	
	return true;
}

bool GameApp::Start()
{
	return true;
}

bool GameApp::Update()
{
	float rotation = _fillRect->GetRotation();
	rotation += 1.0f * Timer::Instance().DeltaTime();
	if(rotation > 360.0f) rotation = 0.0f;
	_fillRect->SetRotation(rotation);

	rotation = _rect->GetRotation();
	rotation -= 1.0f * Timer::Instance().DeltaTime();
	if (rotation < 0.0f) rotation = 360.0f;
	_rect->SetRotation(rotation);
	
	return true;
}

bool GameApp::LateUpdate()
{
	return true;
}

bool GameApp::Render()
{
	WindowManager::Instance().GetWindow().clear(sf::Color::Blue);

	_fillRect->Render();
	_rect->Render();
	
	return true;
}

bool GameApp::RederDebug()
{
	return true;
}

bool GameApp::Release()
{
	if (_fillRect != nullptr)
	{
		_fillRect->Release();
		delete _fillRect;
		_fillRect = nullptr;
	}

	if (_rect != nullptr)
	{
		_rect->Release();
		delete _rect;
		_rect = nullptr;
	}
	
	return true;
}