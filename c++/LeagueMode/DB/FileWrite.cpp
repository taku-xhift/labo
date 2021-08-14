
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

#include "FileWrite.hpp"
#include "../LeagueModeDefineData.h"
#include "../GameResultForCpp.hpp"


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



