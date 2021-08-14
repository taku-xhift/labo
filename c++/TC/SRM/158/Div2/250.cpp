


#include <array>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


#define ALL(arg) (arg.begin(), arg.end())

using namespace std;



class TireRotation {
public:
	int getCycle(string initial, string current) {
		int count = 1;

		string temp = initial;
		string buf("ffff");

		while (temp != current || count == 4) {
			buf[0] = temp[3];
			buf[1] = temp[2];
			buf[2] = temp[0];
			buf[3] = temp[1];
			temp = buf;
			++count;
		}


		if (count == 4) {
			return -1;
		} else {
			return count;
		}
	}
};



int main() {
	TireRotation obj;
	int count = 0;

	if (obj.getCycle("ABCD", "ABCD") == 1) {
		cerr << count << ".ok\n";
	}
	++count;

	if (obj.getCycle("ABCD", "DCAB") == 2) {
		cerr << count << ".ok\n";
	}
	++count;

	if (obj.getCycle("ABCD", "CDBA") == 4) {
		cerr << count << ".ok\n";
	}
	++count;

	if (obj.getCycle("ABCD", "ABDC") == -1) {
		cerr << count << ".ok\n";
	}
	++count;

	if (obj.getCycle("ZAXN", "XNAZ") == 4) {
		cerr << count << ".ok\n";
	}
	++count;
}


