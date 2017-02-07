


#include <iostream>
#include <vector>

#define TRUE 1
#define FALSE 0


template<typename Container, typename Functor>
void for_each(Container container_, Functor functor_) {
	for (typename Container::iterator ite = container_.begin(); ite != container_.end(); ++ite) {
		functor_(*ite);
	}
}

class Out {
public:
	static const int isNULL = FALSE;

	template<typename Type>
	void operator()(const Type& data_) {
		std::cout << "Out::" << data_ << std::endl;
	}
};


class NULLType {
public:
	static const int isNULL = TRUE;
};

template<typename Type1, typename Type2 = NULLType, typename Type3 = NULLType>
class Printer
{
public:
	void print(std::vector<int> container_) {
		for_each(container_, Type1());
	}
};



int main() {
	std::vector<int> container;

	for (int i = 0; i < 5; ++i) {
		container.push_back(i);
	}

	Printer<Out, Out, Out> printer;

	printer.print(container);

	return 0;
}


