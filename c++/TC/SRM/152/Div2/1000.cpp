

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


class ProblemWriting {
public:

	static string removeDot(string source) {
		size_t pos;

		const string rightPlus = ".+";
		while ((pos = source.find(rightPlus)) != string::npos) {
			source.replace(pos, 2, "+");
		}

		const string leftPlus = "+.";
		while ((pos = source.find(leftPlus)) != string::npos) {
			source.replace(pos, 2, "+");
		}

		const string rightMinus = ".-";
		while ((pos = source.find(rightMinus)) != string::npos) {
			source.replace(pos, 2, "-");
		}

		const string leftMinus = "-.";
		while ((pos = source.find(leftMinus)) != string::npos) {
			source.replace(pos, 2, "-");
		}

		const string rightAsta = ".*";
		while ((pos = source.find(rightAsta)) != string::npos) {
			source.replace(pos, 2, "*");
		}

		const string leftAsta = "*.";
		while ((pos = source.find(leftAsta)) != string::npos) {
			source.replace(pos, 2, "*");
		}

		const string rightSlash = "./";
		while ((pos = source.find(rightSlash)) != string::npos) {
			source.replace(pos, 2, "/");
		}

		const string leftSlash = "/.";
		while ((pos = source.find(leftSlash)) != string::npos) {
			source.replace(pos, 2, "/");
		}


		return source;
	}

	static string myCheckData(string dotForm) {
		if (dotForm.size() > 25) {
			return "dotForm must contain between 1 and 25 characters, inclusive.";
		}

		dotForm = removeDot(dotForm);

		size_t pos = string::npos;
		if ((pos = dotForm.find('.')) != string::npos) {
			stringstream ss;
			ss << "dotForm is not in dot notation, check character " << pos+1 << ".";
			return ss.str();
		}


		return "";
	}


	static void test() {
		if (ProblemWriting::myCheckData("3+5") == "") {
			cerr << "0.ok\n";
		}
		if (ProblemWriting::myCheckData("9..+.5...*....3") == "") {
			cerr << "1.ok\n";
		}
		if (ProblemWriting::myCheckData("5.3+4") == "dotForm is not in dot notation, check character 2.") {
			cerr << "2.ok\n";
		}
		if (ProblemWriting::myCheckData("9*9*9*9*9*9*9*9*9*9*9*9*9*9") == "dotForm must contain between 1 and 25 characters, inclusive.") {
			cerr << "3.ok\n";
		}
		if (ProblemWriting::myCheckData("3.........../...........4") == "") {
			cerr << "4.ok\n";
		}
	}
};




int main() {
	ProblemWriting::test();
}

