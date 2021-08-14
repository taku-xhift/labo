


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;


class MostProfitable
{
public:
	static string bestItem(vector <int> costs, vector <int> prices, vector <int> sales, vector <string> items) {
		multimap<int, string, greater<int> > list;
		for (int i = 0; i < costs.size(); ++i) {
			list.insert(multimap<int, string>::value_type((prices[i]-costs[i]) * sales[i], items[i]));
		}

		multimap<int, string, greater<int> >::iterator ite = list.begin();

		if (ite->first <= 0) {
			return "";
		} else {
			return ite->second;
		}
	}

	static void test() {
		{
			vector<int> costs;
			costs.push_back(100);
			costs.push_back(120);
			costs.push_back(150);
			costs.push_back(1000);

			vector<int> prices;
			prices.push_back(110);
			prices.push_back(110);
			prices.push_back(200);
			prices.push_back(2000);

			vector<int> sales;
			sales.push_back(20);
			sales.push_back(100);
			sales.push_back(200);
			sales.push_back(2000);

			vector<string> items;
			items.push_back("Video Card");
			items.push_back("256M Mem");
			items.push_back("CPU/Mobo combo");
			items.push_back("Complete machine");

			if (bestItem(costs, prices, sales, items) == "Complete machine") {
				cerr << "1.ok\n";
			}
		}
		{
			vector<int> costs;
			costs.push_back(10);
			costs.push_back(10);

			vector<int> prices;
			prices.push_back(11);
			prices.push_back(12);

			vector<int> sales;
			sales.push_back(2);
			sales.push_back(1);

			vector<string> items;
			items.push_back("A");
			items.push_back("B");

			if (bestItem(costs, prices, sales, items) == "A") {
				cerr << "3.ok\n";
			}
		}
	}
};



int main() {
	MostProfitable::test();
}


