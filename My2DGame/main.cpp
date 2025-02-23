#include <iostream>
#include "GameApp.h"
#include "WindowManager.h"

int main() {
	//�E�B���h�E���쐬
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	WindowManager::Instance().Initialize(sf::VideoMode(800, 600), "My 2D Game");
	GameApp* gameApp = new GameApp();

	gameApp->Awake();
	gameApp->Start();

	//���C�����[�v
	while (WindowManager::Instance().IsOpen())
	{		
		//�E�B���h�E�̃C�x���g���`�F�b�N
		if (!WindowManager::Instance().CheckWindowEvent()) break;

		gameApp->Update();
		gameApp->LateUpdate();
		gameApp->Render();
		if (gameApp->IsDebugRender())
			gameApp->RederDebug();

		//�`�悵�����e���E�B���h�E�ɔ��f
		WindowManager::Instance().WindowUpdate();

	}

	
	//�������̉��
	gameApp->Release();
	WindowManager::Instance().Release();
	delete gameApp;

	//�I�������R���\�[���Ƀ��b�Z�[�W��\��
	std::cout << "Game Finish!!" << std::endl;

	return 0;
}