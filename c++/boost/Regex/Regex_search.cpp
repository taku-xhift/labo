


#include <iostream>
#include <string>
#include <boost/regex.hpp>


int main()
{
	// new の数と delete の数は同じか？
	boost::regex reg("(new)|(delete)");
	boost::smatch m;
	std::string s = "Calls to new must be followed by delete. Calling simply new results in a leak!";

	int new_counter = 0;
	int delete_counter = 0;
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();

	while (boost::regex_search(it, end, m, reg)) {
		// new か delete か？
		m[1].matched? ++new_counter : ++delete_counter;
		it = m[0].second;
	}

	if (new_counter != delete_counter) {
		std::cout << "メモリリークが検出されました" << std::endl;
	} else {
		std::cout << "一見、問題はなさそうです..." << std::endl;
	}

	return 0;
};


