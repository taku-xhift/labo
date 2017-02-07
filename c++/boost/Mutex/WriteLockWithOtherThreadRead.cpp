


#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <Windows.h>

typedef boost::shared_mutex                     Mutex;
typedef boost::shared_lock<Mutex>               ReadLock;
typedef boost::upgrade_lock<Mutex>              UpLock;
typedef boost::upgrade_to_unique_lock<Mutex>    WriteLock;


Mutex mutex_;

int resource = 0;


void read() {
	ReadLock read(mutex_);
	std::cerr << "Read...\n";
	//UpLock uplock(mutex_);
	Sleep(2000);
	std::cerr << "resource => " << resource << "\n";
	std::cerr << "End!\n";
}

void write() {
	UpLock uplock(mutex_);
	WriteLock write(uplock);

	resource = 100;

	std::cerr << "resource => " << resource << "\n";
	std::cerr << "writen !\n";
}

int main() {
	boost::thread threadRead(boost::ref(*read));
	boost::thread threadWrite(boost::ref(*write));

	threadRead.join();
	threadWrite.join();
}


