


#include <iostream>
#include <algorithm>


const int arrayNum = 1000;
int result = 1000;
int array[arrayNum];



bool binary_search(int x) {
	int l = 0;
	int r = arrayNum;

	while (r - l >= 1) {
		const int i = (l + r)/2;
		if (array[i] == x) {
			return true;
		} else if (array[i] < x) {
			l = i + 1;
		} else {
			r = i;
		}
	}

	return false;
}


void solve() {
	std::sort(array, array + arrayNum);

	bool f = false;

	for (int a= 0; a < arrayNum; ++a) {
		for (int b = 0; b < arrayNum; ++b) {
			for (int c = 0; c < arrayNum; ++c) {
				if (binary_search(result - array[a] - array[b] - array[c])) {
					f = true;
					break;
				}
			}
		}
	}

	if (f) {
		puts("Yes");
	} else {
		puts("No");
	}
}



int main() {
	for (int i = 0; i < arrayNum; ++i) {
		array[i] = rand();
	}

	solve();
}

