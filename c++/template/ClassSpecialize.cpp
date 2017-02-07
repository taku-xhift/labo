


#include <iostream>
#include <string>
#include <map>


template<typename Type>
struct Test;

template<>
struct Test<std::string> {
	std::string string_;
} String;


template<>
struct Test<std::map<std::string, Test> > {
	std::map<std::string, Test> list_;
} Object;


int main() {
	
}


