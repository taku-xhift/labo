

#include <iostream>
#include <vector>


int main()
{
	std::vector<float> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	std::cerr << "container.size() => " << container.size() << "\n";

	container.resize(5);

	std::cerr << "container.size() => " << container.size() << "\n";

	return 0;
}

