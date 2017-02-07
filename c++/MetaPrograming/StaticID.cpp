


#include <iostream>

#define Size (0)

static unsigned int count = 0;

template<unsigned int N>
class Counter {
public:
	static const unsigned int number = N;
};


int main() {
	std::cout << Counter<-1>().number << std::endl;
}


