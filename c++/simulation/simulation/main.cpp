/**
 * @file
 * @brief ƒƒCƒ“ƒ‚ƒWƒ…[ƒ‹
 *
 * @author Takuya Shishido
 * @date 2009.10.20 23:11:19
 *
 * @version 0.01, Shishido Takuya, 2009.10.20 23:11:19
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/



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


