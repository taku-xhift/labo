


#include <iostream>
#include <map>
#include <string>


template<typename T>
class Test
{
public:

	std::pair<std::string, T *> testPair;


	void setPair(std::string name, T &parameter)
	{
		std::pair<std::string, T *> pair = std::make_pair(name, parameter);
		this->testPair.insert(pair);
	}

};


int main()
{
	Test test;


	return 0;
}

