#include "GameApp.h"
#include "BoxCollider.h"
#include "DynamicBody.h"

GameApp::GameApp()
{
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
	//四角形を作成
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

	floorObj = new GameObject(sf::Vector2f(0, 500), sf::Vector2f(800, 100), false);
	floorRec = new Rectangle(floorObj->GetCollider()->GetSize());
	floorRec->SetPosition(floorObj->GetPosition());
	floorRec->SetFillColor(sf::Color::White);

	return true;
}

bool GameApp::Update()
{
	
	sf::Vector2f velo = sf::Vector2f(1.0f, 0.0f);
	//veloの正規化
	float length = std::sqrt(velo.x * velo.x + velo.y * velo.y);
	velo.x /= length;
	velo.y /= length;
	velo *= 0.1f; //スピードを1.0にする
	velo.y = obj1->GetDynamicBody()->GetVelocity().y;
	obj1->Move(velo, ForceMode::SET);

	velo = sf::Vector2f(-1.0f, 0.0f);
	length = std::sqrt(velo.x * velo.x + velo.y * velo.y);
	velo.x /= length;
	velo.y /= length;
	velo *= 0.02f; //スピードを1.0にする
	velo.y = obj2->GetDynamicBody()->GetVelocity().y;
	obj2->Move(velo, ForceMode::SET);

	rec1->SetPosition(obj1->GetPosition());
	rec2->SetPosition(obj2->GetPosition());
	floorRec->SetPosition(floorObj->GetPosition());

	//obj1とobj2が画面端まで行ったら反対側へSetPositionで移動するように
	sf::Vector2u windowSize = WindowManager::Instance().GetWindowSize();

	bool outObj = false;
	if (obj1->GetPosition().x > windowSize.x) outObj = true;
	if (obj1->GetPosition().x + obj1->GetCollider()->GetSize().x < 0) outObj = true;
	if (obj1->GetPosition().y > windowSize.y - obj1->GetCollider()->GetSize().y) outObj = true;

	if (outObj)
	{
		obj1->SetPosition(sf::Vector2f(0, 0));
		obj1->Move(sf::Vector2f(0, 0), ForceMode::SET);
	}

	outObj = false;
	if (obj2->GetPosition().x > windowSize.x) outObj = true;
	if (obj2->GetPosition().x + obj2->GetCollider()->GetSize().x < 0) outObj = true;
	if (obj2->GetPosition().y > windowSize.y - obj2->GetCollider()->GetSize().y) outObj = true;

	if (outObj)
	{
		obj2->SetPosition(sf::Vector2f(600, 0));
		obj2->Move(sf::Vector2f(0, 0), ForceMode::SET);
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
	floorRec->Render();

	return true;
}

bool GameApp::RederDebug()
{
	return true;
}

bool GameApp::Release()
{
	/********Rectangleの解放********/
	rec1->Release();
	delete rec1;
	rec1 = nullptr;

	rec2->Release();
	delete rec2;
	rec2 = nullptr;
		
	floorRec->Release();
	delete floorRec;
	floorRec = nullptr;
	/*******************************/

	/******GameObjectの解放************/
	obj1->Release();
	delete obj1;
	obj1 = nullptr;

	obj2->Release();
	delete obj2;
	obj2 = nullptr;

	floorObj->Release();
	delete floorObj;
	floorObj = nullptr;
	/*********************************/

	return true;
}