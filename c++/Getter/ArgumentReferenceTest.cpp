

#include <iostream>

class Test {
public:
	int integer;
	const char* uri;

	Test() : integer(40), uri("test") {}
};

bool getData(Test& test_) {
	static Test test;
	test_ = test;
	return true;
}


int main() {
	Test test;
	test.integer = 0;
	test.uri = "";
	getData(test);

	std::cout << test.integer << std::endl;
	std::cout << test.uri << std::endl;

	test.integer = 0;
	test.uri = "";

	getData(test);

	std::cout << test.integer << std::endl;
	std::cout << test.uri << std::endl;

	return 0;
}

