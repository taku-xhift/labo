


#include <iostream>
#include <cstdlib>


class ArrayTest {

};


void out(const char* strings) {
	std::cerr << strings << std::endl;
}

int main() {
	char strings[0x100] = {};
	memset(strings, 0, sizeof(strings));

	out(strings);
	Print();

	ArrayTest test;
}

