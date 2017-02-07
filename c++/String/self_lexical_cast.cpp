

#include <iostream>
#include <string>
#include <sstream>


template<typename Type, typename Data>
Type easily_lexical_cast(Data string_) {
	std::istringstream stream(string_);
	Type data;
	stream >> data;

	return data;
}

int main() {

	int data = easily_lexical_cast<int>("10");

	std::cout << data << std::endl;

	return 0;
}


