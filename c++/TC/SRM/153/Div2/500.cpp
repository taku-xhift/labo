


#include <iostream>
#include <vector>
#include <string>



using namespace std;



class Inventory {
public:

	static int monthlyOrder(vector <int> sales, vector <int> daysAvailable) {
		double sum = 0;
		int validCount = 0;

		for (int i = 0; i < sales.size(); ++i) {
			if (daysAvailable[i] == 0) {
				continue;
			}
			sum += sales[i] * (double)(30.0/daysAvailable[i]);
			++validCount;
		}

		if (validCount == 0) {
			return 0;
		}

		return (int)(sum/validCount + 0.9999999);
	}

	static void test() {
		{
			vector<int> sales;
			sales.push_back(5);
			vector<int> daysAvailable;
			daysAvailable.push_back(15);
			if (monthlyOrder(sales, daysAvailable) == 10) {
				cerr << "1.ok\n";
			}
		}
		{
			vector<int> sales;
			sales.push_back(75);
			sales.push_back(120);
			sales.push_back(0);
			sales.push_back(93);
			vector<int> daysAvailable;
			daysAvailable.push_back(24);
			daysAvailable.push_back(30);
			daysAvailable.push_back(0);
			daysAvailable.push_back(30);
			if (monthlyOrder(sales, daysAvailable) == 103) {
				cerr << "2.ok\n";
			}
		}
		{
			vector<int> sales;
			sales.push_back(8773);
			vector<int> daysAvailable;
			daysAvailable.push_back(16);
			if (monthlyOrder(sales, daysAvailable) == 16450) {
				cerr << "3.ok\n";
			}
		}
		{
			vector<int> sales;
			sales.push_back(1115);
			sales.push_back(7264);
			sales.push_back(3206);
			sales.push_back(6868);
			sales.push_back(7301);
			vector<int> daysAvailable;
			daysAvailable.push_back(1);
			daysAvailable.push_back(3);
			daysAvailable.push_back(9);
			daysAvailable.push_back(4);
			daysAvailable.push_back(18);
			if (monthlyOrder(sales, daysAvailable) == 36091) {
				cerr << "4.ok\n";
			}
		}
	}
};





int main() {
	Inventory::test();
}


