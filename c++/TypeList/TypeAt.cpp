


#include <iostream>
#include <string>
#include <loki/Typelist.h>
#include <loki/TypelistMacros.h>
#include <loki/TypeManip.h>
#include <loki/NullType.h>

typedef LOKI_TYPELIST_3(int, float, std::string) TL;
//typedef LOKI_TYPELIST_1(::Loki::NullType) NullList;
typedef ::Loki::NullType NullList;

int main() {
	//::Loki::TL::TypeAt<TL, 1>::Result value = 4;
	//std::cout << value << std::endl;
	std::cerr << typeid(::Loki::TL::TypeAt<TL, 2>::Result).name() << std::endl;

	std::cerr << ::Loki::TL::Length<NullList>::value << std::endl;
}


