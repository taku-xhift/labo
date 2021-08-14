


#include <iostream>


namespace {
	void func() { std::cout << "no name" << std::endl; }
}

void func() { std::cout << "global" << std::endl; }


int main() {
	func();
	::func();
}


