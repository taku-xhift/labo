


#include <iostream>
#include <string>
#include <vector>


using namespace std;

typedef unsigned long long int ull;
typedef unsigned long int ul;



class BallsSeparating {
	static int minOperations(vector <int> red, vector <int> green, vector <int> blue) {
		
	}


	static void test() {
		{
			vector<int> red;
			red.push_back(1);
			red.push_back(1);
			red.push_back(1);
			vector<int> blue;
			red.push_back(1);
			red.push_back(1);
			red.push_back(1);
			vector<int> green;
			red.push_back(1);
			red.push_back(1);
			red.push_back(1);

			if (minOperations(red, green, blue) == 6) {
				cout << "0.ok\n";
			}
		}
		{
			vector<int> red;
			red.push_back(5);
			vector<int> blue;
			red.push_back(6);
			vector<int> green;
			red.push_back(8);

			if (minOperations(red, green, blue) == -1) {
				cout << "1.ok\n";
			}
		}
		{
			vector<int> red;
			red.push_back(4);
			red.push_back(6);
			red.push_back(5);
			red.push_back(7);
			vector<int> blue;
			red.push_back(7);
			red.push_back(4);
			red.push_back(6);
			red.push_back(3);
			vector<int> green;
			red.push_back(6);
			red.push_back(5);
			red.push_back(3);
			red.push_back(8);

			if (minOperations(red, green, blue) == 37) {
				cout << "2.ok\n";
			}
		}
		{
			vector<int> red;
			red.push_back(7);
			red.push_back(12);
			red.push_back(9);
			red.push_back(9);
			red.push_back(7);
			vector<int> blue;
			red.push_back(7);
			red.push_back(10);
			red.push_back(8);
			red.push_back(8);
			red.push_back(9);
			vector<int> green;
			red.push_back(8);
			red.push_back(9);
			red.push_back(5);
			red.push_back(6);
			red.push_back(13);

			if (minOperations(red, green, blue) == 77) {
				cout << "3.ok\n";
			}
		}
		{
			vector<int> red;
			red.push_back(842398);
			red.push_back(491273);
			red.push_back(958925);
			red.push_back(849859);
			red.push_back(771363);
			red.push_back(67803);
			red.push_back(184892);
			red.push_back(391907);
			red.push_back(256150);
			red.push_back(75799);

			vector<int> blue;
			red.push_back(268944);
			red.push_back(342402);
			red.push_back(894352);
			red.push_back(228640);
			red.push_back(903885);
			red.push_back(908656);
			red.push_back(414271);
			red.push_back(292588);
			red.push_back(852057);
			red.push_back(889141);

			vector<int> green;
			red.push_back(662939);
			red.push_back(340220);
			red.push_back(600081);
			red.push_back(390298);
			red.push_back(376707);
			red.push_back(372199);
			red.push_back(435097);
			red.push_back(40266);
			red.push_back(145590);
			red.push_back(505103);

			if (minOperations(red, green, blue) == 7230607) {
				cout << "4.ok\n";
			}
		}
	}
};


int main() {
	
}

