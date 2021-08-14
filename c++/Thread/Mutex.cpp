//�}���`�X���b�h�v���O������ mutex �̎g����
//#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <process.h>

class Mutex
{
public:

	Mutex() {
		WaitForSingleObject(this_, INFINITE);
	}

	~Mutex() {
		ReleaseMutex(this_);
	}

	static HANDLE this_;
};

HANDLE Mutex::this_ = NULL;


class Singleton {
public:

	static void create() {
		if (this_ == NULL) {
			Mutex mutex;
//			WaitForSingleObject(mutex_, INFINITE);
			if (this_ == NULL) {
				this_ = new Singleton();
			}
//			ReleaseMutex(mutex_);
		}
	}

	static Singleton& getInstance() {
		Mutex mutex;
		//WaitForSingleObject(mutex_, INFINITE);
		//ReleaseMutex(mutex_);
		return *this_;
	}


	int integer_;

private:

	Singleton() : integer_(0) {
		mutex_ = CreateMutex(NULL,FALSE,NULL);      //�~���[�e�b�N�X����
	}


	~Singleton() {
		if (this_ != NULL) {
			delete this_;
			this_ = NULL;
		}
		CloseHandle(mutex_);
	}



	static HANDLE      mutex_;
	static Singleton*  this_;
};

HANDLE      Singleton::mutex_ = NULL;
Singleton*  Singleton::this_ = NULL;




HANDLE	hMutex; //�~���[�e�b�N�X�̃n���h��

int count1 = 0; //mutex �ŕϐ���ی삷��
int count2 = 0; //�ی삵�Ȃ�

void func1(LPVOID	pParam)
{
	for (int i = 0; i < 10000; ++i) {
		//WaitForSingleObject(hMutex,INFINITE); //mutex �Ԃ͑��̃X���b�h����ϐ���ύX�ł��Ȃ�
		Mutex mutex;
		++Singleton::getInstance().integer_;
		//std::cout << "thread1 : " << Singleton::getInstance().integer_ << std::endl;
		//Sleep(50);
		//ReleaseMutex(hMutex);
	}
}

void func2(LPVOID	pParam)
{
	for (int i = 0; i < 10000; ++i) {
		//WaitForSingleObject(hMutex,INFINITE); //mutex �Ԃ͑��̃X���b�h����ϐ���ύX�ł��Ȃ�
		Mutex mutex;
		++Singleton::getInstance().integer_;
		//std::cout << "thread2 : " << Singleton::getInstance().integer_ << std::endl;
		//Sleep(50);
		//ReleaseMutex(hMutex);
	}
}

int main()
{
	HANDLE hThread[2];

	//hMutex = CreateMutex(NULL,FALSE,NULL);	//�~���[�e�b�N�X����
	Mutex::this_ = CreateMutex(NULL,FALSE,NULL);	//�~���[�e�b�N�X����

	Singleton::create();

	hThread[0] = (HANDLE)_beginthread(func1,0,NULL);	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthread(func2,0,NULL);	//�X���b�h�Q�쐬

	//�X���b�h�P�A�Q�I���҂�
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);
	CloseHandle(Mutex::this_);

	std::cout << "result : " << Singleton::getInstance().integer_ << std::endl;

}
