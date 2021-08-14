


#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <sstream>


using namespace std;


class ProfitCalculator {
public:
	static int percent(vector <string> items) {
		stringstream ss;

		double price = .0;
		double costs = .0;

		double tempPrice = .0;
		double tempCosts = .0;

		for (int i = 0; i < items.size(); ++i) {
			ss << items[i];
			ss >> tempPrice;
			ss >> tempCosts;
			ss.str("");
			ss.clear();

			price += tempPrice;
			costs += tempCosts;
		}

		if (tempPrice == .0) {
			return 0;
		} else {
			const double sale = price - costs;
			const int ret = (int)(sale * 100.0/price);
			return ret;
		}
	}

	static void test() {
		{
			array<string, 3> arg = {"012.99 008.73","099.99 050.00","123.45 101.07"};
			if (percent(vector<string>(arg.begin(), arg.end())) == 32) {
				cerr << "1.ok\n";
			}
		}
	}
};



int main() {
	ProfitCalculator::test();
}


