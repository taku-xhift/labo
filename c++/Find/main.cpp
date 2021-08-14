

#include <iostream>
#include <vector>
#include <algorithm>


class Test
{
public:

	Test(int integer_) : integer(integer_) {
		
	}

	bool operator==(unsigned int enum_) { return (this->integer == enum_)? true: false; }
	bool operator==(const Test& test_) { return (this->integer == test_.integer)? true: false; }

//private:
	int integer;
};

int main() {
	std::vector<Test> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(Test(i));
	}

	std::vector<Test>::iterator ite = std::find(container.begin(), container.end(), 3);

	std::cout << ite->integer << std::endl;


	return 0;
}


