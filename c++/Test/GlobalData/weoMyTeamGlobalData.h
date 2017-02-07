/**
 * @file  weoMyTeamGlobalData.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.22 13:23:53
 *
 * @version 0.01, Shishido Takuya, 2011.04.22 13:23:53
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef WEOMYTEAMGLOBALDATA_HPP_INCLUDED
#define WEOMYTEAMGLOBALDATA_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include "weoTypeList.h"
#include "weoDataHolder.h"
#include "weoGlobalDataClassBase.h"
#include "weoDLLModefied.h"


//! \brief TypeList の定義
typedef pm_mode::task::GenScatterHierarchy <
	pm_mode::task::MakeTypelist<
	// コメントには下の enum で定義する名前情報を入れると良いかも
		int
	>::Result,
	pm_mode::DataHolder> MyTeamGlobalDataTypeList;


//! \brief リーグで管理したいデータの種類
enum MyTeamGlobalDataMember {
	MYTEAMMEMBER_ID,
	MYTEAMMEMBER_MAX,
};



//! \brief 一般的なデータ(ユーザプロフィール等)をグローバルに保存する
//! \note   呼び出せるメンバ関数は GlobalDataClassBase と同じ。
//! \note   機能的にはクラス定義とまったく同じ
WE_MODE_DLL_EXPORT typedef
	pm_mode::GlobalDataClassBase<MyTeamGlobalDataTypeList, MYTEAMMEMBER_MAX>
		MyTeamGlobalData;       //!< グローバルデータの型名



#endif

