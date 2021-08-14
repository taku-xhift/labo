

#include <iostream>
#include <typeinfo>

//using namespace std;

struct True
{
	int i;
};

struct False
{
	int i,j;
};

template<typename L, typename R>
struct IsBaseOf
{
	static True test(L*);
	static False test(...);
	static const bool result = sizeof(test(static_cast<R*>(NULL)))==sizeof(True);

	void out()
	{
		if (this->result == true) {
			std::cout << this->result << std::endl;
		}
	}
};

int main()
{
	std::cout << IsBaseOf<void, int>::result << std::endl;
	std::cout << IsBaseOf<int, double>::result << std::endl;

	IsBaseOf<void, int> base;
	base.out();

	return 0;
}
