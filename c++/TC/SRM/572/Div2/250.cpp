

#include <array>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


#define ALL(arg) (vector<int>(arg.begin(), arg.end()))


using namespace std;


class EasyHomework {
public:
	static string determineSign(vector <int> A) {
		int negCount = 0;
		for (int i = 0; i < A.size(); ++i) {
			if (A[i] == 0) {
				return "ZERO";
			} else if (A[i] < 0) {
				++negCount;
			}
		}

		if (negCount%2 == 0) {
			return "POSITIVE";
		} else {
			return "NEGATIVE";
		}
	}

	static void test() {
		{
			array<int, 3> arg = {5, 7, 2};
			cerr << determineSign(ALL(arg)) << endl;
		}
		{
			array<int, 3> arg = {-5, 7, 2};
			cerr << determineSign(ALL(arg)) << endl;
		}
		{
			array<int, 4> arg = {5, 7, 2, 0};
			cerr << determineSign(ALL(arg)) << endl;
		}
		{
			array<int, 4> arg = {3, -14, 159, -26};
			cerr << determineSign(ALL(arg)) << endl;
		}
		{
			array<int, 1> arg = {-1000000000};
			cerr << determineSign(ALL(arg)) << endl;
		}
		{
			array<int, 19> arg = {123, -456, 789, -101112, 131415, 161718, 192021, 222324, 252627, 282930, 313233, 343536, 373839, 404142, 434445, 464748, 495051, 525354, 555657};
			cerr << determineSign(ALL(arg)) << endl;
		}
	}
};




int main() {
	EasyHomework::test();
}


