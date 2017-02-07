


#include <iostream>

int* integer_ = NULL;

void copy(int* integer) {
	*integer_ = *integer;
}

int main() {
	integer_ = new int(3);
	int* integer = new int(9);
	copy(integer);

	std::cout << *integer_ << std::endl;
}


