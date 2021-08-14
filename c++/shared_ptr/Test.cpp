


#include <boost/shared_ptr.hpp>
#include <iostream>


class Test {
public:
	void reset(const int& integer) throw() {
		this->ptr.reset(new int(integer));
	}

	boost::shared_ptr<int> ptr;
};


int main() {
	Test test;
	int integer = 4;
	test.reset(integer);

	std::cerr << *test.ptr << std::endl;
}


