

#include <initializer_list>



#include <iostream>
#include <vector>
#include <map>

using namespace std;


class YahtzeeScore {
public:
	static int maxPoints(vector <int> toss) {
		map<int, int> list;
		for (int i = 0; i < toss.size(); ++i) {
			++list[toss[i]];
		}

		int ret = 0;
		for (map<int, int>::const_iterator ite = list.begin(); ite != list.end(); ++ite) {
			const int value = ite->first * ite->second;

			if (ret < value) {
				ret = value;
			}
		}

		return ret;
	}
};


int main() {
	vector<int> arg = { 5, 3, 5, 3, 3 };

	cout << YahtzeeScore::maxPoints(arg) << endl;
}


