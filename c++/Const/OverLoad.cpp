


#include <iostream>



struct Test {
	void function() const throw() {
		std::cout << "const";
		this->functionImpl();
	}

	void function() throw() {
		this->functionImpl();
	}

private:
	void functionImpl() const throw() {
		std::cout << "function" << std::endl;
	}
};


int main() {
	Test test;

	const Test& cTemp = test;
	cTemp.function();

	Test& temp = test;
	temp.function();
}


