

#include <iostream>

void archiveCheck() throw(std::exception);

int main()
{
	try {
		archiveCheck();
	} catch (std::exception& e) {
		std::cout << "catch!!" << std::endl;
	}

	return 0;
}

