


#include <iostream>
#include <boost/any.hpp>

void print(boost::any any) {
	std::cout << boost::any_cast<int>(any) << std::endl;
}

int main() {
	print(2);
}


