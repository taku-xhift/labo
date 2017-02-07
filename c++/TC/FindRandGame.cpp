


#include <iostream>
#include <cstdlib>
#include <ctime>


int main() {
	srand(time(NULL));
	const int answer = rand()%100;

	std::cout << "Please input some number(0 ~ 100).\n";
	std::cout << "If you wont to end this game, input Ctrl + C\n";

	int num = 0;

	std::cout << "Debug Answer : " << answer << "\n";

	while (true) {
		std::cin >> num;

		if (num == answer) {
			std::cout << "Collect !!!\n";
			break;
		} else if (num > answer) {
			std::cout << num << " is too big.\n";
		} else if (num < answer) {
			std::cout << num << " is too small.\n";
		}
	}
}


