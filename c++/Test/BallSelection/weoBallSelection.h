/**
 * @file  BallSelection.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.06.08 18:06:08
 *
 * @version 0.01, Shishido Takuya, 2011.06.08 18:06:08
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_BALLSELECTION_HPP_INCLUDED
#define PM_MODE_BALLSELECTION_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------

#define weBool int


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////////


#define DEFAULT_BALL_ID 8
#define BALL_TYPE_DLC_START 21
#define DLC_BALL_MAX 0

//! ボール使用条件定義
typedef enum {
	BALL_LOCATION_NORMAL = 0,	//!< 0:汎用
	BALL_LOCATION_MAN_U = 1,	//!< 1:マンU専用
	BALL_LOCATION_SNOW = 2,	//!< 2:天候・雪用
	BALL_LOCATION_FRANCE_LEAGUE_DIV_1_NOMAL = 3,	//!< 3:フランス リーグ・アン(本戦)
	BALL_LOCATION_CL_NOMAL = 4,	//!< 4:UEFAチャンピオンズリーグ(本戦)
	BALL_LOCATION_CL_WINNER = 5,	//!< 5:UEFAチャンピオンズリーグ(優勝チーム用)
	BALL_LOCATION_COPA_LIBERTADORES_NOMAL = 6,	//!< 6:コパ・リベルタドーレス(本戦)
	BALL_LOCATION_CL_EXHIBITION = 7,	//!< 7:UEFAチャンピオンズリーグ(エキジビション用)
	BALL_LOCATION_ALL = 8,	//!< 8:
} BALL_LOCATION;


/////////////////////////////////////////////////////////////////////


typedef enum {
	MNBALL_TYPE_000,	// Classic 
	MNBALL_TYPE_001,	// Plain 
	MNBALL_TYPE_002,	// WE-PES 2002 
	MNBALL_TYPE_003,	// WE-PES 2003 
	MNBALL_TYPE_004,	// WE-PES 2007 
	MNBALL_TYPE_005,	// WE-PES 2008 
	MNBALL_TYPE_009,	// WE-PES 2009 Claw 
	MNBALL_TYPE_011,	// WE-PES 2010 
	MNBALL_TYPE_012,	// WE-PES 2011 
	MNBALL_TYPE_155,	// F50 Top X-ite 
	MNBALL_TYPE_156,	// adiPure 2010 
	MNBALL_TYPE_411,	// Total 90 Tracer 
	MNBALL_TYPE_408,	// Total 90 Tracer Hi-Vis 
	MNBALL_TYPE_507,	// POWERCAT 1.10 STATEMENT 
	MNBALL_TYPE_510,	// KING XL 
	MNBALL_TYPE_602,	// Neo Pro Football 
	MNBALL_TYPE_143,	// UEFA CHAMPIONS LEAGUE FINALE MADRID 
	MNBALL_TYPE_144,	// UEFA CHAMPIONS LEAGUE FINALE 10 
	MNBALL_TYPE_145,	// UEFA CHAMPIONS LEAGUE POWERORANGE 
	MNBALL_TYPE_409,	// Total 90 ASCENTE Libertadores 
	MNBALL_TYPE_508,	// Ligue 1 Official Ball 
	MNBALL_TYPE_MAX, //max
} MNBallTypeID;

#define MNBALL_TYPE_RANDOM MNBALL_TYPE_MAX
#define MNBALL_TYPE_DEFAULT MNBALL_TYPE_012


/////////////////////////////////////////////////////////////////////


typedef enum {
	MAKER_WEP,
	MAKER_ADIDAS,
	MAKER_NIKE,
	MAKER_PUMA,
	MAKER_UMBRO,
	MAKER_MAX,
} BallMakerID;


/********************************************************************
 * @brief ボール情報
 * @note    オリジナルのデータは DB から取得する
 * @note    http://wepsrv04.konami/wedatman/we_online/teamlist.php
 *******************************************************************/
typedef struct _ModeBallInformation {
	const char*     name_;          //!< 名前
	int             uniqueBallID_;  //!< ボール毎の固有 ID
	BallMakerID     makerID_;       //!< ボールメーカー。本隊との調整用
	int             dummy_;         //!< 本隊との調整用
	int             condition_;     //!< ボール使用条件。シフト演算で管理される
} ModeBallInformation;



/********************************************************************
 * @brief 使用できるボールリストの検索パラメータ
 *******************************************************************/
typedef struct {
// in (検索用)

	BALL_LOCATION   location_;                      //!< ボールの条件

// out (検索結果)

	int             validSize_;                     //!< ballList_ の中の有効数
	MNBallTypeID    ballList_[MNBALL_TYPE_MAX];     //!< ボールのID。getBallDataByID と組み合わせて使用

} BallSearchCondition;




/********************************************************************
 * @brief ボール情報を取得する
 * @param[in]   ballID      取得したいボール情報
 *******************************************************************/
const ModeBallInformation* const getBallDataByID(MNBallTypeID ballID);



/********************************************************************
 * @brief 条件を与えて使えるボールリストを取得する
 * @param[in, out]  searchCondition     条件と、その結果の出力先
 *******************************************************************/
void getBallDataListByCondition(BallSearchCondition* const searchCondition);



#ifdef __cplusplus
}
#endif

#endif

