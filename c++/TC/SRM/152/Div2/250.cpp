


#include <iostream>
#include <set>

using namespace std;


set<double> list;


class FixedPointTheorem {
public:


	static double cycleRange(double R) {
		//culc(R, 0.25, 201000);
		double x = .25;

		for (int i = 0; i < 200000; ++i) {
			x = R * x * (1-x);
		}

		for (int i = 0; i < 1000; ++i) {
			x = R * x * (1-x);
			list.insert(x);
		}


		double min = *list.begin();
		double max = *(--list.end());
		list.clear();

		return max - min;
	}
};



int main() {
	cout << "0. => " << (FixedPointTheorem::cycleRange(0.1) == 0.0) << "\n";
	cout << "1. => " << (FixedPointTheorem::cycleRange(3.05) == 0.14754098360655865) << "\n";
	cout << "2. => " << (FixedPointTheorem::cycleRange(3.4499) == 0.4175631735867292) << "\n";
	cout << "3. => " << (FixedPointTheorem::cycleRange(3.55) == 0.5325704489850351) << "\n";
	cout << "4. => " << (FixedPointTheorem::cycleRange(3.565) == 0.5454276003030636) << "\n";
	cout << "5. => " << (FixedPointTheorem::cycleRange(3.5689) == 0.5489996297493569) << "\n";
	cout << "6. => " << (FixedPointTheorem::cycleRange(3.00005) == 0.004713996108955176) << "\n";
}


