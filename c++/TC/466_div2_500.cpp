


#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

#ifdef _MSC_VER
typedef __int64 uint64_t;
#endif


class LotteryCheating {
public:
	static int minimalChange(string ID) {
		if (ID == "1") {
			return 0;
		}

		vector<uint64_t> declList;

		uint64_t num = 1;
		for (int i = 0; i < 33; ++i) {
			declList.push_back(num);
			num *= 2;
		}

		stringstream ss;
		ss << ID;
		uint64_t intID = 0;
		ss >> intID;

		ss.str("");
		ss.clear();

		int count = 0;
		for (; count < declList.size(); ++count) {
			if (declList.at(count) > intID) {
				break;
			}
		}

		string target2;

		ss << declList.at(count-1);
		ss >> target2;
		ss.str("");
		ss.clear();

		const int retWith2 = nearCount(target2, ID);

		string target0;
		target0.append(ID.size(), '0');
		const int retWith0 = nearCount(target0, ID);

		if (retWith0 > retWith2) {
			return retWith2;
		} else {
			return retWith0;
		}
	}

	static int nearCount(string target, string ID) {
		string targetTemp = "";
		string IDTemp = "";
		int ret = 0;

		for (int i = 0; i < target.size(); ++i) {
			if (target.at(i) != ID.at(i)) {
				++ret;
			}
		}

		return ret;
	}
};


int main(int argc, char* argv[]) {

	std::cout << LotteryCheating::minimalChange("7654321") << std::endl;
}


