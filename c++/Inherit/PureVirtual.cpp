


#include <iostream>
#include <vector>

class Base {
public:
	virtual void print() = 0;
	virtual void nonImpliment() = 0;
};

class Delived
	: public Base
{
public:
	void print() {
		std::cout << __FUNCTION__ << std::endl;
	}
};


int main() {
	using namespace std;

	vector<Base*> container;
	container.push_back(new Delived());
	container.at(0)->print();
}


