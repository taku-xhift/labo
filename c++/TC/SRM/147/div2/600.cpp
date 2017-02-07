


#include <iostream>
#include <vector>
#include <string>


using namespace std;


class PeopleCircle {
public:
	//static string order(int numMales, int numFemales, int K) {
	static string order(int numMales, int numFemales, int K, string answer = "") {
		const int all = numMales + numFemales;
		string ret(numMales + numFemales, 'M');

		if (numFemales == 0) {
			return ret;
		}

		if (numMales == 0) {
			return string(numFemales, 'F');
		}

		int moveCount = 0;
		int nowPos = 0;
		for (int i = 1; i <= numFemales; ++i, moveCount = 0) {
			const int nowNum = numMales + (numFemales -i+1);
			moveCount = (K-1) % nowNum;

			while (moveCount != 0) {
				++nowPos;
				if (nowPos >= ret.size()) {
					nowPos -= ret.size();
				}
				if (ret[nowPos] == 'M') {
					--moveCount;
				}
			}

			const int access = nowPos;
			ret[access] = 'F';

			if (ret[access] != answer[access]) {
				cout << "Error in " << access << "\n";
			}

			do {
				++nowPos;
				if (nowPos >= ret.size()) {
					nowPos -= ret.size();
				}
			} while (ret[nowPos] != 'M');
		}

		return ret;
	}


	static void test() {
		order(2, 3, 10, "MFFMF");

		if (order(5, 3, 2, "MFMFMFMM") == "MFMFMFMM") {
			cout << "1. ok\n";
		}
		if (order(25, 25, 1000, "MMMMMFFFFFFMFMFMMMFFMFFFFFFFFFMMMMMMMFFMFMMMFMFMMF") == "MMMMMFFFFFFMFMFMMMFFMFFFFFFFFFMMMMMMMFFMFMMMFMFMMF") {
			cout << "2. ok\n";
		}
		if (order(5, 5, 3, "MFFMMFFMFM") == "MFFMMFFMFM") {
			cout << "3. ok\n";
		}
		if (order(1, 0, 245) == "M") {
			cout << "4. ok\n";
		}

		cout << "self check\n";

		if (order(0, 1, 245) == "F") {
			cout << "5. ok\n";
		}
		if (order(0, 0, 245) == "") {
			cout << "6. ok\n";
		}
	}

};



int main() {
	PeopleCircle::test();
}


