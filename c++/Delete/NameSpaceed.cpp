


#include <iostream>
#define Delete(ptr) ::Memory::operator delete(ptr)

namespace Memory
{
	void operator delete(void* data) {
		std::cout << "Namespaced delete" << std::endl;

		free(data);
	}
}

void operator delete(void* data) {
	std::cout << "Globaled deleter" << std::endl;
	free(data);
}


int main()
{
	int* integer = new int;

	Delete (integer);

	return 0;
}


