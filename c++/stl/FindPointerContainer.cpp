

#include <iostream>
#include <algorithm>
#include <list>


class Test {
public:

	Test(int integer_) : integer(integer_) {}

	bool operator== (int integer_) {
		return this->integer == integer_;
	}

//private:
	int integer;
};


struct Finder
{
public:
	Finder(int integer_) : integer(integer_) {}

	template<typename Type> bool operator()(const Type& type_) const {
		return type_->integer == this->integer;
	}

private:
	int integer;
};


int main() {

	std::list<Test*> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(new Test(i));
	}

	std::list<Test*>::iterator ite = std::find_if(container.begin(), container.end(), Finder(3));

	std::cout << (*ite)->integer << std::endl;

	return 0;
}


