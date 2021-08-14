#include <iostream>
#include <string>


int main()
{
	std::string const name1 = "player";
	std::string name2 = "enemy";
	const char* name3 = "Actor";
	const char* name4 = "charctor";

	const int i = 0;
	int ii = 4;

	//i += ii;

	//name3 = name3 + name4;
	name1 = name1 + name2;

	//name0 = name0 + name1;
	std::cout << name3 + name1 << std::endl;
	std::cout << name1 + name2 << std::endl;

	return 0;
}