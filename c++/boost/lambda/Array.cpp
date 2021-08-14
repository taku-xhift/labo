


#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


//const int array[] = {
//	1, 3, 5, 7,
//};


int main() {
	std::vector<int> array;
	for (int i = 0; i < 10; ++i) { array.push_back(i); }

	int count =
		std::count(array.begin(), array.end(), 3);

	std::cout << count << std::endl;
}


