


#include <iostream>
#include <list>
#include <memory>

class Test {
public:
	Test(int integer_) : integer(integer_) {}
	int integer;
};

int main() {
	std::list<int*> intList;

	for (int i = 0; i < 10; ++i) {
		intList.push_back(new int(i));
	}

	std::list<std::tr1::shared_ptr<int> > spIntList;

	for (std::list<int*>::iterator ite = intList.begin(); ite != intList.end(); ++ite) {
		spIntList.push_back(std::tr1::shared_ptr<int> (*ite));
	}

	for (std::list<std::tr1::shared_ptr<int> >::iterator ite = spIntList.begin(); ite != spIntList.end(); ++ite) {
		std::cout << *(ite->get()) << std::endl;
	}

	return 0;
}


