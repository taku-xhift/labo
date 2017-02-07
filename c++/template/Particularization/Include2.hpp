
#ifndef INCLUDE2_HPP
#define INCLUDE2_HPP

#include <iostream>
#include "Include.hpp"


class Include2 {
public:
	const char* include2;

	Include2() : include2("include2") {}
};


template<>
void convertPerlTo(const Include2& type_) {
	std::cout << type_.include2 << std::endl;
}

#endif  // #ifndef INCLUDE2_HPP


