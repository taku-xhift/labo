

#include <iostream>
#include <vector>
#include "Auto_CommandCreater_CommandSpec_GameResult.hpp"
#include "Auto_Converter_CommandSpec_GameResult.hpp"
#include "Auto_CommandSpec_GameResult.h"
#include "Auto_CommandSpec_GameResult_Define.h"
#include "Parse.hpp"

int main()
{
/*
	GameResultDirection direction = createGameResultDirection();

	setUserID_GameResultDirection(&direction, 16);

	ReciprocateData* command = commandCreate_GameResult(&direction);

	std::cout << *static_cast<const int*>(getKeyValue(*command, key_GameResult_userID)) << std::endl;
*/

	GameResult result = createGameResult();
	for (int i = 0; i < 2; ++i) {
		result.adversaryID[i] = i;
	}
	result.matchupNumber = "matchupNumber";
	result.time = 1000;
	result.teamID = 1500;
	result.oppositionTeamID = 1501;
	result.victory = "win!";
	result.firstHalfGoal = 2;
	result.secondHalfGoal = 5;
	result.firstHalfLoss = 1;
	result.secondHalfLoss = 4;
	result.homeAndAway = "home";
	result.isDefault = false;
	
	ReciprocateData* data = storage_GameResult(result, key_GameResult);

//	std::vector<int> node;
//	node.push_back(2);
//	std::cout << *static_cast<const int*>(getKeyValue(*data, key_GameResult_adversaryID, node)) << std::endl;

	GameResult converted = convertToGameResult(data);

	std::cout << converted.adversaryID[0] << std::endl;
	std::cout << converted.adversaryID[1] << std::endl;
	std::cout << converted.time << std::endl;
	std::cout << converted.teamID << std::endl;
	std::cout << converted.oppositionTeamID << std::endl;
	std::cout << converted.victory << std::endl;
	std::cout << converted.firstHalfGoal << std::endl;

	return 0;
}

