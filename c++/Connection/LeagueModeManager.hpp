/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <vector>


//-----------------------------------------------------
//  define
//-----------------------------------------------------
#define USE_STRING 1


namespace LeagueMode {

/**
 * @brief リーグを管理するためのマネージャー
 *          
 * @author  Takuya Shishido
 * @date    2010.04.02 10:44:24
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 */
class LeagueModeManager
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *----------------------------------------------------*/
	LeagueModeManager();


	/**----------------------------------------------------
	 * @brief  destructor
	 *----------------------------------------------------*/
	~LeagueModeManager();


	/**----------------------------------------------------
	 * @brief   実行関数
	 * @return  現在の状態の名前
	 *----------------------------------------------------*/
#if USE_STRING
	std::string& run();
#else
	const char* run();
#endif


	std::vector<int> getContainer();


	/**----------------------------------------------------
	 * @brief   データ取得
	 *----------------------------------------------------*/
	static LeagueModeManager& getInstance() {
		static LeagueModeManager uniqueInstance;
		return uniqueInstance;
	}

private:

#if USE_STRING
	std::string name;   //!< 名前
#else
	const char* name;   //!< 名前
#endif


	std::vector<int>  intContainer;

};    // class LeagueModeManager

//LeagueMode::LeagueModeManager LeagueMode::LeagueModeManager::uniqueInstance;


}    // namespace LeagueMode

#endif

