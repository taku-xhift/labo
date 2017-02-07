

#include <iostream>
#include <string>
#include <map>



class Test
{
public:


	template<typename T> Test(std::string key_, T t)
	{
		this->key = key_;
		this->integer = t;
	}

	std::string key;

	union
	{
		std::string *string;
		float floating;
		int integer;
	};
};



int main()
{
	std::string key = "key";
	int integer = 3;
	Test *test = new Test(key, integer);

	std::cout << test->key << std::endl;
	std::cout << test->integer << std::endl;

	delete test;

	return 0;
}


