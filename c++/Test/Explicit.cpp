


#include <iostream>


class Test {
public:
	explicit Test(int integer, int defaultData = 4) {
		std::cerr << integer << std::endl;
		std::cerr << defaultData << std::endl;
	}
};


int main() {
	Test test = 1;
}


