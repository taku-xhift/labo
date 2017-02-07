/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.01.29 15:47:14
 *
 * @version 0.01, Shishido Takuya, 2010.01.29 15:47:14
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef NEWMODE_AI_HPP_INCLUDED
#define NEWMODE_AI_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "StreamObject.hpp"
#include "GameData.hpp"
#include <list>

namespace NewMode {

/**
 * @brief ＡＩの挙動を全て管理するクラス。判断なども全て行う。
 *          管理されるのはチーム。
 *
 * @author  Takuya Shishido
 * @date    2010.01.29 15:47:14
 * @version 0.01, Shishido Takuya, 2010.01.29 15:47:14
 */
class AI
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	AI();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~AI();

private:

	std::list<UserData> userData;      // 判断を行うためのデータを所持

};    // class AI
}    // namespace NewMode

#endif

