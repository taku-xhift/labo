#include <boost/shared_ptr.hpp>
#include <iostream>


class SharedTest
{
public:
	int* testInt;
};



int main()
{
	SharedTest sharedTest;
	//sharedTest.testInt = new int[4];
	boost::shared_ptr<int>  arrayInt(new int[4]);
	sharedTest.testInt = &(*arrayInt);


	//delete [] sharedTest.testInt;

	return 0;
}