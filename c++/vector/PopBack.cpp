

#include <iostream>
#include <vector>


int main()
{
	std::vector<int> container;

	for (int i = 0; i < 3; ++i) {
		container.push_back(i);
	}

	std::cout << container.front() << std::endl;
	container.pop_back();
	std::cout << container.front() << std::endl;
	container.pop_back();
	std::cout << container.front() << std::endl;
	container.pop_back();

	return 0;
}


