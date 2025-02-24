#pragma once

template <typename T>
class Singleton {
public:
	static T& Instance();
	virtual bool Release() = 0; //�������

	Singleton(const Singleton&) = delete; // �R�s�[�R���X�g���N�^���֎~
	Singleton& operator=(const Singleton&) = delete; // ������Z�q���֎~

protected:
	Singleton(); //�R���X�g���N�^��ی�
	virtual ~Singleton(); //�f�X�g���N�^��ی�
};

//�e���v���[�g�̎���
template <typename T>
T& Singleton<T>::Instance() {
	static T instance; //static���[�J���ϐ��Ƃ��ăC���X�^���X��ێ�
	return instance;
}

template <typename T>
Singleton<T>::Singleton() {
	//�R���X�g���N�^�̎���
}

template <typename T>
Singleton<T>::~Singleton() {
	//�f�X�g���N�^�̎���
}

/*
template <typename T>
bool Singleton<T>::Release() {
	//��������̎���
}
*/