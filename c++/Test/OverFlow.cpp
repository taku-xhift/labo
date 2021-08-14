


#include <iostream>
#include <limits>


int main() {
	unsigned int ui = std::numeric_limits<unsigned int>::max();
	++ui;

	std::cout << ui << std::endl;
}


