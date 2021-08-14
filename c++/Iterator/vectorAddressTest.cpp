

#include <iostream>
#include <vector>


int main()
{
	std::vector<int> intContainer;

	for (int i = 0; i < 10; ++i) {
		intContainer.push_back(i);
	}

	std::cout << &intContainer.at(0) << std::endl;

	intContainer.erase(intContainer.begin());

	std::cout << &intContainer.at(0) << std::endl;
	std::cout << "Parameter is " << intContainer.at(0) << std::endl;

	return 0;
}


