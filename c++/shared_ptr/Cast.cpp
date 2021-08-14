


#include <memory>
#include <iostream>


class Base {
	
};

class Deri : public Base {
public:

	void print() {
		std::cerr << __FUNCTION__ << std::endl;
	}
};

int main() {
	std::tr1::shared_ptr<Base> ptr(new Deri());
	std::tr1::static_pointer_cast<Deri>(ptr)->print();
}


