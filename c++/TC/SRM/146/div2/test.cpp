


#include <iostream>


int SumSigma(int start, int end) {
	return (start + end) * ((end - start + 1)/2);
}


int main() {
	std::cout << SumSigma(1, 10) << std::endl;
}


