


#include <iostream>

namespace {
	const char* const sample = "sample";
}

int main() {
	sample = "test";

	std::cerr << sample << std::endl;
}


