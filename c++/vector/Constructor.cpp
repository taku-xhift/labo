

#include <iostream>
#include <vector>


void out(const std::vector<int>& container) {
	for (std::vector<int>::const_iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}

int container[] = {1,3,5};
std::vector<int> container_(&container[0], &container[sizeof(container)/sizeof(int)]);

int main() {
	int array[5] = {0, 1, 2, 3, 4};
	for (int i = 0; i < 5; ++i) {
		array[i] = i;
	}

	out(std::vector<int> (&array[0], &array[5]));
	out(container_);

	return 0;
}

