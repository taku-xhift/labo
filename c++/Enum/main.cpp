

#include <iostream>


enum LeagueModeStep {
	first,
	second,
};

typedef enum {
	LeagueModeStep,
} MainStep;


void out(MainStep step_) {
	std::cout << step_ << std::endl;
}


int main()
{
	out(first);

	return 0;
}


