


#include <iostream>

struct Test {
	int integer_;
};

int* integer_ = NULL;

void print() {
	std::cout << *integer_ << std::endl;
}



void set(int* integer) {
	integer_ = integer;
}

int main() {
	{
		int integer = 20;
		set(&integer);
	}
	print();
}

