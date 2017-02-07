


#include <array>



#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>


using namespace std;


struct IsSafe {
	double value_;
	int threshold_;

	IsSafe(double value)
		: value_(value)
		, threshold_(1)
	{
	}

	bool isSafe(double num) {
		if (value_ <= num && num <= value_ * 2*threshold_) {
			return true;
		}

		return false;
	}
};


class BenfordsLaw {
public:
	static int questionableDigit(vector <int> transactions, int threshold) {
		vector<IsSafe> expectedList;
		for (int i = 1; i < 10; ++i) {
			expectedList.push_back(IsSafe(log10(1+1.0/i)+threshold));
		}

		int times[9] = {0};
		stringstream ss;
		string tempStr;
		int tempInt = 0;
		for (int i = 0; i < transactions.size(); ++i) {
			ss << transactions[i];
			ss >> tempStr;

			ss.str("");
			ss.clear();

			ss << tempStr[0];
			ss >> tempInt;

			++times[tempInt - 1];

			ss.str("");
			ss.clear();
		}

		for (int i = 0; i < 10; ++i) {
			if (times[i] == 0) {
				continue;
			}
			if (!expectedList[i].isSafe(times[i])) {
				return i + 1;
			}
		}

		return -1;
	}

	static void test() {
		{
			array<int, 20> arg = { 5236,7290,200,1907,3336,9182,17,4209,8746,7932,
				6375,909,2189,3977,2389,2500,1239,3448,6380,4812 };

			if (questionableDigit(vector<int>(arg.begin(), arg.end()), 2) == 1) {
				cerr << "0.ok\n";
			}
		}
		{
			array<int, 10> arg = { 1,10,100,2,20,200,2000,3,30,300 };

			if (questionableDigit(vector<int>(arg.begin(), arg.end()), 2) == 2) {
				cerr << "1.ok\n";
			}
		}
		{
			array<int, 12> arg = { 9,87,765,6543,54321,43219,321987,21987,1987,345,234,123 };

			if (questionableDigit(vector<int>(arg.begin(), arg.end()), 2) == -1) {
				cerr << "2.ok\n";
			}
		}
		{
			array<int, 15> arg = { 1,2,3,4,5,6,7,8,7,6,5,4,3,2,1 };

			if (questionableDigit(vector<int>(arg.begin(), arg.end()), 8) == 9) {
				cerr << "3.ok\n";
			}
		}
	}
};



int main() {
	BenfordsLaw::test();
}


