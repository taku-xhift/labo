


#include <iostream>
#include <vector>


class Test {
public:
	int integer;

	Test() : integer(0) {}
};



int main() {
	Test test[10];

	std::vector<Test&> container;

	for (int i = 0; i < 10; ++i) {
		//test[i].integer = i;
		//container.push_back(test[i]);
	}

	//for (std::vector<Test&>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		//std::cout << ite->integer << std::endl;
	//}
}


