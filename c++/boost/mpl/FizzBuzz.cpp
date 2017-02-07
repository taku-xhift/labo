


#include <iostream>
#include <boost/mpl/string.hpp>


template<int N>
struct Num {
	static const int value = N;
};


int main() {
	std::cerr << Num<0>::value << std::endl;
}


