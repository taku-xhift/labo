/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.05 11:02:05
 *
 * @version 0.01, Shishido Takuya, 2011.04.05 11:02:05
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_LEAGUEGLOBALDATA_HPP_INCLUDED
#define PM_MODE_LEAGUEGLOBALDATA_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "weoTypeList.h"
#include "weoDataHolder.h"
#include "weoGlobalDataClassBase.h"
#include "weoDLLModefied.h"

#include <string>
#include "weCommonType.h"


// ■ League に関するグローバルデータ
//
//  拡張方法
//      1. typedef の中身を増やす(データの型を決定している)
//      2. enum の中にアクセスする名前を登録する
//          以上で新規オブジェクトの追加は終了
//
//      例えば新規に SinglePlayGlobalData を作ろう、と思った場合には
//          1. このファイルをコピー
//          2. インクルードガード変更
//          3. typedef の型名に関する部分を修正(GlobalData の名前)
//          4. enum を変更
//          5. TypeList の型一覧を修正
//      だけでいい。



struct UserInfo
{
	friend void weoGlobalDataSave(::pm_mode::json::object& obj, const UserInfo& value) throw();
	friend void weoGlobalDataLoad(const ::pm_mode::json::object& obj, UserInfo& value) throw();

	UserInfo(int32_t integer = 0, const std::string& name = "")
		: integer_(integer)
		, name_(name)
	{
	}

	int32_t     integer_;
	std::string name_;
};



//! \brief TypeList の定義
typedef pm_mode::task::GenScatterHierarchy <
	pm_mode::task::MakeTypelist<
	// コメントには下の enum で定義する名前情報を入れると良いかも
		int,
		UserInfo
	>::Result,
	pm_mode::DataHolder> LeagueGlobalDataTypeList;


//! \brief リーグで管理したいデータの種類
enum LeagueGlobalDataMember {
	LEAGUEMEMBER_ID,
	LEAGUEMEMBER_USER_INFO,
	LEAGUEMEMBER_MAX,
};



//! \brief リーグデータをグローバルに保存しておくクラスの型定義
//! \note   呼び出せるメンバ関数は GlobalDataClassBase と同じ。
//! \note   機能的にはクラス定義とまったく同じ
//class LeagueGlobalData
//	: public GlobalDataClassBase<LeagueGlobalDataTypeList, LEAGUEMEMBER_MAX>
//{
//
//};
WE_MODE_DLL_EXPORT typedef
	pm_mode::GlobalDataClassBase<LeagueGlobalDataTypeList, LEAGUEMEMBER_MAX>
		LeagueGlobalData;       //!< グローバルデータの型名





#endif

