/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 19:35:16
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 19:35:16
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_UTILITYFUNCTION_HPP_INCLUDED
#define LEAGUEMODE_UTILITYFUNCTION_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <sstream>

namespace LeagueMode {


/**----------------------------------------------------
 * @brief  stringstream を初期化する関数
 * @param[in]   ss_     初期化するストリーム
 *---------------------------------------------------*/
template<typename Type>
void clearStream(Type& ss_)
{
	// バッファクリア
	ss_.str("");
	// ストリームの状態をクリアする。この行がないと意図通りに動作しない
	ss_.clear(std::stringstream::goodbit);
}


/**----------------------------------------------------
 * @brief  安全に delete をするための補助関数
 * @param[in]   data_   消したいデータ
 *---------------------------------------------------*/
template<typename Type>
void safeDelete(Type* data_)
{
	if (data_ != NULL) {
		delete data_;
		data_ = NULL;
	}
}


/**----------------------------------------------------
 * @brief string を "," にて分割し、それをコンテナにして返す関数
 * @note    基本的に csv ファイルを読み込むのに使いましょう。
 *              使えるなら boost の split あたりを使ってください。
 *              boost を使えない環境に備えて作成したものなので。
 *              また、それに準拠しているので、"," は排除されています。
 * @param[in]   参考にする文字列
 * @return      , を基準に分割された文字列群
 *---------------------------------------------------*/
std::vector<std::string> splitString(const std::string& strings_);


}    // namespace LeagueMode

#endif

