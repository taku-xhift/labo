


#include <iostream>
#include <vector>
#include <string>


using namespace std;


class GoldenChain {
	static int minCuts(vector<int> sections) {
		
	}

	static void test() {
		{
			vector<int> arg;
			arg.push_back(2000000000);
			if (minCuts(arg) == 1) {
				cout << "1.ok\n";
			}
		}
		{
			vector<int> arg;
			for (int i = 1; i <= 50; ++i) {
				arg.push_back(i);
			}
			if (minCuts(arg) == 42) {
				cout << "2.ok\n";
			}
		}
		{
			vector<int> arg;
			arg.push_back(20000000);
			arg.push_back(20000000);
			arg.push_back(2000000000);
			if (minCuts(arg) == 3) {
				cout << "3.ok\n";
			}
		}
		{
			vector<int> arg;
			for (int i = 0; i < 5; ++i) {
				arg.push_back(10);
			}
			for (int i = 0; i < 5; ++i) {
				arg.push_back(1);
			}
			if (minCuts(arg) == 5) {
				cout << "4.ok\n";
			}
		}
		{
			vector<int> arg;
			arg.push_back(1);
			arg.push_back(10);
			if (minCuts(arg) == 1) {
				cout << "5.ok\n";
			}
		}
	}
};


int main() {
	
}


