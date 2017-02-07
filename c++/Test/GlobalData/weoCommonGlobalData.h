/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.08 13:57:37
 *
 * @version 0.01, Shishido Takuya, 2011.04.08 13:57:37
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef WEO_COMMONGLOBALDATA_HPP_INCLUDED
#define WEO_COMMONGLOBALDATA_HPP_INCLUDED

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
	int
	>::Result,
	pm_mode::DataHolder> CommonGlobalDataTypeList;


//! \brief 管理したいデータの種類
enum CommonGlobalDataMember {
	COMMONMEMBER_ID,
	COMMONMEMBER_MAX,
};



//! \brief 一般的なデータ(ユーザプロフィール等)をグローバルに保存する
//! \note   呼び出せるメンバ関数は GlobalDataClassBase と同じ。
//! \note   機能的にはクラス定義とまったく同じ
WE_MODE_DLL_EXPORT typedef
	pm_mode::GlobalDataClassBase<CommonGlobalDataTypeList, COMMONMEMBER_MAX>
		CommonGlobalData;       //!< グローバルデータの型名



#endif

