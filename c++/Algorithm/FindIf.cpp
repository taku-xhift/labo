


#include <iostream>
#include <algorithm>
#include <boost/lambda/lambda.hpp>

#define SizeOf(array) (sizeof(array)/sizeof(array[0]))


int main()
{
	int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

	int label = 4;
	const int* isCL = std::find_if(array, array + SizeOf(array), boost::lambda::_1 == label);

	if (isCL != &array[10]) {
		std::cout << *isCL << std::endl;
		std::cout << SizeOf(array) << std::endl;
	} else {
		std::cout << "UnFound" << std::endl;
	}
}


