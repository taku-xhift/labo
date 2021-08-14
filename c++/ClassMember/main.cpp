


#include <iostream>


class Test {
private:
	static int count;
public:
	static int getCount() { return count; }
	Test() {
		++count;
	}
};
int Test::count = 0;

int main() {
	Test::count = 34;

	//std::cout << Test::count << std::endl;
	std::cout << Test::getCount() << std::endl;
}


