

#include <iostream>


class Test {
public:
	const int& integer_;

	Test(const int& integer)
		: integer_(integer)
	{
		
	}
};


int main() {
	int count = 20;
	Test test(count);
	count = 21;
	std::cout << test.integer_ << std::endl;
}

