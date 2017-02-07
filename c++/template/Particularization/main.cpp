

#include "Include1.hpp"
#include "Include2.hpp"

int main()
{
	Include1 include1;
	Include2 include2;

	convertPerlTo<Include1>(include1);
	convertPerlTo<Include2>(include2);

	return 0;
}

