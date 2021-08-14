


#include <iostream>
#include <vector>
#include <algorithm>

int main() {

	std::vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	// 3–¢–‚Ì—v‘f‚ğ remove
	std::vector<int>::iterator end = 
		//std::remove_if(container.begin(), container.end(), std::bind2nd(std::less<int>(), 3));
		std::remove(container.begin(), container.end(), 3);

	std::cout << "removed" << std::endl;

	for (std::vector<int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}

	container.erase(end, container.end());

	std::cout << "erased" << std::endl;

	for (std::vector<int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << *ite << std::endl;
	}


}

