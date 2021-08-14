

#include <iostream>
#include <memory>


int main() {
	std::tr1::shared_ptr<int> integer(new int(3));
	std::tr1::shared_ptr<int> integer2(integer);
	integer.reset();
	integer.reset();

	if (integer != NULL) {
		std::cout << *integer << std::endl;
	}
}


