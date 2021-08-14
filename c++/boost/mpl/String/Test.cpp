


#include <boost/mpl/string.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <iostream>

typedef boost::mpl::string<'fizz'> Fizz;


template<int N>
struct Num {
	static const int value = N;
};

struct print {
	template<typename T>
	void operator()(T) const {
		std::cerr << T::value << std::endl;
	}
};


int main() {
	boost::mpl::for_each<boost::mpl::range_c<int, 0, 10> >(print());
}


