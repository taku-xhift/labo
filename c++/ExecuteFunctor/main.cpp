


#include <iostream>
#include <vector>
#include <algorithm>


class Test
{
	//friend Functor_Execute;

public:
	void setState(int state_) {
		this->state = state_;
	}

	int run() {
		if (counter > this->state) {
			std::cout << this->state << std::endl;
			counter = 0;
			return 1;
		}

		++counter;

		return 0;
	}

	int state;
	static int counter;
};
int Test::counter = 0;


struct Functor_Execute
{
	explicit Functor_Execute(Test& test_) : test(test_) {}

	void operator()(int list_) {
		this->test.setState(list_);
		while (test.run() == 0) {
		}
	}

	Test& test;
};


int main()
{
	std::vector<int> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	Test test;

	std::for_each(container.begin(), container.end(), Functor_Execute(test));

	return 0;
}



