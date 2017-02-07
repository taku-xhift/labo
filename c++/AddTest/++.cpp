
#include <iostream>
#include <vector>


int main()
{
	std::vector<int> intContainer;

	for (int i = 0; i < 10; ++i) {
		intContainer.push_back(i);
	}

	std::vector<int>::iterator ite = intContainer.begin();
	std::vector<int>::iterator nextIte = ite+1;

	std::cout << "next is " << *nextIte << std::endl;
	std::cout << "this is " << *ite << std::endl;

	return 0;
}


