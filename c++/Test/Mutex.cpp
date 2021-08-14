//マルチスレッドプログラムと mutex の使い方
#include <iostream>
#include <windows.h>
#include <process.h>

#pragma warning(disable: 4290)

template<typename Mutex>
class ScopedLocker {
public:

	ScopedLocker(const Mutex& mutex) throw()
		: mutex_(mutex)
	{
		this->mutex_.lock();
	}

	~ScopedLocker() throw() {
		this->mutex_.unlock();
	}

	const Mutex& mutex_;
};


class WindowsMutex {
public:
	WindowsMutex() throw() : mutex_(NULL) {
		this->mutex_ = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成
	}

	~WindowsMutex() throw() {
		CloseHandle(this->mutex_);
	}

	void lock() const throw() {
		WaitForSingleObject(this->mutex_, INFINITE);   // mutex 間は他のスレッドから変数を変更できない
	}

	void unlock() const throw() {
		ReleaseMutex(this->mutex_);
	}

	const HANDLE get() const throw() { return this->mutex_; }

private:

	volatile HANDLE mutex_;
};


class Singleton {
public:

	static void create() {
		if (this_ == NULL) {
			ScopedLocker<WindowsMutex> lock(this_->mutex_);
			if (this_ == NULL) {
				this_ = new Singleton();
			}
		}
	}

	static const Singleton& getInstance() throw(int) {
		if (this_ == NULL) { throw int(); }
		return *this_;
	}

	static void countUp() throw() {
		ScopedLocker<WindowsMutex> lock(this_->mutex_);
		++this_->integer_;
	}


	Singleton() throw() : integer_(0) {}

	volatile int integer_;
	static WindowsMutex mutex_;
	static Singleton* this_;
};

WindowsMutex Singleton::mutex_;
Singleton* Singleton::this_ = NULL;



HANDLE	hMutex; //ミューテックスのハンドル
int main(void);

int count1 = 0; //mutex で変数を保護する
int count2 = 0; //保護しない

unsigned int __stdcall func1(void* pParam)
{
	for (int i = 0; i < 10000; ++i) {
		Singleton::countUp();
	}
	return 0;
}

unsigned int __stdcall func2(void*	pParam)
{
	for (int i = 0; i < 10000; ++i) {
		Singleton::countUp();
	}
	return 0;
}

int main(void){
	HANDLE	hThread[2];
	unsigned int thID[2];
	Singleton::create();

	//hMutex = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, &(thID[0]));	//スレッド１作成
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, &(thID[1]));	//スレッド２作成

	//スレッド１、２終了待ち
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//ハンドルクローズ
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);

	std::cout << Singleton::getInstance().integer_ << std::endl;

	return 0;
}
