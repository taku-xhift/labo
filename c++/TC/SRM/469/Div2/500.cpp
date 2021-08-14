

#include <array>


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


#define ALL(arg) arg.begin(), arg.end()



using namespace std;


struct Result {
	Result(const vector<int>& length, const vector<int>& scary, const vector<int>& list)
		: minutes_(0)
		, list_(list)
	{
		int scared = 75;
		int temp = 0;

		for (int i = 0; i < list.size(); ++i) {
			temp = scared - scary[i];

			if (temp < -0.5) {
				this->minutes_ += scared;
			}

			temp += 47 - length[i] - scary[i];

			if (temp < -0.5) {
				this->minutes_ += length[i] - temp;
			}

			scared = temp;
			this->minutes_ += length[i];
		}
	}


	bool operator<(const Result& other) const {
		return this->minutes_ < other.minutes_;
	}

	int minutes_;
	vector<int> list_;
};

class TheMoviesLevelTwoDivTwo {
public:
	static vector <int> find(vector <int> length, vector <int> scary) {
		vector<Result> list;

		vector<int> idList(length.size());

		do {
			list.push_back(Result(length, scary, idList));
		} while (next_permutation(ALL(idList)));

		sort(ALL(list));

		return list.begin()->list_;
	}

	static void test() {
		{
			array<int, 2> arg1 = {100, 50};
			array<int, 2> arg2 = {1, 1};
			auto ret = find(vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<int, 2> arg1 = {100, 50};
			array<int, 2> arg2 = {1, 49};
			auto ret = find(vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<int, 4> arg1 = {100, 100, 100, 100};
			array<int, 4> arg2 = {77, 76, 75, 74};
			auto ret = find(vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<int, 1> arg1 = {100};
			array<int, 1> arg2 = {99};
			auto ret = find(vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
	}

};



int main() {
	TheMoviesLevelTwoDivTwo::test();
}


