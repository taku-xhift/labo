
#include "FunctionTest.h"


float Test::getFloating()
{
	giveParameter(this->floating);

	return this->floating;
}




void giveParameter(float &x)
{
	x = 4.0f;
}

