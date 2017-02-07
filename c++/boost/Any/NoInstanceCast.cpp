


#include <iostream>
#include <boost/any.hpp>


int main() {
	boost::any any;

	try {
		std::cout << boost::any_cast<int>(any) << std::endl;
	} catch (boost::bad_any_cast& e) {
		std::cout << e.what() << std::endl;
	}

}


