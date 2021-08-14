


#include <iostream>


struct BaseA {
	int integer_;
	float floating_;

	BaseA() : integer_(3), floating_(5.0f) {}
};


struct BaseB {
	int integer_;
	float floating_;

	BaseB() : integer_(0), floating_(.0f) {}
};



struct Derived
	: public BaseA
{
	
};


void print(const BaseB& base) {
	std::cout << base.integer_ << std::endl;
	std::cout << base.floating_ << std::endl;
}


int main() {
	Derived obj;

	print(*reinterpret_cast<BaseB*>(&obj));
}


