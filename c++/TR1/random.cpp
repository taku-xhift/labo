

#include <random>
#include <iostream>


int main() {
	std::tr1::ranlux64_base_01 eng;
	std::tr1::normal_distribution<float> dist(1.5f, 2.0f);
	std::tr1::normal_distribution<float>::input_type engval = eng();
	std::tr1::normal_distribution<float>::result_type distVal = dist(eng);

	dist.reset();
	std::cerr << "a random value => " << dist(eng) << std::endl;
	dist.reset();
	std::cerr << "a random value => " << dist(eng) << std::endl;
	dist.reset();
	std::cerr << "a random value => " << dist(eng) << std::endl;
}


