
#include <iostream>
#include "StreamObject.hpp"
#include "GameManager.hpp"
#include "Utility.hpp"

int main()
{
//	while (GameManager::getInstance().run() != 0) {
//	}

	Utility::readInitFile(GameManager::getInstance());

	so::out << "End Game." << so::endl;

	return 0;
}


