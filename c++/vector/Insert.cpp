


#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> base;
	vector<int> other;

	for (int i = 0; i < 10; ++i) {
		base.push_back(i);
		other.push_back(i);
	}

	base.insert(base.end(), other.begin(), other.end());

	for (vector<int>::iterator ite = base.begin(); ite != base.end(); ++ite) {
		cout << *ite << endl;
	}
}


