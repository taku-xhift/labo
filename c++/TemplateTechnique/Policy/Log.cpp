


#include <iostream>


template<
typename Type = double
, typename Type2 = int>
class A {
public:
	Type value;
};


int main() {
	A<> a;
}

