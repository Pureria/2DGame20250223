#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameApp.h"

int main() {
	//�E�B���h�E���쐬
	sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	GameApp* gameApp = new GameApp(window);
	
	gameApp->Awake();
	gameApp->Start();

	//���C�����[�v
	while (window.isOpen())
	{
		//�R�[�h�̃R�����g�ǉ�
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}

		gameApp->Update();
		gameApp->LateUpdate();

		//�E�B���h�E�̃N���A
		window.clear(sf::Color::Blue);

		gameApp->Render();

		if (gameApp->IsDebugRender())
			gameApp->RederDebug();

		//�`�悵�����e���E�B���h�E�ɔ��f
		window.display();

	}

	
	//�������̉��
	gameApp->Release();
	delete gameApp;

	//�I�������R���\�[���Ƀ��b�Z�[�W��\��
	std::cout << "Game Finish!!" << std::endl;

	return 0;
}