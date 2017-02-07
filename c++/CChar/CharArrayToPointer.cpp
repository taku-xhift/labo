



#include <iostream>
#include <cstdlib>


void print(const char* string) {
	std::cerr << string << std::endl;
}


int main() {
	char array[0xff];
	std::strncpy(array, "test", 0xff);
	print(array);
}

