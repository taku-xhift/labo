


#include <iostream>
//#include <boost/preprocessor/stringize.hpp>
//#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/seq.hpp>


#define COMMONMEMBERSIZE 1
#define LEAGUEMEMBERSIZE 4
#define UNRANKMATCHMEMBERSIZE 7
#define MYTEAMMEMBERSIZE 11


#define GLOBALDATA_MEMBERSIZE_SEQ (COMMONMEMBERSIZE)(LEAGUEMEMBERSIZE)(UNRANKMATCHMEMBERSIZE)(MYTEAMMEMBERSIZE)


////////////////////////////////////////////////////////////////////////
#define GEN_GD_UPLOAD_MODE_OBJECT_STR(_, objectID, modeID)\
	template<>\
	void upload<static_cast<GlobalDataMember>(modeID), objectID>() throw();

#define GEN_GD_UPLOAD_MODE_OBJECT(r, modeID, sequence)\
	BOOST_PP_REPEAT_FROM_TO(0, BOOST_PP_SEQ_ELEM(modeID, sequence), GEN_GD_UPLOAD_MODE_OBJECT_STR, modeID)


#define GEN_GD_FUNCTION_DECLARATION(sequence)\
	BOOST_PP_REPEAT_FROM_TO(0, BOOST_PP_SEQ_SIZE(sequence), GEN_GD_UPLOAD_MODE_OBJECT, sequence)


GEN_GD_FUNCTION_DECLARATION(GLOBALDATA_MEMBERSIZE_SEQ)
////////////////////////////////////////////////////////////////////////



#define COMMON_GLOBALDATA\
	(pm_mode::GAMEOPTION_SETTINGS,    GAMEOPTION_SETTINGS,          true),\
	(pm_mode::EXOPTION_SETTINGS,      EXOPTION_SETTINGS,            true),\
	(pm_mode::USER_PROFILE,           USER_PROFILE,                 true),\
	(pm_mode::CmnCallbackUniform,     UNIFORMDATA,                  true),\
	(pm_mode::KeyConfigOption,        KEY_CONFIG,                   true),\
	(pm_mode::UserInfoData,           USER_INFO,                    true),\
	(pm_mode::MyTeamPlayerUpdateData, MY_TEAM_PLAYER_UPDATE_DATA,   true),\
	)









//! \brief TypeList の定義
typedef pm_mode::task::GenScatterHierarchy <
	pm_mode::task::MakeTypelist<
	// コメントには下の enum で定義する名前情報を入れると良いかも
		pm_mode::GAMEOPTION_SETTINGS,
		pm_mode::EXOPTION_SETTINGS,
		pm_mode::USER_PROFILE,
		pm_mode::CmnCallbackUniform,
		pm_mode::KeyConfigOption,
		pm_mode::UserInfoData,
		pm_mode::MyTeamPlayerUpdateData
	>::Result,
	pm_mode::DataHolder> CommonGlobalDataTypeList;


//! \brief 管理したいデータの種類
enum CommonGlobalDataMember {
	COMMONMEMBER_GAMEOPTION_SETTINGS,			//!< 試合の設定
	COMMONMEMBER_EXOPTION_SETTINGS,				//!< 試合の中でもオプションの設定
	COMMONMEMBER_USER_PROFILE,					//!< ユーザプロフィール
	COMMONMEMBER_UNIFORMDATA,					//!< ユニフォームのロードファンクタ
	COMMONMEMBER_KEY_CONFIG,					//!< キーコンフィグデータ
	COMMONMEMBER_USER_INFO,						//!< ユーザーデータ
	COMMONMEMBER_MY_TEAM_PLAYER_UPDATE_DATA,	//!< マイチームの選手データ
	COMMONMEMBER_MAX,
};





//! \brief TypeList の定義
typedef pm_mode::task::GenScatterHierarchy <
	pm_mode::task::MakeTypelist<
	// コメントには下の enum で定義する名前情報を入れると良いかも
		pm_mode::GAMEOPTION_SETTINGS,
		pm_mode::EXOPTION_SETTINGS,
		pm_mode::USER_PROFILE,
		pm_mode::CmnCallbackUniform,
		pm_mode::KeyConfigOption,
		pm_mode::UserInfoData,
		pm_mode::MyTeamPlayerUpdateData
	>::Result,
	pm_mode::DataHolder> CommonGlobalDataTypeList;


//! \brief 管理したいデータの種類
enum CommonGlobalDataMember {
	COMMONMEMBER_GAMEOPTION_SETTINGS,			//!< 試合の設定
	COMMONMEMBER_EXOPTION_SETTINGS,				//!< 試合の中でもオプションの設定
	COMMONMEMBER_USER_PROFILE,					//!< ユーザプロフィール
	COMMONMEMBER_UNIFORMDATA,					//!< ユニフォームのロードファンクタ
	COMMONMEMBER_KEY_CONFIG,					//!< キーコンフィグデータ
	COMMONMEMBER_USER_INFO,						//!< ユーザーデータ
	COMMONMEMBER_MY_TEAM_PLAYER_UPDATE_DATA,	//!< マイチームの選手データ
	COMMONMEMBER_MAX,
};








enum GlobalDataMember {
	GLOBALMEMBER_COMMON,
	GLOBALMEMBER_LEAGUE,
	GLOBALMEMBER_MYTEAM,
	GLOBALMEMBER_UNRANKMATCH,
	GLOBALMEMBER_MAX,
};

enum CommonGlobalDataMember {
	COMMONMEMBER_GAMEOPTION_SETTINGS,			//!< 試合の設定
	COMMONMEMBER_EXOPTION_SETTINGS,				//!< 試合の中でもオプションの設定
	COMMONMEMBER_USER_PROFILE,					//!< ユーザプロフィール
	COMMONMEMBER_UNIFORMDATA,					//!< ユニフォームのロードファンクタ
	COMMONMEMBER_KEY_CONFIG,					//!< キーコンフィグデータ
	COMMONMEMBER_USER_INFO,						//!< ユーザーデータ
	COMMONMEMBER_MY_TEAM_PLAYER_UPDATE_DATA,	//!< マイチームの選手データ
	COMMONMEMBER_MAX,
};

enum LeagueGlobalDataMember {
	LEAGUEMEMBER_ID,					//!< ユーザの ID
	LEAGUEMEMBER_USERINFO,				//!< ユーザの個人情報
	LEAGUEMEMBER_MYTEAM,				//!< マイチーム情報
	LEAGUEMEMBER_LEAGUETOP,				//!< リーグトップ(対戦準備画面と共用）
	LEAGUEMEMBER_LEAGUESCHEDULE,		//!< リーグスケジュール
	LEAGUEMEMBER_LEAGUETOURNAMENTINFO,	//!< 大会情報
	LEAGUEMEMBER_LEAGUESEASONEND,		//!< シーズン結果
	LEAGUEMEMBER_MAX,
};


int main() {
	//print<static_cast<ENUM>(0)>();

	TEST();
}




template void GlobalData::upload<static_cast<GlobalDataMember>(0), 0>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(0), 1>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(0), 2>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(0), 3>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(0), 4>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(0), 5>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(0), 6>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 0>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 1>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 2>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 3>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 4>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 5>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(1), 6>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 0>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 1>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 2>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 3>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 4>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 5>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 6>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 7>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 8>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 9>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(2), 10>() throw();
 template void GlobalData::upload<static_cast<GlobalDataMember>(3), 0>() throw();











