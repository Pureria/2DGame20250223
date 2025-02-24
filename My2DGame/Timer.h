#pragma once
#include "Singleton.h"
#include <chrono>

class Timer : public Singleton<Timer>
{
private:
	std::chrono::steady_clock::time_point _startTime; //�v���O�����J�n����
	std::chrono::steady_clock::time_point _lastFrameTime; //�O��̃t���[������
	double _deltaTime; //�O���Update����̌o�ߎ���

public:
	Timer();
	void Reset();
	double Elapsed() const; // �o�ߎ��Ԃ��擾
	double DeltaTime() const; // �O���Update����̌o�ߎ��Ԃ��擾
	double GetFPS() const; // FPS���擾
	void Update(); // ���Ԃ̍X�V

	bool Release() override;
};

inline double Timer::DeltaTime() const
{
	return _deltaTime;
}

inline double Timer::GetFPS() const
{
	return 1.0 / _deltaTime;
}

