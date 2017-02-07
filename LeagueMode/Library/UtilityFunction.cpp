/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.04.02 19:35:16
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 19:35:16
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/UtilityFunction.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"

namespace LeagueMode {



/**----------------------------------------------------
 * @brief string を "," にて分割し、それをコンテナにして返す関数
 * @note    基本的に csv ファイルを読み込むのに使いましょう。
 *              使えるなら boost の split あたりを使ってください。
 *              boost を使えない環境に備えて作成したものなので。
 *              また、それに準拠しているので、"," は排除されています。
 * @param[in]   参考にする文字列
 * @return      , を基準に分割された文字列群
 *---------------------------------------------------*/
std::vector<std::string> splitString(const std::string& strings_)
{
	std::vector<std::string> container;
	unsigned int num = 0;
	std::string temp = strings_;

	while (true) {
		num = temp.find(",", 0);
		if (num == std::string::npos) {
			container.push_back(temp);
			return container;
		}
		container.push_back(temp.substr(0, num));

		temp.erase(0, num+1);
	}

	return container;
}


}    // namespace LeagueMode

