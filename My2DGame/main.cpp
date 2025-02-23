#include <iostream>
#include "GameApp.h"
#include "WindowManager.h"

int main() {
	//ウィンドウを作成
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	WindowManager::Instance().Initialize(sf::VideoMode(800, 600), "My 2D Game");
	GameApp* gameApp = new GameApp();

	gameApp->Awake();
	gameApp->Start();

	//メインループ
	while (WindowManager::Instance().IsOpen())
	{		
		//ウィンドウのイベントをチェック
		if (!WindowManager::Instance().CheckWindowEvent()) break;

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