


#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


const int array[4] = { 0, 1, 2, 3 };

const std::vector<int> container(&array[0], &array[4]);

int main() {
	std::for_each(container.begin(), container.end(), std::cout << boost::lambda::_1);
}


