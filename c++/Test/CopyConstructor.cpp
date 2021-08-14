


#include <iostream>


struct Test {
	Test() throw()
		: integer_(33)
	{}

	Test(const Test& test) throw() {
		std::cout << "Call CopyConstructor.\n";
	}

	int integer_;
};


const Test& getTest() throw() {
	static Test* test;
	if (test == NULL) {
		test = new Test();
	}

	return *test;
}

void print(const Test& test) throw() {
	std::cout << test.integer_ << std::endl;
}

int main() {
	const Test& test = getTest();
	print(test);
}


