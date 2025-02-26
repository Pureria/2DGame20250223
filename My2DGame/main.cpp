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

	//�E�B���h�E���쐬
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My 2D Game");
	WindowManager::Instance().Initialize(sf::VideoMode(800, 600), "My 2D Game");
	PhysicsManager::Instance();
	GameApp* gameApp = new GameApp();
	Timer::Instance();

	gameApp->Awake();
	gameApp->Start();

	//���C�����[�v
	while (WindowManager::Instance().IsOpen())
	{		
		//�E�B���h�E�̃C�x���g���`�F�b�N
		if (!WindowManager::Instance().CheckWindowEvent()) break;

		//���Ԃ̍X�V
		Timer::Instance().Update();
		
		//�������Z�̍X�V
		PhysicsManager::Instance().Update();

		//�Q�[���̍X�V
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
	PhysicsManager::Instance().Release();
	Timer::Instance().Release();
	if (gameApp != nullptr)
	{
		delete gameApp;
		gameApp = nullptr;
	}

	//�I�������R���\�[���Ƀ��b�Z�[�W��\��
	//std::cout << "Game Finish!!" << std::endl;
	DebugManager::LogInfo("__cplusplus: " + std::to_string(__cplusplus));
	DebugManager::LogInfo("Game Finish!!");

	return 0;
}