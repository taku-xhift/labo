


#include <iostream>
#include <string>
#include <vector>

using namespace std;


class CircleGame {
public:

	static bool Is13(vector<int>::const_iterator begin, vector<int>::const_iterator end) {
		int sum = *begin;
		++begin;

		while (begin != end) {
			sum += *begin;
		}

		if (sum == 13) {
			return true;
		} else {
			return false;
		}
	}

	static int cardsLeft(string deck) {
		deck.remove(0, 'K');
		vector<int> list(deck.begin(), deck.end());
		int length = 0;
		int nowPos = 0;

		while (length != list.size()) {
			vector<int> begin = list.begin() + nowPos;
			vector<int> end = list.begin() + length;
			if (Is13(begin, end)) {
				list.erase(begin, end);
			}
		}

		return list.size();
	}

	static void test() {
		if (cardsLeft("KKKKKKKKKK") == 0) {
			cout << "1.ok\n";
		}
		if (cardsLeft("KKKKKAQT23") == 1) {
			cout << "2.ok\n";
		}
		if (cardsLeft("KKKKATQ23J") == 6) {
			cout << "3.ok\n";
		}
		if (cardsLeft("AT68482AK6875QJ5K9573Q") == 4) {
			cout << "4.ok\n";
		}
		if (cardsLeft("AQK262362TKKAQ6262437892KTTJA332") == 24) {
			cout << "5.ok\n";
		}

		cout << "self check\n";

		if (cardsLeft("358") == 0) {
			cout << "6.ok\n";
		}
		if (cardsLeft("6185822") == 1) {
			cout << "7.ok\n";
		}
	}
};



int main() {
	CircleGame::test();
}


