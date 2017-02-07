/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 18:41:12
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 18:41:12
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <boost/algorithm/string.hpp>
#include "../LeagueModeDefineData.h"
#include "../ReciprocateData.h"
#include "../ReciprocateDataForCpp.hpp"
#include "fileRead.hpp"
#include "../PlayerDataForCpp.hpp"
#include "../UtilityFunction.hpp"
#include "../LeagueModeDefineData.h"
#include "../MemoryLeakCheck.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	std::string dataFileName = "game_para.csv";     //!< データベースとして使うファイルの名前
	const int teamNameDataNumber = 0;               //!< チームネームが入っている番号
	const int entryNumberDataNumber = 1;            //!< 選手の管理番号が入っている番号
	const int playerNameDataNumber = 2;             //!< 選手の管理番号が入っている番号
	const int offenceDataNumber = 3;               //!< オフェンスのデータが入っている番号
	const int defenceDataNumber = 4;               //!< ディフェンスのデータが入っている番号
}


void readFile_TeamInformation(const char* teamName_, ReciprocateData* reciprocateData_)
{
	assert(reciprocateData_);

	std::ifstream ifs(dataFileName.c_str());
	std::string fileData;

	// ファイルが読み込めたかチェックを行う
	assert(ifs.good());

	// データの確保
	std::vector<std::vector<std::string> > playerDataContainer;
	while (std::getline(ifs, fileData)) {
		std::vector<std::string> dataName;
		boost::algorithm::split(dataName, fileData, boost::is_any_of(","));
		// 名前が指定されたものと一致したときのみデータを確保
		if (dataName[teamNameDataNumber] == teamName_) {
			playerDataContainer.push_back(dataName);
		}
	}

	// 配列オーバーを起こさないかチェック。
	// reciprocateData_ にはあらかじめメモリが確保されている。
	// ここで動的にサイズを確保してもローカルオブジェクトと診断され、
	// 関数を出る頃には消えてしまう…
	if (playerDataContainer.size() > teamNumber) {
		// チーム予定数を超えてしまいました。このまま進むと配列オーバーが起きます
		assert(0);
	}

	// 読み取ったデータを保存
	reciprocateData_->num = playerDataContainer.size();
	reciprocateData_->type = DATATYPE_PLAYERDATA;
	reciprocateData_->data = (void**)calloc(playerDataContainer.size() , sizeof(PlayerData));
	PlayerData* array = (PlayerData*)calloc(playerDataContainer.size() , sizeof(PlayerData));

	std::istringstream is;
	for (unsigned int i = 0; i < playerDataContainer.size(); ++i) {
		LeagueMode::clearStream(is);
		strcpy(array[i].name, playerDataContainer.at(i).at(playerNameDataNumber).c_str());
		is.str(playerDataContainer.at(i).at(entryNumberDataNumber));
		is >> array[i].entryNumber;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(offenceDataNumber));
		is >> array[i].offence;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(defenceDataNumber));
		is >> array[i].defence;
	}

	for (unsigned int i = 0; i < playerDataContainer.size(); ++i) {
		reciprocateData_->data[i] = (void*)&array[i];
	}

	reciprocateData_->address = reinterpret_cast<unsigned int>(array);
}



