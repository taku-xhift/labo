/*
	pointerTest
	�����ł� boost::shared_ptr �̃|�C���^��
	���g�̃|�C���^�^�Ŏ擾������@������̂���������
*/


#include <boost/shared_ptr.hpp>
#include <iostream>


class Test
{
public:

	Test() : index(8) {};


	int index;
};

void Out(Test *test)
{
	std::cout << test->index << std::endl;
}


void Out(Test &test)
{
	std::cout << test.index + 1 << std::endl;
}





int main()
{
	//Test test;

	//Out(test);

	boost::shared_ptr<Test> test(new Test());

	Out(*test);

	return 0;
}


