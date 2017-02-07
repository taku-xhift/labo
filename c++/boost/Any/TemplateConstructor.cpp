


#include <iostream>
#include <boost/any.hpp>

class Test {
public:
	template<typename Type>
	Test(Type type_) : any_(type_) {}

	boost::any any_;
};

int main() {
	Test test = Test(3);

	std::cout << boost::any_cast<int>(test.any_) << std::endl;
}


