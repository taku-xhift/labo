


#include <iostream>
#include <vector>


class Test;

class Test
{
public:
	static std::vector<const Test*> allData;

	Test() : data(3)
	{
		allData.push_back(this);
	}

	int data;
};



int main()
{
	Test test;

	std::cout << Test::allData.at(0)->data << std::endl;

	return 0;
}


