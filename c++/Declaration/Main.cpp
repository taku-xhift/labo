


#include <iostream>
#include "TypeList.hpp"

int main() {
	std::cerr << typeid(TypeList).name() << std::endl;
	std::cerr << sizeof(TypeListHolder) << std::endl;
}


