


#include <iostream>

template<typename T, unsigned int i>
class Template {
public:
	typedef T Type;
	static const int value = i;
};


template<typename T, unsigned int i>
class Lapper {
public:
	typedef Template<T, i> ResultType;

	typename ResultType::Type get() {
		return ResultType::value;
	}
};


//typedef Template<1> One;


int main() {
	Lapper<int, 3> lapper;
	std::cout << lapper.get() << std::endl;
}


