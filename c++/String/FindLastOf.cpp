

#include <iostream>
#include <string>


int main() {

	std::string str = "あいう";

	std::cout << str.find_last_of("あ", std::string::npos);
	std::cout << str.rfind("あ", std::string::npos);

	return 0;
}

