


#include <iostream>


enum ENUM {
	ENUM_MAX,
};

template<ENUM enum_>
void print() {
	std::cout << enum_ << std::endl;
}

int main() {
	print<static_cast<ENUM>(0)>();
}


