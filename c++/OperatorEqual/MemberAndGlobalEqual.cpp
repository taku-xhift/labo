


#include <iostream>


struct AAA {
	int integer_;
};


struct BBB {
	BBB& operator=(const AAA& other) throw() {
		this->integer_ = other.integer_;
		return *this;
	}

	friend static AAA& operator=(AAA& lhs, const BBB& rhs) throw() {
		lhs.integer_ = rhs.integer;
		return lhs;
	}

	int integer_;
};


int main() {
	AAA aaa;
	aaa.integer_ = 2;
	BBB bbb;
	bbb.integer_ = 4;

	aaa = bbb;

	std::cout << aaa.integer_ << std::endl;
}

