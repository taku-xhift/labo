#include <iostream>

using namespace std;

int main()
{
	for (int k = 0; k < 3; ++k) {
		for (int i = 3 - k; i > 0; --i) {
			for (int j = 3 - k; j > 0; --j) {
				cout << i << " " << j << " " << k << " " << endl;
			}
		}
	}

	return 0;
}