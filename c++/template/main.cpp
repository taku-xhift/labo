


#include <iostream>


template<unsigned int i>
const char* const fileName();


template<>
const char* const fileName<0>() {
	return "0 filename!";
}

template<>
const char* const fileName<1>() {
	return "1 filename!";
}


const char* const fileName_ = fileName<0>();

int main() {
	std::cout << fileName_ << std::endl;
}


