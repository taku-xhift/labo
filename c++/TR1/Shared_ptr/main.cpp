


#include <iostream>
#include <memory>


struct Test {
	int integer_;
};


int main()
{
	std::tr1::shared_ptr<Test> spTest(new Test());
	Test test;
	test.integer_ = 30;
	*spTest = test;

	std::cout << (*spTest).integer_ << std::endl;
}


