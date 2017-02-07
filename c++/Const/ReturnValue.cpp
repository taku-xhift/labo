


#include <iostream>

class Data {
public:
	Data(int data_ = 0) : integer(data_) {}

	int integer;


public:

	Data(const Data& ohter_) {
		std::cout << "Copy" << std::endl;
	}

};

class Test {
public:
	const Data& getData() { return this->data; }
private:
	Data data;
};


Data createData() {
	Test test;
	return test.getData();
}

int main() {
	Data data;

	{
		Test test;

		std::cout << test.getData().integer << std::endl;

		data = test.getData();
	}

	std::cout << data.integer << std::endl;


	data.integer = 3;
	std::cout << data.integer << std::endl;


	std::cout << createData().integer << std::endl;
}

