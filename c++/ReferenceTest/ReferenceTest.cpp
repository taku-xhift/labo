

#include <iostream>



class Test
{
public:
	float* floating_;

	Test() throw()
		: floating_(NULL)
	{
		this->floating_ = new float(3);
	}

	float& floating() throw() {
		return *(this->floating_);
	}
};

void out(float* address) {
	std::cout << address << std::endl;
}


int main()
{
	Test test;

	std::cout << "pointer address = " << test.floating_ << std::endl;
	float temp = test.floating();
	out(&temp);
	temp = 4.0f;
	std::cout << "floating = " << test.floating() << std::endl;
}




