
#include <iostream>

struct UniqueNumber {
   template<class type_t>
   static unsigned int number() { static unsigned int n(count()); return n; };
private:
   static unsigned int count() { static unsigned int c(0); return c++; };
};

int main() {


	static const unsigned int zero = UniqueNumber::number<unsigned int>();
	static const unsigned int one = UniqueNumber::number<unsigned int>();

	std::cout << zero << std::endl;
	std::cout << one << std::endl;
}
