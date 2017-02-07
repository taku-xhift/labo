


#include <array>


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>



using namespace std;


class PaternityTest {
public:

	static bool IsFather(string child, string mother, string men) {
		vector<bool> checkList(child.size());
		for (int i = 0; i < child.size(); ++i) {
			if (child[i] == men[i]) {
				checkList[i] = true;
			}
		}

		// 半分は同じ、という条件を満たせたか
		int sameCount = 0;
		for (int i = 0; i < checkList.size(); ++i) {
			if (checkList[i]) {
				++sameCount;
			}
		}
		if (sameCount < child.size()/2) {
			return false;
		}


		// 父親にとって不一致のものを母親が補えるか
		int mothersSame = 0;
		for (int i = 0; i < child.size(); ++i) {
			if (!checkList[i] && child[i] == mother[i]) {
				++mothersSame;
			}
		}

		if (mothersSame < child.size() - sameCount) {
			return false;
		} else {
			return true;
		}
	}

	static vector <int> possibleFathers(string child, string mother, vector <string> men) {
		vector<int> ret;
		for (int i = 0; i < men.size(); ++i) {
			if (IsFather(child, mother, men[i])) {
				ret.push_back(i);
			}
		}

		return ret;
	}


	static void test() {
		{
			array<string, 2> arg = { "SBTD", "QRCD" };
			auto ret = possibleFathers("ABCD", "AXCY", std::vector<string>(arg.begin(), arg.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<string, 3> arg = { "ABCY", "ASTD", "QBCD" };
			auto ret = possibleFathers("ABCD", "ABCX", std::vector<string>(arg.begin(), arg.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<string, 4> arg = { "ABABAB", "ABABCC", "ABCCDD", "CCDDEE" };
			auto ret = possibleFathers("ABABAB", "ABABAB", std::vector<string>(arg.begin(), arg.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<string, 5> arg = {"YZQLDPWT", "BZELSWQM", "OZGPSFKT", "GZTKFYQT", "WQJLSMQT"};
			auto ret = possibleFathers("YZGLSYQT", "YUQRWYQT", std::vector<string>(arg.begin(), arg.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
		{
			array<string, 5> arg = {
				"WNELPYCHXWXPCMNKDDXD",
				"WFEEPYCHFWDNPMKKALIW",
				"WSEFPYCHEWEFGMPKIQCK",
				"WAEXPYCHAWEQXMSKYARN",
				"WKEXPYCHYWLLFMGKKFBB"
			};
			auto ret = possibleFathers("WXETPYCHUWSQEMKKYNVP", "AXQTUQVAUOSQEEKCYNVP", std::vector<string>(arg.begin(), arg.end()));
			for (auto& val : ret) {
				cerr << val << ", ";
			}
			cerr << "\n";
		}
	}

};





int main() {
	PaternityTest::test();
}


