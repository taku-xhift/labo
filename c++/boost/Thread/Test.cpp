// 長くてゴメンナサイ…
#include <iostream>
#include <string>
#include <boost/ref.hpp>
#include <boost/thread.hpp>

#include <windows.h>

using namespace std;

void init() {
	Sleep(5000);
}

class Initializer
{
	typedef boost::shared_mutex     Mutex;
	typedef boost::shared_lock<Mutex>              ReadLock;
	typedef boost::upgrade_lock<Mutex>             UpLock;
	typedef boost::upgrade_to_unique_lock<Mutex>   WriteLock;
	//typedef boost::mutex::scoped_lock Lock;

public:
	Initializer() : isEnd_(false) {}

	// スレッドのメインルーチン
	void operator()()
	{

		{
			UpLock upLock(this->mutex_);
			WriteLock writeLock(upLock);
			init();
		}

		this->isEnd(true);
	}


	bool isEnd() const throw() {
		ReadLock lock(this->mutex_);
		return this->isEnd_;
		//exitRequest.notify_one();
	}


	bool try_lock() const throw() {
		const bool isLockable = UpLock(this->mutex_, boost::try_to_lock_t());
		return isLockable;
	}


private:

	void isEnd(bool value) throw() {
		UpLock upLock(this->mutex_);
		WriteLock writeLock(upLock);
		this->isEnd_ = value;
	}

private:

	volatile bool                     isEnd_;
	mutable Mutex                     mutex_;
	boost::condition_variable_any     exitRequest;

};



class Executer
{
public:

	Executer() throw() {
		boost::thread thr(boost::ref(this->init_));
	}

	void execute() throw() {
		bool tryLock = false;
		bool isEnd = false;
		while ((tryLock = !this->init_.try_lock()) || (isEnd = !this->init_.isEnd())) {
			std::cerr << "tryLock = " << !tryLock << "\n";
			std::cerr << "isEnd = " << !isEnd << "\n";
			std::cerr << "Still not end..." << std::endl;
			Sleep(1000);
		}
		std::cerr << "tryLock = " << !tryLock << "\n";
		std::cerr << "isEnd = " << !isEnd << "\n";
	}

private:

	Initializer init_;

};



int main()
{
	Executer exe;
	exe.execute();
}

