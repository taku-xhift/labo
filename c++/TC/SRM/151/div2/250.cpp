


#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


class PrefixCode {
public:
	static string isOne(vector<string> words) {
		if (words.size() == 1) {
			return "Yes";
		}

		for (int i = 0; i < words.size(); ++i) {
			for (int j = 0; j < words.size(); ++j) {
				if (i == j) {
					continue;
				}

				if (words[j].find_first_of(words[i], 0) == 0) {
					stringstream ss;
					ss << "No, " << i;
					return ss.str();
				}
			}
		}

		return "Yes";
	}


	static void test() {
		{
			vector<string> arg;
			arg.push_back("trivial");
			if (isOne(arg) == "Yes") {
				cerr << "1.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("10001");
			arg.push_back("011");
			arg.push_back("100");
			arg.push_back("001");
			arg.push_back("10");
			if (isOne(arg) == "No, 2") {
				cerr << "2.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("no");
			arg.push_back("nosy");
			arg.push_back("neighbors");
			arg.push_back("needed");
			if (isOne(arg) == "No, 0") {
				cerr << "3.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("1010");
			arg.push_back("11");
			arg.push_back("100");
			arg.push_back("0");
			arg.push_back("1011");
			if (isOne(arg) == "Yes") {
				cerr << "4.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("No");
			arg.push_back("not");
			if (isOne(arg) == "Yes") {
				cerr << "5.ok\n";
			}
		}
	}
};


int main() {
	PrefixCode::test();
}

