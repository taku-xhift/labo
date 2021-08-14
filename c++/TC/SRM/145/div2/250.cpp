


#include <iostream>
#include <vector>

using namespace std;

class ImageDithering {
public:
	static int count(string dithered, vector<string> screen) {
		int ret = 0;

		for (int i = 0; i < screen.size(); ++i) {
			for (int j = 0; j < screen[i].size(); ++j) {
				// up
				if (i != 0 && dithered.find(screen[i-1][j], 0) != string::npos) {
					++ret;
					break;
				}
				// left
				if (j != 0 && dithered.find(screen[i][j-1], 0) != string::npos) {
					++ret;
					break;
				}
				// down
				if (i != screen.size()-1 && dithered.find(screen[i+1][j], 0) != string::npos) {
					++ret;
					break;
				}
				// right
				if (j != screen[i].size()-1 && dithered.find(screen[i][j+1], 0) != string::npos) {
					++ret;
					break;
				}
			}
		}

		return ret;
	}
};


string sample[] = {
	"AAAAAAAA",
	"ABWBWBWA",
	"AWBWBWBA",
	"ABWBWBWA",
	"AWBWBWBA",
	"AAAAAAAA"
};
#define numberof(arg) (arg/arg[0])

int main() {
	vector<string> arg;
	//for (int i = 0; i < numberof(sample); ++i) {
	for (int i = 0; i < 6; ++i) {
		arg.push_back(sample[i]);
	}
	cout << ImageDithering::count("BW", arg) << endl;
}


