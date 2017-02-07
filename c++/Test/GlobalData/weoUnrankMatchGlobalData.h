/**
 * @file  UnrankMatchGlobalData.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.06.22 16:29:15
 *
 * @version 0.01, Shishido Takuya, 2011.06.22 16:29:15
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef UNRANKMATCHGLOBALDATA_HPP_INCLUDED
#define UNRANKMATCHGLOBALDATA_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "weoTypeList.h"
#include "weoDataHolder.h"
#include "weoGlobalDataClassBase.h"
#include "weoDLLModefied.h"


//! \brief TypeList の定義
typedef pm_mode::task::GenScatterHierarchy <
	pm_mode::task::MakeTypelist<
	// コメントには下の enum で定義する名前情報を入れると良いかも
		int       //!< 
	>::Result,
	pm_mode::DataHolder> UnrankMatchGlobalDataTypeList;


//! \brief 管理したいデータの種類
enum UnrankMatchGlobalDataMember {
	UNRANKMATCHMEMBER_ID,
	UNRANKMATCHMEMBER_MAX,
};



//! \brief 一般的なデータ(ユーザプロフィール等)をグローバルに保存する
//! \note   呼び出せるメンバ関数は GlobalDataClassBase と同じ。
//! \note   機能的にはクラス定義とまったく同じ
WE_MODE_DLL_EXPORT typedef
	pm_mode::GlobalDataClassBase<UnrankMatchGlobalDataTypeList, UNRANKMATCHMEMBER_MAX>
		UnrankMatchGlobalData;       //!< グローバルデータの型名



#endif

