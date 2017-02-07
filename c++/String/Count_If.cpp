

#include <iostream>
#include <string>



unsigned int count_if(const std::string& source, char target) {
	unsigned int counter = 0;

	std::string::size_type index = source.find(target);

	while (index != std::string::npos) {
		index = source.find(target, index +1);
		++counter;
	}

	return counter;
}


int main() {
	std::string strings = "sam,m,m,m,m,mmmmple";

	std::cout << count_if(strings, ',') << std::endl;
}

