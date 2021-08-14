
#ifndef INCLUDE1_HPP
#define INCLUDE1_HPP

#include <iostream>
#include "Include.hpp"


class Include1 {
public:
	const char* include1;

	Include1() : include1("include1") {}
};


template<>
void convertPerlTo(const Include1& type_) {
	std::cout << type_.include1 << std::endl;
}


#endif  // INCLUDE1_HPP

