


#include <iostream>

struct Data {
	int integer_;
};

class Test {
public:
	Data* const getter() const throw() {
		return this->data_;
	}

private:
	Data* data_;
};

void setter(Data** data) {
	*data = new Data();
}

int main() {
	Test test;
	test.getter()->integer_ = 2;

	std::cout << test.getter()->integer_ << std::endl;
}


