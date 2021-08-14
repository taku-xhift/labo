#include <iostream>


class TemplateTest
{
public:
	TemplateTest()
	{
		std::cout << "Constructored a TemplateTest." << std::endl;
	}
};



int main()
{
	TemplateTest templateTest;

	return 0;
}



