

#include <iostream>



#include <vector>
#include <string>

#include <sstream>
#include <cstdlib>
#include <bitset>


using namespace std;


class BinaryCode {
public:

	static vector<string> decode(string message) {
		vector<vector<int> > retInt(2);
		retInt[0].resize(message.size()+1);
		retInt[1].resize(message.size()+1);
		retInt[0][0] = 0;
		retInt[1][0] = 1;

		vector<int> messageInt(message.size()+1);
		{
			stringstream ss;
			for (int i = 0; i < message.size(); ++i) {
				ss << message[i];
				ss >> messageInt[i];
				ss.str("");
				ss.clear();
			}
			messageInt[message.size()] = 0;
		}

		vector<vector<int> >::iterator ite = retInt.begin();
		vector<vector<int> >::iterator end = retInt.end();
		std::bitset<2> invalids;
		invalids[0] = false;
		invalids[1] = false;
		int count = 0;

		for (; ite != end; ++ite, ++count) {
			int pre2 = 0;
			int pre1 = (*ite)[0];
			int temp = 0;

			for (int i = 1; i < message.size(); ++i) {
				temp = messageInt[i-1] - pre2 - pre1;

				if (temp == 0) {
					(*ite)[i] = 0;
				} else if (temp == 1) {
					(*ite)[i] = 1;
				} else {
					invalids[count] = true;
				}

				pre2 = pre1;
				pre1 = (*ite)[i];
			}

			// check
			for (int i = 0; i < message.size(); ++i) {
				if (i == 0) {
					if (messageInt[i] != (*ite)[i] + (*ite)[i+1]) {
						invalids[count] = true;
						break;
					}
				} else if (i == message.size() - 1) {
					if (messageInt[i] != (*ite)[i-1] + (*ite)[i]) {
						invalids[count] = true;
						break;
					}
				} else {
					if (messageInt[i] != (*ite)[i-1] + (*ite)[i] + (*ite)[i+1]) {
						invalids[count] = true;
						break;
					}
				}
			}
		}


		vector<string> ret(2);
		for (int i = 0; i < ret.size(); ++i) {
			if (invalids[i]) {
				ret[i] = "NONE";
				continue;
			}

			stringstream ss;
			for (int j = 0; j < message.size(); ++j) {
				ss << retInt[i][j];
			}

			ret[i] = ss.str();
		}

		return ret;
	}
};





int main(int argc, char* argv[]) {
	vector<string> ret = BinaryCode::decode(argv[1]);

	std::cout << ret[0] << std::endl;
	std::cout << ret[1] << std::endl;
}

