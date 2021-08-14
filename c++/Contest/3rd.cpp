


#include <iostream>


const int n = 4;
const int array[n] = {1, 2, 4, 7};
const int k = 13;

bool DFS(int i, int sum) {
	if (i == n) {
		return sum == k;
	}

	if (DFS(i+1, sum)) {
		return true;
	}

	if (DFS(i+1, sum + array[i])) {
		return true;
	}

	return false;
}


int main() {

	if (DFS(0, 0)) {
		std::cerr << "YES => " << k << "\n";
	} else {
		std::cerr << "No\n";
	}
}


