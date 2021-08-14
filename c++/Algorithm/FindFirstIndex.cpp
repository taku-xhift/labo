


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/lambda/lambda.hpp>



template<typename Type, typename Functor>
unsigned int first_index_of(const Type& value, Functor functor) throw() {
	std::vector<int>::const_iterator ite = std::find_if(value.begin(), value.end(), functor);
	return std::distance<std::vector<int>::const_iterator>(value.begin(), ite);
}


int main() {
	std::vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	std::cout << first_index_of(container, boost::lambda::_1 == 23) << std::endl;
}


