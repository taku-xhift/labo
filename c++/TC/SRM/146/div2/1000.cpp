

//#include <initializer_list>



#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


class BridgeCrossing {
public:
	static int minTime(vector <int> times) {
		vector<int> left(times.begin(), times.end());
		std::sort(left.begin(), left.end());
		vector<int> right;

		int ret = 0;
		bool stateFast = true;
		int time = 0;

		while (true) {
			if (left.empty()) {
				break;
			}
			if (left.size() == 1) {
				ret += *left.begin();
				break;
			}
			if (left.size() == 2) {
				ret += *(++left.begin());
				break;
			}

			if (stateFast) {
				vector<int>::iterator ite = left.begin();
				right.insert(right.begin(), *ite);
				time = *(++ite);
				right.insert(right.begin(), time);

				std::sort(right.begin(), right.end());

				ret += time;

				left.erase(left.begin(), left.begin()+2);

				time = *right.begin();
				left.insert(left.begin(), time);
				right.erase(right.begin());

				std::sort(left.begin(), left.end());

				ret += time;
			} else {
				vector<int>::reverse_iterator ite = left.rbegin();
				time = *ite;
				right.insert(right.end(), time);
				right.insert(right.end(), *(++ite));

				std::sort(right.begin(), right.end());

				ret += time;

				vector<int>::iterator begin = (left.rbegin() + 2).base();
				vector<int>::iterator end = (left.rbegin()).base();
				//left.erase(left.end()-1, left.end()-3);
				left.erase(begin, end);

				time = *right.begin();
				left.insert(left.begin(), time);
				right.erase(right.begin());

				std::sort(left.begin(), left.end());

				ret += time;
			}

			stateFast ^= 1;
		}

		return ret;
	}
};



int main() {
	//vector<int> arg = { 1, 2, 5, 10 };
	//vector<int> arg = { 1, 2, 3, 4, 5 };
	//vector<int> arg = { 1, 2, 3, 50, 99, 100 };
	//{100, 100, 100, 100, 100, 100};
	//vector<int> arg = {99, 13, 67, 32, 5, 17};
	//vector<int> arg;
	for (int i = 0; i < 5; ++i) {
		//arg.push_back(100);
		//arg.push_back(i+1);
	}
	vector<int> arg;
	arg.push_back(99);
	arg.push_back(13);
	arg.push_back(67);
	arg.push_back(32);
	arg.push_back(5);
	arg.push_back(17);

	cout << BridgeCrossing::minTime(arg) << endl;
}


