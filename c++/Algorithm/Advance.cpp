


#include <iostream>
#include <algorithm>
#include <vector>


template<typename Type>
typename Type::const_iterator advance(const Type& value, unsigned int step) throw() {
	//typename Type::const_iterator ite = value.begin();
	//std::advance(ite, step);
	//return ite;

	return value.begin();
}

int main() {
	std::vector<int> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	container.erase(::advance(container, 4));
	//std::vector<int>::const_iterator ite = ::advance(container, 4);

	for (int i = 0; i < container.size(); ++i) {
		std::cout << container.at(i) << std::endl;
	}
}


