/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.22 13:19:35
 *
 * @version 0.01, Shishido Takuya, 2010.04.22 13:19:35
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef COMMANDCREATER_FOUNDTEAM_HPP_INCLUDED
#define COMMANDCREATER_FOUNDTEAM_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/ReciprocateData.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	USELIST_USE,
	USELIST_UNUSE,
} UseList;


/**
 * @brief チーム情報をＤＢから取得するための検索指示
 *          
 * @note    パラメータのうち、片方だけが指定されていればそれで検索する
 *              同時に成り立たないものの優先度はメンバの上から順。
 * @author  Takuya Shishido
 * @date    2010.04.22 13:19:35
 * @version 0.01, Shishido Takuya, 2010.04.22 13:19:35
 */
typedef struct
{
	int         teamID;         //!< 検索：チームのユニークＩＤ。指定しないなら INT_MAX にすること
	const char* teamName;       //!< 検索：チームの名前

	UseList     useList[2];     //!< 使用未使用のフラグリスト
} FoundTeamDataDirection;




/**----------------------------------------------------
 * @brief 初期化されたコマンドの取得関数
 * @note    UseList の管理も行うので、直接代入せず、このモジュールを通すこと
 * @return      初期化されたコマンド
 *---------------------------------------------------*/
FoundTeamDataDirection getFoundTeamDataDirection();


/**----------------------------------------------------
 * @brief パラメータセットモジュール
 * @note    UseList の管理も行うので、直接代入せず、このモジュールを通すこと
 * @param[in]   teamID_     チームID
 *---------------------------------------------------*/
void setTeamID_FoundTeamDataDirection(FoundTeamDataDirection* command_, int teamID_);


/**----------------------------------------------------
 * @brief パラメータセットモジュール
 * @param[in]   teamName_   チーム名
 *---------------------------------------------------*/
void setTeanName_FoundTeamDataDirection(FoundTeamDataDirection* command_, const char* teamName_);


/**----------------------------------------------------
 * @brief コマンド作成関数
 * @note    取得したコマンドは自分で解放関数を使って解放すること
 * @param[in]   指示
 * @return      作成されたコマンド
 *---------------------------------------------------*/
ReciprocateData* commandCreate_FoundTeamData(FoundTeamDataDirection* direction_);



#ifdef __cplusplus
}
#endif

#endif  // COMMANDCREATER_FOUNDTEAM_HPP_INCLUDED

