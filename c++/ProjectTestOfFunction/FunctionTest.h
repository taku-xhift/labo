
#ifndef FunctionTest_hpp
#define FunctionTest_hpp

#include <iostream>

#include "Types.hpp"

class Test
{
public:

	struct TestInTest
	{
		int rational;

		TestInTest()
		{
			this->rational = 3;
		}
	};

	Test()
	{
		floating = 2.0f;
	}

	float getFloating();


	float floating;
};


void giveParameter(float &x);

#endif

