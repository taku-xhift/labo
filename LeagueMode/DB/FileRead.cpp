/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 18:41:12
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 18:41:12
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <malloc.h>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/DB/fileRead.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/UtilityFunction.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Storage.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"


//-----------------------------------------------------
//  define
//-----------------------------------------------------
namespace {
	std::string dataFileName = "game_para.csv";     //!< データベースとして使うファイルの名前
	const int teamNameDataNumber = 0;               //!< チームネームが入っている番号
	const int entryNumberDataNumber = 4;            //!< 選手の管理番号が入っている番号
	const int playerNameDataNumber = 5;             //!< 選手の管理番号が入っている番号
	const int offenceDataNumber = 25;               //!< オフェンスのデータが入っている番号
	const int defenceDataNumber = 26;               //!< ディフェンスのデータが入っている番号
}




/**----------------------------------------------------
 * @brief ファイルからチームの名前を頼りに選手データを読み込む
 * @note    これは本来 Perl で行われるべき処理のはずだが、
 *              先行して cpp にて作成。
 *              perl が追いついたらそちらに置換されるべき。
 * @param[in]   teamName_           探すチーム名
 * @param[out]  reciprocateData_    データ格納を行う場所。
 *                                      これは C と perl のデータのやり取りを行うためのデータ。
 *---------------------------------------------------*/
void readFile_TeamDataInformation(const char* teamName_, ReciprocateData* reciprocateData_)
{
	assert(reciprocateData_);

	std::ifstream ifs(dataFileName.c_str());
	std::string fileData;

	// ファイルが読み込めたかチェックを行う
	assert(ifs.good());

	// データの確保
	std::vector<std::vector<std::string> > playerDataContainer;
	while (std::getline(ifs, fileData)) {
		std::vector<std::string> dataName = LeagueMode::splitString(fileData);
		//boost::algorithm::split(dataName, fileData, boost::is_any_of(","));
		// 名前が指定されたものと一致したときのみデータを確保
		if (dataName[teamNameDataNumber] == teamName_) {
			playerDataContainer.push_back(dataName);
		}
	}

	// 配列オーバーを起こさないかチェック。
	// reciprocateData_ にはあらかじめメモリが確保されている。
	// ここで動的にサイズを確保してもローカルオブジェクトと診断され、
	// 関数を出る頃には消えてしまう…
	if (playerDataContainer.size() > team_playerNumber) {
		// チーム予定数を超えてしまいました。このまま進むと配列オーバーが起きます
		assert(0);
	}

	// 読み取ったデータを保存
	reciprocateData_->num = playerDataContainer.size();
	reciprocateData_->type = DATATYPE_STRUCT;

	TeamData teamData;
	teamData.playerNumber = playerDataContainer.size();

	strcpy(teamData.name, teamName_);
	std::istringstream is;
	for (unsigned int i = 0; i < teamData.playerNumber; ++i) {
		LeagueMode::clearStream(is);
		strcpy(teamData.players[i].name, playerDataContainer.at(i).at(playerNameDataNumber).c_str());
		is.str(playerDataContainer.at(i).at(entryNumberDataNumber));
		is >> teamData.players[i].entryNumber;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(offenceDataNumber));
		is >> teamData.players[i].offence;
		LeagueMode::clearStream(is);
		is.str(playerDataContainer.at(i).at(defenceDataNumber));
		is >> teamData.players[i].defence;
	}

	ReciprocateData* temp = storage_TeamData(teamData, key_TeamData);

	memmove(reciprocateData_, temp, sizeof(ReciprocateData));

	free(temp);


/*
	reciprocateData_->value = (void**)calloc(playerDataContainer.size() , sizeof(PlayerData));
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
		reciprocateData_->value[i] = (void*)&array[i];
	}
*/
	//reciprocateData_->address = reinterpret_cast<unsigned int>(array);
}



