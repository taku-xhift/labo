

#include <iostream>
#include <string>


int main() {

	std::string str = "‚ ‚¢‚¤";

	std::cout << str.find_last_of("‚ ", std::string::npos);
	std::cout << str.rfind("‚ ", std::string::npos);

	return 0;
}

