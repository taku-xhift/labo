


#include <iostream>


void resetPointer(int** intP_)
{
	int* intPointer = new int;

	std::cout << __FUNCTION__ << std::endl;
	std::cout << "intPointer = " << (unsigned int)(*intPointer) << std::endl;
	std::cout << "intP_ = " << (unsigned int)(intP_) << std::endl;

	delete *intP_;

	*intP_ = intPointer;

	std::cout << "new intPointer = " << (unsigned int)(*intPointer) << std::endl;
}


void resetPointer(int*** intR_)
{
	//int* intPointer = new int;

	//&intR_ = intPointer;
}




int main()
{
	int* integerP = new int;

	std::cout << (unsigned int)(integerP) << std::endl;

	resetPointer(&(&integerP));

	std::cout << (unsigned int)(integerP) << std::endl;

	delete integerP;

	return 0;
}



