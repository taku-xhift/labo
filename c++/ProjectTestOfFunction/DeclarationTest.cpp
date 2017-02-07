

#include "DeclarationTest.hpp"
//#include "FunctionTest.h"

Declaration::Declaration()
{
	this->testInTest = new Test::TestInTest();
}


Declaration::~Declaration()
{
	delete this->testInTest;
}

