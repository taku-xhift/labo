


#include <string>
#include <iostream>
#include <ctime>

const int roopTimes = 500000;


int main() {
	std::string plusTest = "";
	std::string appendTest = "";

	clock_t  start = std::clock();

	for (int i = 0; i < roopTimes; ++i) {
		plusTest += "+";
	}

	closck_t firstTestEnd = std::clock();

	for (int i = 0; i < roopTimes; ++i) {
		appendTest.append("+");
	}

	clock_t secondTestEnd = std::clock();

	std::cout << "first  : " << firstTestEnd - start << "ms" << std::endl;
	std::cout << "second : " << secondTestEnd - firstTestEnd << "ms" << std::endl;
}



