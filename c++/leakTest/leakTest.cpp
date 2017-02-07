#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <boost/shared_ptr.hpp>

class LeakTest
{
public:

	int      testMenber;
	int*     pTestMenber;
	boost::shared_ptr<int> SpTestMenber;
};


void Out(int *out)
{
	*out += 1;
	std::cout << *out << std::endl;
}


int main()
{
	

	LeakTest leakTest;

	{
		//leakTest.testMenber = leak.get();
		boost::shared_ptr<int> leak(new int());
		*leak = 3;
		leakTest.testMenber = *leak;
		
		leakTest.pTestMenber = leak.get();
		//std::cout << *leakTest.pTestMenber << std::endl;

		leakTest.SpTestMenber = leak;
	}


	std::cout << leakTest.testMenber << std::endl;
	Out(&leakTest.testMenber);
	//Out(leakTest.pTestMenber);
	
	std::cout << *leakTest.SpTestMenber << std::endl;
	Out(leakTest.SpTestMenber.get());
	std::cout << *leakTest.SpTestMenber << std::endl;
		

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	return 0;
}

