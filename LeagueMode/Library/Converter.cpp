/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.16 15:10:07
 *
 * @version 0.01, Shishido Takuya, 2010.04.16 15:10:07
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Converter.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"


/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
DBError convertToDBError(const ReciprocateData* reciprocateData_, std::vector<int> node_ /*= std::vector<int>()*/)
{
	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {
		if (node_.empty()) {
			// 配列でない可能性がある。もしくは指定のミス
			assert(0);
		}
	}

	DBError data;

	strcpy(data.error, reinterpret_cast<const char*>(getKeyValue(*reciprocateData_, key_DBError, node_)));

	return data;
}



/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
PlayerData convertToPlayerData(const ReciprocateData* reciprocateData_, std::vector<int> node_ /* = std::vector<int>()*/)
{
	if (reciprocateData_->type != DATATYPE_STRUCT
		&& reciprocateData_->type != DATATYPE_STRUCTARRAY)
	{
		// 渡されているデータが不正なものの可能性がある
		assert(0);
	}

	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {
		if (node_.empty()) {
			// 配列でない可能性がある。もしくは指定のミス
			assert(0);
		}
	}

	PlayerData data;

	strcpy(data.name, reinterpret_cast<const char*>(getKeyValue(*reciprocateData_, key_PlayerData_player_name, node_)));
	data.entryNumber = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_PlayerData_player_id, node_));
	data.offence = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_PlayerData_offence, node_));
	data.defence = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_PlayerData_defence, node_));

	return data;
}



/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
TeamData convertToTeamData(const ReciprocateData* reciprocateData_, std::vector<int> node_ /* = std::vector<int>()*/)
{
	if (reciprocateData_->type != DATATYPE_STRUCT
		&& reciprocateData_->type != DATATYPE_STRUCTARRAY)
	{
		// 渡されているデータが不正なものの可能性がある
		assert(0);
	}

	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {
		if (node_.empty()) {
			// 配列でない可能性がある。もしくは指定のミス
			assert(0);
		}
	}

	TeamData data;

	strcpy(data.name, reinterpret_cast<const char*>(getKeyValue(*reciprocateData_, key_TeamData_name, node_)));
	data.teamID = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_TeamData_ID, node_));
	data.playerNumber = *reinterpret_cast<const int*>(getKeyValue(*reciprocateData_, key_TeamData_playerNumber, node_));

	for (int i = 0; i < data.playerNumber; ++i) {
		// 引数で指定された node_ は、TeamData 自身が配列だった場合のもの。
		// localNode を作るのは、struct TeamData ではさらにその先に PlayerData 型の配列が待っていて、
		// それを指定するためにループを回しながら localNode を毎回作成しなおしている
		std::vector<int> localNode(node_);
		localNode.push_back(i);

		data.players[i] = convertToPlayerData(reciprocateData_, localNode);
	}

	return data;
}




