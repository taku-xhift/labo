



#include <iostream>
#include <string>
#include <bitset>
#include <ctime>


const int roopTimes = 500000;


int main() {
	std::string first = "first";
	std::string second = "second";
	//std::bitset<roopTimes> result;
	std::clock_t firstStart = std::clock();

	bool result = false;

	for (int i = 0; i < roopTimes; ++i) {
		result = (first == second);
	}


	std::clock_t firstEnd = std::clock();
	std::clock_t secondStart = std::clock();

	for (int i = 0; i < roopTimes; ++i) {
		result = !!first.compare(second);
	}

	std::clock_t secondEnd = std::clock();

	std::cout << "first  : " << firstEnd - firstStart << std::endl;
	std::cout << "second : " << secondEnd - secondStart << std::endl;
}



