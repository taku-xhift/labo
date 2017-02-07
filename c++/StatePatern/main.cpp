/*!
 * @file
 * @brief Main roop.
 *
 * @author Takuya Shishido
 * @date 2009-10-17
 *
 * @version 0.01, Shishido Takuya, 2009-10-17
 *      (c) 2009 Uehara seminar
*/

#include "StateManager.hpp"
#include "StateMachine.hpp"


int main()
{
	//StateManager manager;

	while (StateManager::getInstance()->run() != "error") {
	}

	std::cout << "Roop is out!!!" << std::endl;

	return 0;
}


