


#include <iostream>
#include <cstdlib>
#include <string>

int main() {
	char array[0xff];
	strcpy(array, "test");

	std::string string(array);
	std::cout << string << std::endl;
}


