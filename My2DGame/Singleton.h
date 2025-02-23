#pragma once

template <typename T>
class Singleton {
public:
	static T& Instance();

	Singleton(const Singleton&) = delete; // コピーコンストラクタを禁止
	Singleton& operator=(const Singleton&) = delete; // 代入演算子を禁止

protected:
	Singleton(); //コンストラクタを保護
	virtual ~Singleton(); //デストラクタを保護
};

//テンプレートの実装
template <typename T>
T& Singleton<T>::Instance() {
	static T instance; //staticローカル変数としてインスタンスを保持
	return instance;
}

template <typename T>
Singleton<T>::Singleton() {
	//コンストラクタの実装
}

template <typename T>
Singleton<T>::~Singleton() {
	//デストラクタの実装
}