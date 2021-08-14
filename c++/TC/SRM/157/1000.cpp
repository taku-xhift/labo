

#include <array>



#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <cmath>


using namespace std;


class HourGlass {
public:

	static vector <int> measurable(int glass1, int glass2) {
		set<int> list;

		const int diff = abs(glass1 - glass2);

		for (int i = 1; i <= 10; ++i) {
			list.insert(glass1 * i);
			list.insert(glass2 * i);

			list.insert(diff + glass1 * i);
			list.insert(diff + glass2 * i);
		}

		list.insert(diff + glass1 + diff);
		list.insert(diff + glass2 + diff);

		list.insert(diff + glass1 + diff + diff);
		list.insert(diff + glass2 + diff + diff);

		set<int>::iterator ite = list.begin();
		advance(ite, 10);

		return vector<int>(list.begin(), ite);
	}


	static void test() {
		{
			const vector<int>& ret = measurable(5, 7);
			for (auto val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = measurable(13, 5);
			for (auto val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = measurable(23, 23);
			for (auto val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = measurable(24, 30);
			for (auto val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = measurable(1, 50);
			for (auto val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
	}
};



int main() {
	HourGlass::test();
}

