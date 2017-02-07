


#include <iostream>
#include <list>

int main() {
	std::list<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	std::list<int> subContainer;

	container.merge(subContainer);

}


