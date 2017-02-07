

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


class Random
{
public:
	// コンストラクタ
	Random()
	{
		srand( static_cast<unsigned int>( time(NULL) ) );
	}

	// 関数オブジェクト
	unsigned int operator()(unsigned int max)
	{
		double tmp = static_cast<double>( rand() ) / static_cast<double>( RAND_MAX );
		return static_cast<unsigned int>( tmp * max );
	}
};

unsigned int random(unsigned int max) {
	srand( static_cast<unsigned int>( time(NULL) ) );
	double tmp = static_cast<double>( rand() ) / static_cast<double>( RAND_MAX );
	return static_cast<unsigned int>( tmp * max );
}

int main() {
	std::vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	std::random_shuffle(container.begin(), container.end(), random);

	std::for_each(container.begin(), container.end(), std::cout << boost::lambda::_1 << "\n");
}

