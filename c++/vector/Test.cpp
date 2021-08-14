

#include <iostream>
#include <vector>


struct Test {
	Test(int i)
		: integer_(i)
	{
		
	}
	int integer_;
};

struct Holder {
	Holder(int i)
	{
		
	}

	std::vector<Test> test_;
};


int main() {
	Holder holder(3);
}


