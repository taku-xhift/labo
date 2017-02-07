

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
// #include <maniplator>

bool IsReversible(const std::string& str) {
	std::size_t count = str.length()/2;
	if (count == 0) {
		return true;
	}

	auto begin = str.cbegin();
	auto rbegin = str.crbegin();

	for (std::size_t i = 0; i < count; ++i) {
		char beginVal = *begin;
		char rbeginVal = *rbegin;
		if (beginVal != rbeginVal) {
			return false;
		}
		++begin;
		++rbegin;
	}

	return true;
}


bool IsKaibun(int i) {
	// std::cout << i << ":\n";

	std::stringstream ss;

	ss << i;
	auto str = ss.str();
	std::cout << "\t" << str << std::endl;
	bool isReversible = IsReversible(str);
	if (isReversible == false) {
		return false;
	}

	ss.clear();
	ss.str("");


	// ２進数のチェック
	std::bitset<32> binary(i);
	bool isFirst = true;
	for (int i = binary.size() -1; i >= 0; --i) {
		int val = binary[i];
		if (binary[i] == 0) {
			if (isFirst == true) {
				continue;
			}
		} else {
			isFirst = false;
		}
		ss << binary[i];
	}
	str = ss.str();
	std::cout << "\t" << str << std::endl;
	const bool isBinaryReversible = IsReversible(ss.str());
	if (isBinaryReversible == false) {
		return false;
	}

	ss.clear();
	ss.str("");

	ss << std::oct << i;
	const bool isOctReversible = IsReversible(ss.str());
	str = ss.str();
	std::cout << "\t" << str << "\n";
	return isOctReversible;
}



int main() {
	// const bool nine = IsKaibun(9);
	// std::cout << "nine => " << nine << std::endl;

	// const bool ninty = IsKaibun(90);
	// std::cout << "ninty => " << ninty << std::endl;

	int i = 11;
	for (; ; ++i) {
		const bool isKaibun = IsKaibun(i);
		if (isKaibun == true) {
			break;
		}
	}
	// int i = 121;
	// const bool isKaibun = IsKaibun(i);

	std::cout << "the minimum => " << i << "\n";
}



