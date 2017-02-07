

#include <map>
#include <iostream>


int main()
{
	std::map<int, int> integerMap;
	integerMap.insert(std::map<int, int>::value_type(0, 3));

	for (std::map<int, int>::iterator ite = integerMap.begin();
		ite != integerMap.end();
		ite++)
	{
		std::cout << (*ite).first << std::endl;
		std::cout << (*ite).second << std::endl;
	}

	return 0;
}

