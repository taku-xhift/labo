


#include <iostream>


void print(const char* string) throw() {
	std::cout << string << std::endl;
}


int main() {
	char name[0xff];
	strncpy(name, "name", 0xff);

	print(name);
}

