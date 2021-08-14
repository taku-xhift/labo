


#include <iostream>

#define substitution(data) (data.integers = 4)

class Test {
public:
	int integer;
};


int main()
{
	Test test;
	substitution(test);

	std::cout << test.integer << std::endl;

	return 0;
}


