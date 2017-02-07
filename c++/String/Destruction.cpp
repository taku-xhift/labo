

#include <iostream>
#include <string>


std::string getString() {
	return std::string("get") + "String";
}

void print(const char* log) {
	std::cout << log << std::endl;
}

int main() {
	{
		std::string string = "string";
		string = string + "Get";
		print((string + "test").c_str());
	}
}


