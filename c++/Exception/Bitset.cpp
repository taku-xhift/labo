


#include <iostream>
#include <bitset>
#include <stdexcept>
#include <typeinfo>


#define getSkill(ParamList) ParamList, true


int main() {
	std::bitset<2> bit;

	try {
		bit.set(getSkill(3, true));
		std::cerr << "succeed" << std::endl;
	} catch (std::out_of_range& e) {
		std::cerr << "out_of_range" << std::endl;
		std::cerr << e.what() << std::endl;
	} catch (std::invalid_argument& e) {
		std::cerr << "invalid" << std::endl;
		std::cerr << e.what() << std::endl;
	} catch (std::length_error& e) {
		std::cerr << "length" << std::endl;
	} catch (std::bad_exception& e) {
		std::cerr << "bad_exception" << std::endl;
	} catch (std::logic_error& e) {
		std::cerr << "logic_error" << std::endl;
	} catch (std::runtime_error& e) {
		std::cerr << "runtime_error" << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cerr << typeid((3, true)).name() << std::endl;
}


