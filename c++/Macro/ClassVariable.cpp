


#include <iostream>

class Test {
public:
	static const int result = 1;
};

int main() {

#if Test::result
	std::cout << Test::result << std::endl;
#endif


	return 0;
}

