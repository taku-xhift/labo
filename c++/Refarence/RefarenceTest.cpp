

#include <iostream>



class Test
{
public:
	float &floating;

	Test(float &tempFloat)
		: floating(tempFloat)
	{
	}
};




int main()
{
	float floating = 4.0f;

	Test test(floating);


	std::cout << test.floating << std::endl;

	floating = 5.0f;

	std::cout << test.floating << std::endl;

	return 0;
}




