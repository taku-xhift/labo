


#include <iostream>

class Base {
public:

	virtual void out(int name) = 0;
};


class Child : public Base {
public:

	void out(int ID) {
		std::cout << ID << std::endl;
	}
};

int main() {
	Child child;

	child.out(3);

	return 0;
}

