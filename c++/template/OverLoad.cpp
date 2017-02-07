


#include <iostream>



class Test {
public:
	template<int i, int j>
	void print() {
		std::cout << i << std::endl;
		std::cout << j << std::endl;
	}

	template<int i>
	void print() {
		std::cout << i << std::endl;
	}
};


int main() {
	Test test;
	test.print<1, 23>();
	test.print<55>();
}


