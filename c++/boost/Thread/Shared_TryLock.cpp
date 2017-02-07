


#include <iostream>
#include <boost/thread.hpp>
#include <Windows.h>


typedef boost::shared_mutex                     Mutex;
typedef boost::shared_lock<Mutex>               ReadLock;
typedef boost::upgrade_lock<Mutex>              UpLock;
typedef boost::upgrade_to_unique_lock<Mutex>    WriteLock;



class ThreadObj
{
public:

	ThreadObj() throw()
		: counter_(0)
	{}

	void MainCall() throw() {
//		UpLock upLock(this->mutex_);
//		WriteLock writeLock(upLock);
		ReadLock(this->mutex_);
		this->SubCall();
		std::cerr << __FUNCTION__ << "\n";
	}

	bool isEnd() const throw() {
		
		ReadLock lock(this->mutex_, boost::try_to_lock_t());

		if (!lock || this->counter_ < 5) {
			return false;
		} else {
			return true;
		}
	}


	void SubCall() throw() {
//		UpLock upLock(this->mutex_);
//		WriteLock writeLock(upLock);
		ReadLock(this->mutex_);
		std::cerr << __FUNCTION__ << "\n";
	}

	void operator()() throw() {
		UpLock uplock(this->mutex_);

		while (this->counter_ < 5) {
			Sleep(1000);
			this->isEnd();
			this->MainCall();

			WriteLock writeLock(uplock);
			++this->counter_;
			std::cerr << this->counter_ << "\n";
		}
	}

private:

	mutable Mutex   mutex_;
	int             counter_;
};


int main() {
	ThreadObj obj;
	boost::thread th(boost::ref(obj));
	//obj.MainCall();

	while (!obj.isEnd()) {
		std::cerr << "Still not end...\n";
		Sleep(500);
	}

	std::cerr << "End!!!\n";
}


