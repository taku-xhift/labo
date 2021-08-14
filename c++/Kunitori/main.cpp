
#include <iostream>
#include "StreamObject.hpp"
#include "GameManager.hpp"
#include "Utility.hpp"

int main()
{
	while (NewMode::GameManager::getInstance().run() != 0) {
	}

	//Utility::readInitFile(NewMode::GameManager::getInstance());

	so::out << "End Game." << so::endl;

	return 0;
}


