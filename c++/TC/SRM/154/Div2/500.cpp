


#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


const char* Small = "abcdfghijklmnopqrstuvwxyzabcdefghijklmnoparstuvwxyz";
const char* Large = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* Number = "01234567890123456789";


class SuperRot {
public:
	static string decoder(string message) {
		string ret;
		for (int i = 0; i < message.size(); ++i) {
			if (48 <= message[i] && message[i] <= 57) {
				ret.append(1, Number[message[i] - 48 + 5]);
			} else if (65 <= message[i] && message[i] <= 90) {
				ret.append(1, Large[(message[i] - 65 + 13)]);
			} else if (97 <= message[i] && message[i] <= 122) {
				ret.append(1, Small[(message[i] - 97 + 13)]);
			} else if (message[i] == ' ') {
				ret.append(1, ' ');
			}
		}

		return ret;
	}


	static void test() {
		if (decoder("Uryyb 28") == "Hello 73") {
			cerr << "0.ok\n";
		}
		if (decoder("GbcPbqre") == "TopCoder") {
			cerr << "1.ok\n";
		}
		if (decoder("") == "") {
			cerr << "2.ok\n";
		}
		if (decoder("5678901234") == "0123456789") {
			cerr << "3.ok\n";
		}
		if (decoder("NnOoPpQqRr AaBbCcDdEe") == "AaBbCcDdEe NnOoPpQqRr") {
			cerr << "4.ok\n";
		}
		if (decoder("Gvzr vf 54 71 CZ ba Whyl 4gu bs gur lrne 7558 NQ") == "Time is 09 26 PM on July 9th of the year 2003 AD") {
			cerr << "5.ok\n";
		}
		if (decoder("Gur dhvpx oebja sbk whzcf bire n ynml qbt") == "The quick brown fox jumps over a lazy dog") {
			cerr << "6.ok\n";
		}
	}
};





int main() {
	SuperRot::test();
}

