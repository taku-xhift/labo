


#include <iostream>

struct ABase {
	ABase() : integer_(2) {}
	int integer_;
};

struct BBase {
	BBase() : integer_(33) {}
	int integer_;
};


struct Derived
	: public ABase
	, public BBase
{
	Derived() : integer_(99) {}
	int integer_;
};


int main() {
	ABase* derived = new Derived();

	Derived* derived2 = static_cast<Derived*>(derived);
	BBase* bbase = static_cast<BBase*>(derived2);

	std::cout << bbase->integer_ << std::endl;
}

