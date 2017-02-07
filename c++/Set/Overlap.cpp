

#include <set>
#include <iostream>


int main() {
	std::set<int> set;
	set.insert(1200);
	set.insert(1200);

	for (std::set<int>::const_iterator ite = set.begin(); ite != set.end(); ++ite) {
		std::cout << *ite << std::endl;
	}
}

