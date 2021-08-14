// 日本語

#include <iostream>


class Test {
public:
	int GetInteger() const {
		return this->integer_;
	}
	int integer_;
}; 


class Base {
public:
	float floating_;
	void SetFloating(float value) {
		this->floating_ = value;
	}
};

class Derived
	: public Base
{
public:
	double doubleF_;
	void SetFloating(float value) {
		this->doubleF_ = value;
	}
};

void func() {
	int integer_ = 0;
} 


int main() {
	try {
		// 日本語入力テスト
		std::cout << "Hello" << std::endl;
		Test test;

		test.integer_ = 4;
    test.integer_ = 4;全然ダメじゃん
		std::cout << test.integer_ << std::endl;

		Derived d;
		Base b;
	} catch (...) {
		std::cerr << "catch some error" << std::endl;
	}
	std::cout << "Hello world!" << std::endl;
}

