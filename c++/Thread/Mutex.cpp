//マルチスレッドプログラムと mutex の使い方
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
		mutex_ = CreateMutex(NULL,FALSE,NULL);      //ミューテックス生成
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




HANDLE	hMutex; //ミューテックスのハンドル

int count1 = 0; //mutex で変数を保護する
int count2 = 0; //保護しない

void func1(LPVOID	pParam)
{
	for (int i = 0; i < 10000; ++i) {
		//WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
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
		//WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
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

	//hMutex = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成
	Mutex::this_ = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成

	Singleton::create();

	hThread[0] = (HANDLE)_beginthread(func1,0,NULL);	//スレッド１作成
	hThread[1] = (HANDLE)_beginthread(func2,0,NULL);	//スレッド２作成

	//スレッド１、２終了待ち
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//ハンドルクローズ
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);
	CloseHandle(Mutex::this_);

	std::cout << "result : " << Singleton::getInstance().integer_ << std::endl;

}
