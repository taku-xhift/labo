#include <iostream>
#include <string>
#include <functional>
#include <boost/bind.hpp>



struct Functor  : std::unary_function< std::string, void >
{
	//typedef void result_type;

	result_type operator()(argument_type str) {
		std::cout << str << std::endl;
	}
};





int main()
{
	//boost::bind(Functor(), "Hello")();
	boost::bind(Functor(), "Hello")();

	return 0;
}

