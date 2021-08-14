

#include <array>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;



class NextOrPrev {
public:
	static bool overTest(int lStart, int lGoal, int rStart, int rGoal) {
		const int lDiff = lStart - lGoal;
		const int rDiff = rStart - rGoal;

		// どっちかが覆ってしまっている
		if ((lStart <= rStart && rGoal <= lGoal)
			|| (rStart <= lStart && lGoal <= rGoal))
		{
			return false;
		}

		// 進行の向きが違う
		if (lDiff * rDiff < 0) {
			if (((lGoal >= rGoal) && (lStart <= rStart))
				|| ((rStart >= lStart) && (lGoal >= rStart)))
			{
				return false;
			}
		}

		return true;
	}


	static int getMinimum(int nextCost, int prevCost, string start, string goal) {
		// check
		for (int i = 0; i < start.size(); ++i) {
			for (int j = i + 1; j < start.size(); ++j) {
				if (!overTest(start[i], goal[i], start[j], goal[j])) {
					return -1;
				}
			}
		}

		int score = 0;
		for (int i = 0; i < start.size(); ++i) {
			const int diff = start[i] - goal[i];
			if (diff < 0) {
				// goal の方が後の文字
				// diff は - なので -=
				score -= diff * nextCost;
			} else {
				score += diff * prevCost;
			}
		}

		return score;
	}

	static void test() { 
		int count = 0;
		if (getMinimum(5, 8, "ae", "bc") == 21) {
			cerr << count << ".ok\n";
		}
		++count;
		if (getMinimum(5, 8, "ae", "cb") == -1) {
			cerr << count << ".ok\n";
		}
		++count;
		if (getMinimum(1, 1, "srm", "srm") == 0) {
			cerr << count << ".ok\n";
		}
		++count;
		if (getMinimum(10, 1, "acb", "bdc") == 30) {
			cerr << count << ".ok\n";
		}
		++count;
		if (getMinimum(10, 1, "zyxw", "vuts") == 16) {
			cerr << count << ".ok\n";
		}
		++count;

		cerr << "system test\n";

		if (getMinimum(217, 14, "pzm", "uya") == 1267) {
			cerr << count << ".ok\n";
		}
		++count;
	}
};




int main() {
	NextOrPrev::test();
}


