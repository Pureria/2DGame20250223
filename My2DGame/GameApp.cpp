#include "GameApp.h"
#include "BoxCollider.h"

GameApp::GameApp()
{
	rec1 = nullptr;
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
	//éläpå`ÇçÏê¨
	obj1 = new GameObject(sf::Vector2f(100, 100), sf::Vector2f(100, 100), true);
	//obj1 = std::make_shared<GameObject>(sf::Vector2f(100, 100), sf::Vector2f(100, 100), true);
	rec1 = new Rectangle(obj1->GetCollider()->GetSize());
	rec1->SetPosition(obj1->GetPosition());
	rec1->SetFillColor(sf::Color::Red);

	obj2 = new GameObject(sf::Vector2f(500, 100), sf::Vector2f(100, 100), true);
	//obj2 = std::make_shared<GameObject>(sf::Vector2f(500, 100), sf::Vector2f(100, 100), true);
	rec2 = new Rectangle(obj2->GetCollider()->GetSize());
	rec2->SetPosition(obj2->GetPosition());
	rec2->SetFillColor(sf::Color::Green);

	return true;
}

bool GameApp::Update()
{
	sf::Vector2f pos = obj1->GetPosition();
	pos.x += 0.05f;
	obj1->SetPosition(pos);
	rec1->SetPosition(obj1->GetPosition());

	sf::Vector2f pos2 = obj2->GetPosition();
	pos2.x -= 0.05f;
	obj2->SetPosition(pos2);
	rec2->SetPosition(obj2->GetPosition());

	if (pos.x + obj1->GetCollider()->GetSize().x >= pos2.x)
	{
		int hoge = 0;
	}

	return true;
}

bool GameApp::LateUpdate()
{
	return true;
}

bool GameApp::Render()
{
	WindowManager::Instance().GetWindow().clear(sf::Color::Blue);

	rec1->Render();
	rec2->Render();

	return true;
}

bool GameApp::RederDebug()
{
	return true;
}

bool GameApp::Release()
{
	if (rec1 != nullptr)
	{
		rec1->Release();
		delete rec1;
		rec1 = nullptr;
	}

	if (rec2 != nullptr)
	{
		rec2->Release();
		delete rec2;
		rec2 = nullptr;
	}

	obj1->Release();
	obj2->Release();

	//obj1.reset();
	//obj2.reset();
	delete obj1;
	delete obj2;

	return true;
}