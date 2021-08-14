

#include <cstdio>
#include <iostream>
#include <string>

int main() {
	const int num = 16;

	for (int i = 0; i < num; ++i) {
		bool devByTwo = (i%3 == 0);
		bool devByFive = (i%5 == 0);

		if (i == 0) {
			devByTwo = false;
			devByFive = false;
		}

		std::string str = "";
		if (devByTwo) {
			str += "Fizz";
		}
		if (devByFive) {
			str += "Buzz";
		}

		if (!devByTwo && !devByFive) {
			char temp[0x10];
			sprintf(temp, "%d", i);
			str = std::string(temp);
		}

		str += " ";

		std::cout << str;
	}
}

