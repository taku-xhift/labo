


#include <iostream>
#include "MMDModel.hpp"
const char* mikuFile = "./Model/miku.pmd";

int main() {
	mmd::Model model(mikuFile);
	std::cerr << model;
}

