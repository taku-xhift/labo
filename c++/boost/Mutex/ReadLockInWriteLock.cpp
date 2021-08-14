

#include <iostream>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>


typedef boost::shared_mutex                     Mutex;
typedef boost::shared_lock<Mutex>               ReadLock;
typedef boost::upgrade_lock<Mutex>              UpLock;
typedef boost::upgrade_to_unique_lock<Mutex>    WriteLock;


Mutex mutex;

void read() {
	const bool tryCheck = mutex.try_lock();

	if (!tryCheck) {
		mutex.unlock_and_lock_upgrade();
		ReadLock read(mutex);

		std::cerr << __FUNCTION__ << std::endl;
	} else {
		std::cerr << __FUNCTION__ << std::endl;
		mutex.unlock();
	}

}


void write() {
	UpLock uplock(mutex);
	WriteLock write(uplock);

	std::cerr << __FUNCTION__ << std::endl;
}


void readAndWrite() {
	UpLock uplock(mutex);
	WriteLock write(uplock);

	read();

	std::cerr << __FUNCTION__ << std::endl;
}



int main() {
	read();
	write();
	readAndWrite();
}


