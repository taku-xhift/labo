


#include <iostream>
#include <string>
#include <list>
#include <algorithm>


struct startWith
{
	char target;
	startWith(char c)
		: target(c)
	{
	}

	bool operator() (const std::string &x) const
	{
		return x.size() != 0 && x[0] == target;
	}
};



int main()
{
	std::list<std::string> sl;
	sl.push_back("Line");
	sl.push_back("anpasand");

	std::list<std::string>::iterator it2 = 
		std::find_if(sl.begin(), sl.end(), startWith('A'));

	if (it2 != sl.end()) {
		std::cout << "Find A!" << std::endl;
	}

	sl.push_back("Algorithm");


	return 0;
}



