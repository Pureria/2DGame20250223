#pragma once
#include "GameApp.h"
#include "WindowManager.h"
#include "Timer.h"
#include "PhysicsManager.h"
#include "DebugManager.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ウィンドウを作成
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	WindowManager::Instance().Initialize(sf::VideoMode(800, 600), "My 2D Game");
	PhysicsManager::Instance();
	GameApp* gameApp = new GameApp();
	Timer::Instance();

	gameApp->Awake();
	gameApp->Start();

	//メインループ
	while (WindowManager::Instance().IsOpen())
	{		
		//ウィンドウのイベントをチェック
		if (!WindowManager::Instance().CheckWindowEvent()) break;

		//時間の更新
		Timer::Instance().Update();
		
		//物理演算の更新
		PhysicsManager::Instance().Update();

		//ゲームの更新
		gameApp->Update();
		gameApp->LateUpdate();
		gameApp->Render();
		if (gameApp->IsDebugRender())
			gameApp->RederDebug();

		//描画した内容をウィンドウに反映
		WindowManager::Instance().WindowUpdate();
	}

	
	//メモリの解放
	gameApp->Release();
	WindowManager::Instance().Release();
	PhysicsManager::Instance().Release();
	Timer::Instance().Release();
	if (gameApp != nullptr)
	{
		delete gameApp;
		gameApp = nullptr;
	}

	//終わったらコンソールにメッセージを表示
	//std::cout << "Game Finish!!" << std::endl;
	DebugManager::LogInfo("__cplusplus: " + std::to_string(__cplusplus));
	DebugManager::LogInfo("Game Finish!!");

	return 0;
}