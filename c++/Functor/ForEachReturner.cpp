


#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <typeinfo>


class Executioner {
public:

	template<typename Type>
	void operator()(Type& data_) {
		this->resultList.push_back(data_.method());
	}

	std::vector<int> resultList;
};

class Test {
public:

	Test(int data_) : data(data_) {}

	int method() {
		std::cout << "data = " << this->data << std::endl;
		return 1;
	}

	int data;
};


int main() {
	std::vector<Test> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(Test(i));
	}

	Executioner result = std::for_each(container.begin(), container.end(), Executioner());
	std::cout << typeid(result).name() << std::endl;

	return 0;
}


