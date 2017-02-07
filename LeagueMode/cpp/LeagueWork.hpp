/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 14:07:08
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 14:07:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_LEAGUEWORK_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEWORK_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

namespace LeagueMode {

/**
 * @brief 雑多なデータを管理するためのクラス
 *          現状何も保存の予定が無いため、空っぽ。
 *          増えれば逆にファイル分割の可能性も。
 * @author  Takuya Shishido
 * @date    2010.04.02 14:07:08
 * @version 0.01, Shishido Takuya, 2010.04.02 14:07:08
 */
class LeagueWork
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	LeagueWork();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~LeagueWork();


	/**----------------------------------------------------
	 * @brief  初期化作業
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief  update. メインでループして欲しい作業
	 *---------------------------------------------------*/
	void update();


private:

};    // class LeagueWork
}    // namespace LeagueMode

#endif

