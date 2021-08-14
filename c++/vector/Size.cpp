


#include <iostream>
#include <vector>


int main()
{
	std::vector<int> container;

	for (int i = 0; i < 5; ++i) {
		container.push_back(i);
	}

	std::cerr << container.size() << std::endl;

	for (; container.size() != 0;) {
		std::cerr << container.at(container.size()-1) << std::endl;
		container.pop_back();
	}

	return 0;
}


