

#include <array>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


#define ALL(arg) (arg.begin(), arg.end())
#define ALL2VEC(arg) std::vector<string>(arg.begin(), arg.end())



class FoxAndGame {
public:
	int countStars(vector <string> result) {
		int getCount = 0;
		for (int i = 0; i < result.size(); ++i) {
			for (int j = 0; j < result[i].size(); ++j) {
				if (result[i][j] == 'o') {
					++getCount;
				}
			}
		}

		return getCount;
	}
};



int main() {
	FoxAndGame obj;
	int count = 0;
	{
		array<string, 2> arg = {"ooo", "ooo"};
		if (obj.countStars(ALL2VEC(arg)) == 6) {
			cerr << count << ".ok\n";
		}
		++count;
	}
	{
		array<string, 3> arg = {"ooo",
			"oo-",
			"o--"};
		if (obj.countStars(ALL2VEC(arg)) == 6) {
			cerr << count << ".ok\n";
		}
		++count;
	}
	{
		array<string, 5> arg = {"ooo",
			"---",
			"oo-",
			"---",
			"o--"};
		if (obj.countStars(ALL2VEC(arg)) == 6) {
			cerr << count << ".ok\n";
		}
		++count;
	}
	{
		array<string, 5> arg = {"o--",
			"o--",
			"o--",
			"ooo",
			"---"};
		if (obj.countStars(ALL2VEC(arg)) == 6) {
			cerr << count << ".ok\n";
		}
		++count;
	}
	{
		array<string, 8> arg = {"---",
			"o--",
			"oo-",
			"ooo",
			"ooo",
			"oo-",
			"o--",
			"---"};
		if (obj.countStars(ALL2VEC(arg)) == 12) {
			cerr << count << ".ok\n";
		}
		++count;
	}
	{
		array<string, 6> arg = {"---",
			"---",
			"---",
			"---",
			"---",
			"---"};
		if (obj.countStars(ALL2VEC(arg)) == 0) {
			cerr << count << ".ok\n";
		}
		++count;
	}
	{
		array<string, 1> arg = {"oo-"};
		if (obj.countStars(ALL2VEC(arg)) == 2) {
			cerr << count << ".ok\n";
		}
		++count;
	}
}


