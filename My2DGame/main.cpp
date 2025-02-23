#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameApp.h"

int main() {
	//ウィンドウを作成
	sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	GameApp* gameApp = new GameApp(window);
	bool end = false;

	gameApp->Awake();
	gameApp->Start();

	//メインループ
	while (window.isOpen())
	{		
		sf::Event event; //イベントを管理するクラス
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				end = true;
			}
		}
		if (end) break;

		gameApp->Update();
		gameApp->LateUpdate();

		//ウィンドウのクリア
		window.clear(sf::Color::Blue);

		gameApp->Render();

		if (gameApp->IsDebugRender())
			gameApp->RederDebug();

		//描画した内容をウィンドウに反映
		window.display();

	}

	
	//メモリの解放
	gameApp->Release();
	delete gameApp;

	//終わったらコンソールにメッセージを表示
	std::cout << "Game Finish!!" << std::endl;

	return 0;
}