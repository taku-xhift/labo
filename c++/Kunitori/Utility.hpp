/**
 * @file
 * @brief 便利メソッド所有モジュール
 *
 * @author Takuya Shishido
 * @date   2009.11.08 21:13:39
 *
 * @version 0.01, Shishido Takuya, 2009.11.08 21:13:39
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

namespace NewMode {
	class GameManager;
}


namespace Utility {
/**
 * @brief 初期化データ読み込み
 * @author  Takuya Shishido
 * @date    2009.11.08 21:13:39
 * @version 0.01, Shishido Takuya, 2009.11.08 21:13:39
 */
	void readInitFile(NewMode::GameManager& manager);



}   // namespace Utility

#endif

