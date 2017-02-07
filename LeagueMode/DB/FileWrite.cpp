/**
 * @file
 * @brief ファイルに書き込む処理。本来は perl が行う仕事
 *
 * @author Takuya Shishido
 * @date   2010.04.07 16:07:26
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 16:07:26
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/DB/FileWrite.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Define/LeagueModeDefineData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/GameResultForCpp.hpp"


/**-------------------------------------------------------------
 * @brief 試合の結果をファイルに書き出し。
 * @param[in]   userID_     試合を行ったユーザのＩＤ
 * @param[in]   gameResult  試合結果
 *-------------------------------------------------------------*/
void writeFile_GameResult(int userID_, const GameResult* gameResult_)
{
	// 書き出しモジュール作成
	std::ofstream fileout(dataBaseResultFileName, std::ios::app);

	// 開けなかった場合は終了
	if(fileout.fail()) {
		std::cout << dataBaseResultFileName << "cannot open." << std::endl;
		assert(0);
	}

	// 出力
	fileout << "userID = " << userID_ << std::endl;
	fileout << "GameResult = " << (*gameResult_) << std::endl;

	// ファイルを閉じる
	fileout.close();
}



