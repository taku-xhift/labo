


#include <iostream>
#include <vector>


using namespace std;


class LeaguePicks {
public:
	static vector <int> returnPicks(int position, int friends, int picks) {
		vector<int> list;
		bool forward = true;
		int count = 1;
		for (int i = 0; i < picks; ++i) {
			list.push_back(count);
			if (forward) {
				++count;
			} else {
				--count;
			}

			if (count > friends) {
				forward ^= 1;
				count = friends;
			} else if (count <= 0) {
				forward ^= 1;
				count = 1;
			}
		}

		vector<int> ret;
		for (int i = 0; i < list.size(); ++i) {
			if (list[i] == position) {
				ret.push_back(i+1);
			}
		}

		return ret;
	}

	static void test() {
		{
			const vector<int>& ret = returnPicks(3, 6, 15);
			for (int i = 0; i < ret.size(); ++i) {
				cerr << ret[i] << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = returnPicks(1, 1, 10);
			for (int i = 0; i < ret.size(); ++i) {
				cerr << ret[i] << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = returnPicks(1, 2, 39);
			for (int i = 0; i < ret.size(); ++i) {
				cerr << ret[i] << ", ";
			}
			cerr << "\n";
		}
		{
			const vector<int>& ret = returnPicks(5, 11, 100);
			for (int i = 0; i < ret.size(); ++i) {
				cerr << ret[i] << ", ";
			}
			cerr << "\n";
		}
	}
};



int main() {
	LeaguePicks::test();
}


