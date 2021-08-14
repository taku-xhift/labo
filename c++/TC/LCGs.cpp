


#include <iostream>
#include <vector>


double LCGs(int A, int B, int M, int seed) {
	return (A * seed + B) % M;
}



int main() {
	std::vector<double> randList;

	for (int i = 0; i < 100; ++i) {
		if (i == 0) {
			randList.push_back(LCGs(997, 1, 65536, 12345));
		} else {
			randList.push_back(LCGs(997, 1, 65536, *randList.rbegin()));
		}
	}

	double sum = .0;
	for (auto rand : randList) {
		std::cout << rand/65536 << " ";
		sum += rand;
	}
	std::cout << "\n";

	std::cout << "average => " << sum/100/65536 << std::endl;
}


