


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <bitset>


template<typename T>
std::string lexical_cast(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}


int CountStr(const std::string& source, int num) {
	int hitCount = 0;
	std::stringstream ss;
	ss << num;

	for (int i = 0; i < source.size(); ++i) {
		// 文字が何なのか判定してみる
		if (source.at(i) == ss.str()[0]) {
			++hitCount;
		}
	}

	return hitCount;
}


std::string MakeAnswer() {
	srand(time(NULL));

	while (true) {
	RoopStart:

		const int ans = rand()%10000;

		if (ans <= 1000) {
			continue;
		}

		const std::string& str = lexical_cast(ans);

		for (int i = 0; i < 10; ++i) {
			const int hitCount = CountStr(str, i);

			// 同じ文字が２つ以上はだめ
			if (hitCount >= 2) {
				goto RoopStart;
			}
		}

		return str;
	}
}


int main() {
	const std::string& answer = MakeAnswer();

	std::cout << "Debug Answer : " << answer << "\n";
	std::cout << "Input 4 number\n";


	int userNumber = 0;

	while (true) {
		std::cin >> userNumber;
		//std::cout << userNumber << " ";

		const std::string& userNumStr = lexical_cast(userNumber);

		std::bitset<4> hitPos;

		int hitCount = 0;
		for (int i = 0; i < 4; ++i) {
			if (answer[i] == userNumStr[i]) {
				++hitCount;
				hitPos[i] = true;
			}
		}

		int blowCount = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (answer[j] == userNumStr[i] && !hitPos[i]) {
					++blowCount;
				}
			}
		}

		if (hitCount == 4) {
			std::cout << "You are collct!!!\n";
			break;
		} else {
			std::cout << hitCount << "hit, " << blowCount << "blow\n";
		}
	}
}


