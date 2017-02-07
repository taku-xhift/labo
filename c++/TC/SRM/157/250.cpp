


#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;



class GuessTheNumber {
public:
	static int noGuesses(int upper, int answer) {
		int count = 1;

		int min = 1;
		int max = upper;
		int half = int(float(min + max)/2.0f);

		while (half != answer) {
			if (half < answer) {
				min = half + 1;
				half = int(float(min + max)/2.0f);
			} else {
				max = half - 1;
				half = int(float(min + max)/2.0f);
			}
			++count;
		}

		return count;
	}

	static void test() {
		if (GuessTheNumber::noGuesses(9, 6) == 3) {
			cerr << "0.ok\n";
		}
		if (GuessTheNumber::noGuesses(1000, 750) == 2) {
			cerr << "1.ok\n";
		}
		if (GuessTheNumber::noGuesses(643, 327) == 7) {
			cerr << "2.ok\n";
		}
		if (GuessTheNumber::noGuesses(157, 157) == 8) {
			cerr << "3.ok\n";
		}
		if (GuessTheNumber::noGuesses(128, 64) == 1) {
			cerr << "4.ok\n";
		}
	}
};


int main() {
	GuessTheNumber::test();
}


