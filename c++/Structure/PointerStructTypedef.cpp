

#include <iostream>

typedef struct {
	int integer;
} Structure, *lpStructure;


int main() {

	lpStructure structure;
	structure->integer = 20;

	std::cout << structure->integer << std::endl;

	return 0;
}
