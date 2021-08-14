

#include <iostream>
#include <bitset>
#include <vector>

int main() {
	std::bitset<2> single_;
	std::bitset<2> double_[2];
	std::vector<std::bitset<2> > vecDouble_(2);

	single_[1] = true;
	double_[0][1] = true;
	double_[1][0] = true;

	std::cout << single_.test(0) << std::endl;
	std::cout << single_.test(1) << std::endl;

	std::cout << double_[0].test(0) << std::endl;
	std::cout << double_[0].test(1) << std::endl;
	std::cout << double_[1].test(0) << std::endl;
	std::cout << double_[1].test(1) << std::endl;
}

