#include <iostream>
#include <boost/smart_ptr.hpp>


int main()
{
	int zero = 0;
	int one = 1;

	//int zeroHolder[] = { zero,zero,zero,zero };
	//int* zeroHolder = new int[4];
	boost::shared_array<int> zeroHolder(new int[4]);

	for (int i = 0; i < 4; ++i) {
		zeroHolder[i] = zero;
	}

	zeroHolder[1] = one;

	for (int i = 0; i < 4; ++i) {
		std::cout << zeroHolder[i] << std::endl;
	}

	//delete [] zeroHolder;

	return 0;
}
