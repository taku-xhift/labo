

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>


using namespace std;


char list[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class CCipher {
public:
	static string decode(string cipherText, int shift) {
		vector<int> accessList(cipherText.begin(), cipherText.end());
		for (int i = 0; i < accessList.size(); ++i) {
			accessList.at(i) = (accessList.at(i) -65 + (26 - shift))%26;
		}
		string ret;

		for (int i = 0; i < accessList.size(); ++i) {
			ret += list[accessList.at(i)];
		}

		return ret;
	}


	static void test() {
		if (decode("VQREQFGT", 2) == "TOPCODER") {
			cout << "1. ok\n";
		}
		if (decode("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10) == "QRSTUVWXYZABCDEFGHIJKLMNOP") {
			cout << "2. ok\n";
		}
		if (decode("ZWBGLZ", 25) == "AXCHMA") {
			cout << "3. ok\n";
		}
		if (decode("DBNPCBQ", 1) == "CAMOBAP") {
			cout << "4. ok\n";
		}
		if (decode("LIPPSASVPH", 4) == "HELLOWORLD") {
			cout << "5. ok\n";
		}
	}
};




int main() {
	CCipher::test();
	//CCipher::decode("A", 1);
}


