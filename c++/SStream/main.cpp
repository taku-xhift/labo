

#include <iostream>
#include <string>
#include <sstream>

void out(const char* strings) {
	std::cerr << strings << std::endl;
}


int main()
{
	int a, b;
	a = 1;
	b = 23;

	std::ostringstream oss;

	std::string as;
	oss << a;
	as = "a is " + oss.str() + "\n";

	std::string bs;
	oss << b;
	bs = "b is " + oss.str() + "\n";

	out(("The data is strange!!\n" + as + bs).c_str());

	return 0;
}

