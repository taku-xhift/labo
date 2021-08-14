
#include <array>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


using namespace std;


#define ALL(arg) (arg.begin(), arg.end())
#define ALL2VEC(arg) std::vector<string>(arg.begin(), arg.end())


class FoxAndMp3Easy {
public:
	vector <string> playList(int n) {
		vector<string> mp3List(n);
		stringstream ss;

		for (int i = 1; i <= n; ++i) {
			ss << i << ".mp3";
			ss >> mp3List[i-1];

			ss.str("");
			ss.clear();
		}

		sort(mp3List.begin(), mp3List.end());

		if (mp3List.size() < 50) {
			return mp3List;
		}

		std::vector<string>::iterator last = mp3List.begin();
		std::advance(last, 50);

		return std::vector<string>(mp3List.begin(), last);
	}
};



int main() {
	FoxAndMp3Easy obj;
	int count = 0;
	{
		auto ret = obj.playList(3);
		cerr << count << " => ";
		for (auto& val : ret) {
			cerr << val << ", ";
		}
		cerr << "\n";
		++count;
	}
	{
		auto ret = obj.playList(10);
		cerr << count << " => ";
		for (auto& val : ret) {
			cerr << val << ", ";
		}
		cerr << "\n";
		++count;
	}
	{
		auto ret = obj.playList(16);
		cerr << count << " => ";
		for (auto& val : ret) {
			cerr << val << ", ";
		}
		cerr << "\n";
		++count;
	}
	{
		auto ret = obj.playList(32);
		cerr << count << " => ";
		for (auto& val : ret) {
			cerr << val << ", ";
		}
		cerr << "\n";
		++count;
	}
	{
		auto ret = obj.playList(109);
		cerr << count << " => ";
		for (auto& val : ret) {
			cerr << val << ", ";
		}
		cerr << "\n";
		++count;
	}
}


