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
	//床の作成
	sf::Vector2u windowSize = WindowManager::Instance().GetWindowSize();
	floor = new GameObject(sf::Vector2f(windowSize.x * 0.5f, windowSize.y - 50.0f), sf::Vector2f(windowSize.x, 100));
	floor->AddComponent<BoxCollider>(floor->GetCenterPosition(), floor->GetSize(), floor);
	floor->AddComponent<DynamicBody>(1.0f, floor, true);
	floorRect = new Rect(sf::Vector2f(windowSize.x, 100));
	floorRect->SetColor(sf::Color::White);
	floorRect->SetCenterPosition(floor->GetCenterPosition());
	floorRect->SetLineSize(5.0f);

	//オブジェクト1の作成
	obj1 = new GameObject(sf::Vector2f(windowSize.x * 0.5f, 0), sf::Vector2f(100, 100));
	obj1->AddComponent<BoxCollider>(obj1->GetCenterPosition(), obj1->GetSize(), obj1);
	obj1->AddComponent<DynamicBody>(0.01f, obj1, false);
	obj1->SetRotation(45.0f);
	obj1Rect = new Rect(sf::Vector2f(100, 100));
	obj1Rect->SetColor(sf::Color::Red);
	obj1Rect->SetCenterPosition(obj1->GetCenterPosition());
	obj1Rect->SetLineSize(5.0f);
	
	//オブジェクト2の作成
	obj2 = new GameObject(sf::Vector2f(windowSize.x * 0.8f, 0), sf::Vector2f(100, 100));
	obj2->AddComponent<BoxCollider>(obj2->GetCenterPosition(), obj2->GetSize(), obj2);
	obj2->AddComponent<DynamicBody>(0.01f, obj2, true);
	obj2Rect = new Rect(sf::Vector2f(100, 100));
	obj2Rect->SetColor(sf::Color::Green);
	obj2Rect->SetCenterPosition(obj2->GetCenterPosition());
	obj2Rect->SetLineSize(5.0f);
	
	return true;
}

bool GameApp::Start()
{
	return true;
}

bool GameApp::Update()
{
	return true;
}

bool GameApp::LateUpdate()
{
	floorRect->SetCenterPosition(floor->GetCenterPosition());
	floorRect->SetRotation(floor->GetRotation());

	obj1Rect->SetCenterPosition(obj1->GetCenterPosition());
	obj1Rect->SetRotation(obj1->GetRotation());

	obj2Rect->SetCenterPosition(obj2->GetCenterPosition());
	obj2Rect->SetRotation(obj2->GetRotation());
	return true;
}

bool GameApp::Render()
{
	WindowManager::Instance().GetWindow().clear(sf::Color::Blue);

	obj1->Render();
	obj2->Render();
	floor->Render();
	
	floorRect->Render();
	obj1Rect->Render();
	obj2Rect->Render();
	return true;
}

bool GameApp::RederDebug()
{
	return true;
}

bool GameApp::Release()
{
	if(floorRect != nullptr)
	{
		floorRect->Release();
		delete floorRect;
		floorRect = nullptr;
	}

	if(obj1Rect != nullptr)
	{
		obj1Rect->Release();
		delete obj1Rect;
		obj1Rect = nullptr;
	}

	if(floor != nullptr)
	{
		floor->Release();
		delete floor;
		floor = nullptr;
	}

	if(obj1 != nullptr)
	{
		obj1->Release();
		delete obj1;
		obj1 = nullptr;
	}

	if(obj2Rect != nullptr)
	{
		obj2Rect->Release();
		delete obj2Rect;
		obj2Rect = nullptr;
		
	}

	if(obj2 != nullptr)
	{
		obj2->Release();
		delete obj2;
		obj2 = nullptr;
	}
	
	return true;
}