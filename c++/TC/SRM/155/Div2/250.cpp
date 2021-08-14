

#include <array>


#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;



class Quipu {
public:

	static int readKnots(string knots) {
		stringstream ss;

		int xCounter = 0;
		bool countedSegment = false;
		for (int i = 1; i < knots.size(); ++i) {
			if (knots[i] == 'X') {
				++xCounter;
				countedSegment = false;
			} else if (knots[i] == '-' && countedSegment) {
				ss << 0;
				countedSegment = false;
			} else if (knots[i] == '-') {
				countedSegment = true;
				ss << xCounter;
				xCounter = 0;
			}
		}

		int ret = 0;
		ss >> ret;
		return ret;
	}


	static void test() {
		if (readKnots("-XX-XXXX-XXX-") == 243) {
			cerr << "0.ok\n";
		}
		if (readKnots("-XX--XXXX---XXX-") == 204003) {
			cerr << "1.ok\n";
		}
		if (readKnots("-X-") == 1) {
			cerr << "2.ok\n";
		}
		if (readKnots("-X-------") == 1000000) {
			cerr << "3.ok\n";
		}
		if (readKnots("-XXXXXXXXX--XXXXXXXXX-XXXXXXXXX-XXXXXXX-XXXXXXXXX-") == 909979) {
			cerr << "4.ok\n";
		}
	}

};




int main() {
	Quipu::test();
}


