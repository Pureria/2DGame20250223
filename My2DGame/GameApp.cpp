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
	return true;
}

bool GameApp::Start()
{
	//四角形を作成
	obj1 = new GameObject(sf::Vector2f(100, 100), sf::Vector2f(100, 100));
	obj1->AddComponent<BoxCollider>(sf::Vector2f(100, 100), sf::Vector2f(100, 100), obj1);
	obj1->AddComponent<DynamicBody>(0.05f, obj1, false);

	//TrygetComponentを使ってみる
	std::shared_ptr<BoxCollider> boxCollider;
	if (obj1->TryGetComponent<BoxCollider>(boxCollider))
	{
		rec1 = new Rectangle(boxCollider->GetSize());
		rec1->SetPosition(obj1->GetPosition());
		rec1->SetFillColor(sf::Color::Red);
	}

	obj2 = new GameObject(sf::Vector2f(500, 100), sf::Vector2f(100, 100));
	obj2->AddComponent<BoxCollider>(sf::Vector2f(500, 100), sf::Vector2f(100, 100), obj2);
	obj2->AddComponent<DynamicBody>(0.05f, obj2, false);
	if (obj2->TryGetComponent<BoxCollider>(boxCollider))
	{
		rec2 = new Rectangle(boxCollider->GetSize());
		rec2->SetPosition(obj2->GetPosition());
		rec2->SetFillColor(sf::Color::Green);
	}

	floorObj = new GameObject(sf::Vector2f(0, 500), sf::Vector2f(800, 100));
	floorObj->AddComponent<BoxCollider>(sf::Vector2f(0, 500), sf::Vector2f(800, 100), floorObj);
	floorObj->AddComponent<DynamicBody>(0.05f, floorObj, true);
	if (floorObj->TryGetComponent<BoxCollider>(boxCollider))
	{
		floorRec = new Rectangle(boxCollider->GetSize());
		floorRec->SetPosition(floorObj->GetPosition());
		floorRec->SetFillColor(sf::Color::White);
	}

	return true;
}

bool GameApp::Update()
{
	bool outObj = false;
	sf::Vector2u windowSize = WindowManager::Instance().GetWindowSize();
	std::shared_ptr<DynamicBody> dynamicBody;
	std::shared_ptr<BoxCollider> boxCollider;

	//obj1の処理
	sf::Vector2f velo = sf::Vector2f(1.0f, 0.0f);
	//veloの正規化
	float length = std::sqrt(velo.x * velo.x + velo.y * velo.y);
	velo.x /= length;
	velo.y /= length;
	velo *= 0.1f; //スピードを0.1fにする
	if (obj1->TryGetComponent<DynamicBody>(dynamicBody))
	{
		velo.y = dynamicBody->GetVelocity().y;
		dynamicBody->SetVelocity(velo, ForceMode::SET);
		//obj1->Move(velo, ForceMode::SET);
	}

	//obj1とobj2が画面端まで行ったら反対側へSetPositionで移動するように
	outObj = false;
	if (obj1->TryGetComponent<BoxCollider>(boxCollider))
	{
		if (obj1->GetPosition().x > windowSize.x) outObj = true;
		if (obj1->GetPosition().x + boxCollider->GetSize().x < 0) outObj = true;
		if (obj1->GetPosition().y > windowSize.y - boxCollider->GetSize().y) outObj = true;
	}

	if (outObj)
	{
		obj1->SetPosition(sf::Vector2f(0, 0));
		dynamicBody->SetVelocity(sf::Vector2f(1.0f, 0.0f), ForceMode::SET);
		//obj1->Move(sf::Vector2f(0, 0), ForceMode::SET);
	}

	//obj2の処理
	velo = sf::Vector2f(-1.0f, 0.0f);
	length = std::sqrt(velo.x * velo.x + velo.y * velo.y);
	velo.x /= length;
	velo.y /= length;
	velo *= 0.02f; //スピードを0.02fにする
	if (obj2->TryGetComponent<DynamicBody>(dynamicBody))
	{
		velo.y = dynamicBody->GetVelocity().y;
		dynamicBody->SetVelocity(velo, ForceMode::SET);
		//obj2->Move(velo, ForceMode::SET);
	}
	outObj = false;
	if (obj2->TryGetComponent<BoxCollider>(boxCollider))
	{
		if (obj2->GetPosition().x > windowSize.x) outObj = true;
		if (obj2->GetPosition().x + boxCollider->GetSize().x < 0) outObj = true;
		if (obj2->GetPosition().y > windowSize.y - boxCollider->GetSize().y) outObj = true;
	}

	if (outObj)
	{
		obj2->SetPosition(sf::Vector2f(600, 0));
		dynamicBody->SetVelocity(sf::Vector2f(-1.0f, 0.0f), ForceMode::SET);
		//obj2->Move(sf::Vector2f(0, 0), ForceMode::SET);
	}
	
	rec1->SetPosition(obj1->GetPosition());
	rec2->SetPosition(obj2->GetPosition());
	floorRec->SetPosition(floorObj->GetPosition());

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

	obj1->Render();
	obj2->Render();
	floorObj->Render();

	return true;
}

bool GameApp::RederDebug()
{
	obj1->RenderDebug();
	obj2->RenderDebug();
	floorObj->RenderDebug();

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