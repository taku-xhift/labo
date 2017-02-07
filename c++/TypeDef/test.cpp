

#include <iostream>


struct Test;


class A {
public:
	A();
	Test* test_;
};

#include <vector>
struct Test : std::vector<int>{};

A::A() : test_(NULL) { this->test_ = new Test(); }

int main() {
	A a;
	a.test_->push_back(3);
}
