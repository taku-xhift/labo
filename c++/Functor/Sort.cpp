

#include <iostream>
#include <vector>
//#include <functional>
#include <algorithm>
#include <time.h>



class Test {
public:
	Test(int win) : win_(win) {}
	int win() const throw() { return this->win_; }
	int win_;
};


struct SortGreater {
	bool operator()(const Test& lhs, const Test& rhs) {
		return lhs.win() > rhs.win();
	}
};



int main() {
	srand((unsigned int)time(NULL));

	std::vector<Test> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(Test(rand()));
	}

	std::sort(container.begin(), container.end(), SortGreater());

	for (std::vector<Test>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		std::cout << ite->win() << std::endl;
	}
}


