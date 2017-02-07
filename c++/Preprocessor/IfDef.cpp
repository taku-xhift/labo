


#include <iostream>


#define TEST 0

class Test {
public:

#if (TEST)
	int integer;
#endif
};


int main() {
	Test test;
	std::cerr << test.integer << std::endl;
}


