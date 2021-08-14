//�}���`�X���b�h�v���O������ mutex �̎g����
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
		this->mutex_ = CreateMutex(NULL,FALSE,NULL);	//�~���[�e�b�N�X����
	}

	~WindowsMutex() throw() {
		CloseHandle(this->mutex_);
	}

	void lock() const throw() {
		WaitForSingleObject(this->mutex_, INFINITE);   // mutex �Ԃ͑��̃X���b�h����ϐ���ύX�ł��Ȃ�
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



HANDLE	hMutex; //�~���[�e�b�N�X�̃n���h��
int main(void);

int count1 = 0; //mutex �ŕϐ���ی삷��
int count2 = 0; //�ی삵�Ȃ�

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

	//hMutex = CreateMutex(NULL,FALSE,NULL);	//�~���[�e�b�N�X����

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, &(thID[0]));	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, &(thID[1]));	//�X���b�h�Q�쐬

	//�X���b�h�P�A�Q�I���҂�
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);

	std::cout << Singleton::getInstance().integer_ << std::endl;

	return 0;
}
