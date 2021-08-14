


#include <iostream>
#include <string>
#include <vector>


using namespace std;

typedef unsigned long long int ull;
typedef unsigned long int ul;



class TheSimilarNumbers {
public:

	static bool IsSimilar(int lower, int upper) {
		if (lower <= 10*upper && upper <= 10*lower) {
			return true;
		} else {
			return false;
		}
	}


	static int find(int lower, int upper) {
		int temp = upper;
		int count = 0;
		while (temp != 0) {
			++count;
			temp /= 10;
		}

		return count;
	}


	static void test() {
		if (find(1, 10) == 1) {
			cout << "1.ok\n";
		}
		if (find(5, 511) == 3) {
			cout << "2.ok\n";
		}
		if (find(5, 4747) == 3) {
			cout << "3.ok\n";
		}
		if (find(1, 1000000) == 6) {
			cout << "4.ok\n";
		}
		if (find(10, 10110) == 3) {
			cout << "5.ok\n";
		}
		cout << "self check\n";

		
		if (find(1, 1) == 1) {
			cout << "6.ok\n";
		}
	}
};



int main() {
	TheSimilarNumbers::test();
}

