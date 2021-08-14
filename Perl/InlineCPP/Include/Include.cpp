
#include <iostream>
#include "Exception.hpp"
#include "Include.hpp"

//void sayHello()
void sayHello(const char* hello_) throw(std::exception)
{
	std::cout << checkStrings(hello_, false) << std::endl;
	//std::cout << "Hello" << std::endl;
}

//void sayWorld()
void sayWorld(const char* world_) throw(std::exception)
{
	std::cout << checkStrings(world_, false) << "!!" << std::endl;
	//std::cout << "World!!" << std::endl;
}
