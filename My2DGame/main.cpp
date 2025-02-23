#include <iostream>
#include "GameApp.h"
#include "WindowManager.h"
#include "Timer.h"

int main() {
	//ウィンドウを作成
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	WindowManager::Instance().Initialize(sf::VideoMode(800, 600), "My 2D Game");
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
	delete gameApp;

	//終わったらコンソールにメッセージを表示
	std::cout << "Game Finish!!" << std::endl;

	return 0;
}