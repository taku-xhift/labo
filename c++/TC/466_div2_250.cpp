


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;


class LotteryTicket {
public:
	static string buy(int price, int b1, int b2, int b3, int b4) {
		vector<int> list;
		list.push_back(b1);
		list.push_back(b2);
		list.push_back(b3);
		list.push_back(b4);

		list.push_back(b1+b2);
		list.push_back(b1+b3);
		list.push_back(b1+b4);
		list.push_back(b2+b3);
		list.push_back(b2+b4);
		list.push_back(b3+b4);

		list.push_back(b1+b2+b3);
		list.push_back(b1+b2+b4);
		list.push_back(b1+b3+b4);
		list.push_back(b2+b3+b4);

		list.push_back(b1+b2+b3+b4);

		//auto ite = find_if(list.begin(), list.end(), [price](int x){ return x == price; });

		for (int i = 0; i < list.size(); ++i) {
			if (list.at(i) == price) {
				return "POSSIBLE";
			}
		}

		return "IMPOSSIBLE";
	}
};


int main(int argc, char* argv[]) {
	int price, b1, b2, b3, b4;

	stringstream ss;
	ss << argv[1];
	ss >> price;
	ss.str("");
	ss.clear();

	ss << argv[2];
	ss >> b1;
	ss.str("");
	ss.clear();

	ss << argv[3];
	ss >> b2;
	ss.str("");
	ss.clear();

	ss << argv[4];
	ss >> b3;
	ss.str("");
	ss.clear();

	ss << argv[5];
	ss >> b4;
	ss.str("");
	ss.clear();

	cout << LotteryTicket::buy(price, b1, b2, b3, b4) << endl;


	//cout << LotteryTicket::buy(10, 1, 5, 10, 50) << endl;
}


