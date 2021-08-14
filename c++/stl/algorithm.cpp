#include <iostream>
#include <vector>
#include <algorithm>

bool even(int x)
{
	return !(x%2);
}

int main()
{
	std::vector<int> v;
	
	for (int i = 0; i < 20; ++i) {
		if (i % 2) {
			v.push_back(1);
		} else {
			v.push_back(2);
		}
	}

	std::cout << "ƒV[ƒPƒ“ƒXF";

	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;

	int n;
	n = count(v.begin(), v.end(), 1);
	std::cout << n << "ŒÂ‚Å‚·(‚P‚Ì—v‘f)" << std::endl;

	n = count_if(v.begin(), v.end(), even);
	std::cout << n << "ŒÂ‚Å‚·(‚Q‚Ì—v‘f)" << std::endl;

	return 0;
}