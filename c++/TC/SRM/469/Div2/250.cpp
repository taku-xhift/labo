


#include <array>


#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


class TheMoviesLevelOneDivTwo {
public:

	static int find(int n, int m, vector <int> row, vector <int> seat) {
		vector<vector<int> > seats;
		seats.resize(n);
		for (int i = 0; i < seats.size(); ++i) {
			seats[i].resize(m);
		}

		for (int i = 0; i < row.size(); ++i) {
			seats[row[i]-1][seat[i]-1] = 1;
		}

		int ret = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m -1; ++j) {
				if (seats[i][j] == 0 && seats[i][j+1] == 0) {
					++ret;
				}
			}
		}

		return ret;
	}

	static void test() {
		{
			array<int, 2> arg1 = {1, 2};
			array<int, 2> arg2 = {2, 3};
			if (find(2, 3, vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end())) == 1) {
				cerr << "0.ok\n";
			}
		}
		{
			array<int, 6> arg1 = {1, 1, 1, 2, 2, 2};
			array<int, 6> arg2 = {1, 2, 3, 1, 2, 3};
			if (find(2, 3, vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end())) == 0) {
				cerr << "1.ok\n";
			}
		}
		{
			array<int, 1> arg1 = {1};
			array<int, 1> arg2 = {1};
			if (find(4, 7, vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end())) == 23) {
				cerr << "2.ok\n";
			}
		}
		{
			array<int, 10> arg1 = {1, 9, 6, 10, 6, 7, 9, 3, 9, 2};
			array<int, 10> arg2 = {7, 7, 3, 3,  7, 1, 5, 1, 6, 2};
			if (find(10, 8, vector<int>(arg1.begin(), arg1.end()), vector<int>(arg2.begin(), arg2.end())) == 54) {
				cerr << "3.ok\n";
			}
		}
	}

};


int main() {
	TheMoviesLevelOneDivTwo::test();
}



