


#include <iostream>
#include <boost/foreach.hpp>
#include <vector>


int main() {
	std::vector<int> container;
	container.resize(10);

	BOOST_FOREACH(int& i, container) {
		i = 100;
	}

	BOOST_FOREACH(int i, container) {
		std::cout << i << std::endl;
	}
}


