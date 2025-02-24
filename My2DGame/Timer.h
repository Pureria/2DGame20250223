#pragma once
#include "Singleton.h"
#include <chrono>

class Timer : public Singleton<Timer>
{
private:
	std::chrono::steady_clock::time_point _startTime; //プログラム開始時間
	std::chrono::steady_clock::time_point _lastFrameTime; //前回のフレーム時間
	double _deltaTime; //前回のUpdateからの経過時間

public:
	Timer();
	void Reset();
	double Elapsed() const; // 経過時間を取得
	double DeltaTime() const; // 前回のUpdateからの経過時間を取得
	double GetFPS() const; // FPSを取得
	void Update(); // 時間の更新

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

