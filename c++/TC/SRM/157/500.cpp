

#include <array>


#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


#define ALL(arg) arg.begin(), arg.end()
#define SSClear(ss) { ss.str(""); ss.clear(); }


class Salary {
public:
	static int ParseTime(const string& time) {
		int ret = 0;
		int temp = 0;
		stringstream ss;

		ss << time.substr(0, 2);
		ss >> temp;
		SSClear(ss);
		ret += temp * 60 * 60;

		ss << time.substr(3, 2);
		ss >> temp;
		SSClear(ss);
		ret += temp * 60;

		ss << time.substr(6, 2);
		ss >> temp;
		SSClear(ss);
		ret += temp;

		return ret;
	}

	enum State {
		Night,
		Morning,
		Evening,
		None,
	};


	static int howMuch(vector <string> arrival, vector <string> departure, int wage) {
		//const double wageParSecond = wage/(60.0 * 60.0);
		const double wageParSecond = wage/3600.0;

		double ret = .0;
		vector<int> timeStampStart;
		vector<int> timeStampEnd;

		const int Oc06 = ParseTime("06:00:00");
		const int Oc18 = ParseTime("18:00:00");
		const int Oc24 = ParseTime("23:59:59");

		for (int i = 0; i < arrival.size(); ++i) {
			//timeStampStart(ParseTime(arrival[i]));
			//timeStampEnd(ParseTime(departure[i]));
			const int arrive = ParseTime(arrival[i]);
			const int depart = ParseTime(departure[i]);

			int now = arrive;

			bool isAlreadyArrive = (arrive < Oc06);

			// 6
			if (isAlreadyArrive) {
				if (now < depart) {
					if (depart < Oc06) {
						ret += (depart - now) * wageParSecond * 1.5;
						continue;
					} else {
						ret += (Oc06 - now) * wageParSecond * 1.5;
					}
				}
			}

			if (isAlreadyArrive) {
				now = Oc06;
			} else if (Oc06 < arrive && arrive < Oc18) {
				now = arrive;
				isAlreadyArrive = true;
			}

			// 18
			if (isAlreadyArrive) {
				if (depart < Oc18) {
					ret += (depart - now) * wageParSecond;
					continue;
				} else {
					ret += (Oc18 - now) * wageParSecond;
				}
			}


			if (isAlreadyArrive) {
				now = Oc18;
			} else if (Oc18 < arrive && arrive < Oc24) {
				now = arrive;
				isAlreadyArrive = true;
			}

			// 24
			if (depart < Oc24) {
				ret += (depart - now) * wageParSecond * 1.5;
				continue;
			} else {
				ret += (Oc24 - now) * wageParSecond * 1.5;
			}

			if (arrive < depart) {
				continue;
			}

			// 06
			ret += depart * wageParSecond * 1.5;
		}

		return static_cast<int>(ret);
	}


	static void test() {
		{
			array<string, 3> arg1 = {"08:00:00","13:00:00","19:27:32"};
			array<string, 3> arg2 = {"12:00:00","17:00:00","20:48:10"};
			if (howMuch(vector<string>(ALL(arg1)), vector<string>(ALL(arg2)), 1000) == 10015) {
				cerr << "0.ok\n";
			}
		}
		{
			array<string, 2> arg1 = {"01:05:47","16:48:12"};
			array<string, 2> arg2 = {"09:27:30","21:17:59"};
			if (howMuch(vector<string>(ALL(arg1)), vector<string>(ALL(arg2)), 2000) == 33920) {
				cerr << "1.ok\n";
			}
		}
		{
			array<string, 1> arg1 = {"00:00:00"};
			array<string, 1> arg2 = {"23:59:59"};
			if (howMuch(vector<string>(ALL(arg1)), vector<string>(ALL(arg2)), 10000) == 299995) {
				cerr << "2.ok\n";
			}
		}
		{
			array<string, 1> arg1 = {"10:00:00"};
			array<string, 1> arg2 = {"18:00:00"};
			if (howMuch(vector<string>(ALL(arg1)), vector<string>(ALL(arg2)), 10000) == 80000) {
				cerr << "3.ok\n";
			}
		}
		{
			array<string, 1> arg1 = {"22:19:46"};
			array<string, 1> arg2 = {"23:12:46"};
			if (howMuch(vector<string>(ALL(arg1)), vector<string>(ALL(arg2)), 5320) == 7049) {
				cerr << "4.ok\n";
			}
		}
		cerr << "System test\n";
		{
			array<string, 1> arg1 = {"12:00:00"};
			array<string, 1> arg2 = {"13:00:00"};
			if (howMuch(vector<string>(ALL(arg1)), vector<string>(ALL(arg2)), 8189) == 8189) {
				cerr << "4.ok\n";
			}
		}
	}
};



int main() {
	Salary::test();
}

