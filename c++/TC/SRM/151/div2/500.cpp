


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <iomanip>


using namespace std;



struct Day {
	int month_;
	int day_;

	Day(const string& day) {
		stringstream ss;

		const int slashPos = day.find_first_of('/', 0);

		ss.str("");
		ss.clear();
		ss << day.substr(0, slashPos);
		ss >> this->month_;

		ss.str("");
		ss.clear();
		ss << day.substr(slashPos + 1);
		ss >> this->day_;
	}

	bool operator< (const Day& other) const {
		if (this->month_ * 100 + this->day_ < other.month_ * 100 + other.day_) {
			return true;
		}

		return false;
	}
};



class Birthday {
public:
	static string getNext(string date, vector <string> birthdays) {
		multiset<Day> list;
		stringstream ss;
		string temp;

		for (int i = 0; i < birthdays.size(); ++i) {
			ss << birthdays[i];
			ss >> temp;
			list.insert(Day(temp));

			ss.str("");
			ss.clear();
		}

		Day find(date);
			list.insert(find);

		multiset<Day>::iterator ite = list.find(find);
		++ite;

		if (ite == list.end()) {
			ite = list.begin();
		}

		ss.str("");
		ss.clear();

		ss << setw(2) << setfill('0') << ite->month_ << "/" << setw(2) << setfill('0') << ite->day_;
		temp = ss.str();
		return temp;
	}

	static void test() {
		{
			vector<string> arg;
			arg.push_back("02/17 Wernie");
			arg.push_back("10/12 Stefan");
			if (getNext("06/17", arg) == "10/12") {
				cerr << "0.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("10/12 Stefan");
			if (getNext("06/17", arg) == "10/12") {
				cerr << "1.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("02/17 Wernie");
			arg.push_back("10/12 Stefan");
			if (getNext("02/17", arg) == "02/17") {
				cerr << "2.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("10/12 Stefan");
			if (getNext("12/24", arg) == "10/12") {
				cerr << "3.ok\n";
			}
		}
		{
			vector<string> arg;
			arg.push_back("02/17 Wernie");
			arg.push_back("10/12 Stefan");
			arg.push_back("02/17 MichaelJordan");
			arg.push_back("10/12 LucianoPavarotti");
			arg.push_back("05/18 WilhelmSteinitz");
			if (getNext("01/02", arg) == "02/17") {
				cerr << "4.ok\n";
			}
		}
		cerr << "selfcheck\n";

		{
			vector<string> arg;
			arg.push_back("02/01 Wernie");
			arg.push_back("10/02 Stefan");
			if (getNext("01/02", arg) == "02/01") {
				cerr << "5.ok\n";
			}
		}
	}
};



int main() {
	Birthday::test();
}

