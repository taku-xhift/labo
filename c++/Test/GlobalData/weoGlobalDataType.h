/**
 * @file  GlobalDataType.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.06.24 12:48:27
 *
 * @version 0.01, Shishido Takuya, 2011.06.24 12:48:27
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef GLOBALDATATYPE_HPP_INCLUDED
#define GLOBALDATATYPE_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include "weoTypeList.h"
#include "weoGlobalDataHolder.h"
#include "weoDLLModefied.h"

// グローバルデータの型
#include "weoLeagueGlobalData.h"
#include "weoCommonGlobalData.h"
#include "weoMyTeamGlobalData.h"
#include "weoUnrankMatchGlobalData.h"


//! \brief TypeList の定義
//WE_MODE_DLL_EXPORT typedef pm_mode::task::GenScatterHierarchy<
//	pm_mode::task::MakeTypelist<
//	// コメントには下の enum で定義する名前情報を入れると良いかも
//		CommonGlobalData,       //!< モードに依存しないデータ
//		LeagueGlobalData,       //!< リーグに関するデータ
//		MyTeamGlobalData,
//		UnrankMatchGlobalData
//	>::Result,
//	pm_mode::GlobalDataHolder> GlobalDataTypeList;

class WE_MODE_DLL_EXPORT GlobalDataTypeList
	: public pm_mode::task::GenScatterHierarchy<
	pm_mode::task::MakeTypelist<
	// コメントには下の enum で定義する名前情報を入れると良いかも
		CommonGlobalData,       //!< モードに依存しないデータ
		LeagueGlobalData,       //!< リーグに関するデータ
		MyTeamGlobalData,
		UnrankMatchGlobalData
	>::Result,
	pm_mode::GlobalDataHolder>
{
};


//! \brief グローバルに管理したいデータの種類
//! \note   単位はモードごとレベル
enum GlobalDataMember {
	GLOBALMEMBER_COMMON,
	GLOBALMEMBER_LEAGUE,
	GLOBALMEMBER_MYTEAM,
	GLOBALMEMBER_UNRANKMATCH,
	GLOBALMEMBER_MAX,
};



#endif

