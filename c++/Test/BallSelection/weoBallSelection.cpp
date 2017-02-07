/**
 * @file  BallSelection.cpp
 * @brief
 * @note    bit 演算参考 http://www.cc.kyoto-su.ac.jp/~yamada/pB/bit.html
 *
 * @author Takuya Shishido
 * @date   2011.06.08 18:06:08
 *
 * @version 0.01, Shishido Takuya, 2011.06.08 18:06:08
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include "BallSelection.h"


namespace {


const ModeBallInformation ballData[] = {
{
	"\x43\x6c\x61\x73\x73\x69\x63",
	0,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//Classic
{
	"\x50\x6c\x61\x69\x6e",
	1,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//Plain
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x30\x32",
	2,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2002
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x30\x33",
	3,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2003
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x30\x37",
	4,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2007
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x30\x38",
	5,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2008
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x30\x39\x20\x43\x6c\x61\x77",
	9,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2009 Claw
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x31\x30",
	11,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2010
{
	"\x57\x45\x2d\x50\x45\x53\x20\x32\x30\x31\x31",
	12,
	MAKER_WEP,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//WE-PES 2011
{
	"\x46\x35\x30\x20\x54\x6f\x70\x20\x58\x2d\x69\x74\x65",
	155,
	MAKER_ADIDAS,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//F50 Top X-ite
{
	"\x61\x64\x69\x50\x75\x72\x65\x20\x32\x30\x31\x30",
	156,
	MAKER_ADIDAS,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//adiPure 2010
{
	"\x54\x6f\x74\x61\x6c\x20\x39\x30\x20\x54\x72\x61\x63\x65\x72",
	411,
	MAKER_NIKE,
	0,
	(1<<BALL_LOCATION_NORMAL)|(1<<BALL_LOCATION_MAN_U)
},	//Total 90 Tracer
{
	"\x54\x6f\x74\x61\x6c\x20\x39\x30\x20\x54\x72\x61\x63\x65\x72\x20\x48\x69\x2d\x56\x69\x73",
	408,
	MAKER_NIKE,
	0,
	(1<<BALL_LOCATION_NORMAL)|(1<<BALL_LOCATION_SNOW)
},	//Total 90 Tracer Hi-Vis
{
	"\x50\x4f\x57\x45\x52\x43\x41\x54\x20\x31\x2e\x31\x30\x20\x53\x54\x41\x54\x45\x4d\x45\x4e\x54",
	507,
	MAKER_PUMA,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//POWERCAT 1.10 STATEMENT
{
	"\x4b\x49\x4e\x47\x20\x58\x4c",
	510,
	MAKER_PUMA,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//KING XL
{
	"\x4e\x65\x6f\x20\x50\x72\x6f\x20\x46\x6f\x6f\x74\x62\x61\x6c\x6c",
	602,
	MAKER_UMBRO,
	0,
	(1<<BALL_LOCATION_NORMAL)
},	//Neo Pro Football
{
	"\x55\x45\x46\x41\x20\x43\x48\x41\x4d\x50\x49\x4f\x4e\x53\x20\x4c\x45\x41\x47\x55\x45\x20\x46\x49\x4e\x41\x4c\x45\x20\x4d\x41\x44\x52\x49\x44",
	143,
	MAKER_ADIDAS,
	0,
	(1<<BALL_LOCATION_CL_WINNER)
},	//UEFA CHAMPIONS LEAGUE FINALE MADRID
{
	"\x55\x45\x46\x41\x20\x43\x48\x41\x4d\x50\x49\x4f\x4e\x53\x20\x4c\x45\x41\x47\x55\x45\x20\x46\x49\x4e\x41\x4c\x45\x20\x31\x30",
	144,
	MAKER_ADIDAS,
	0,
	(1<<BALL_LOCATION_CL_NOMAL)|(1<<BALL_LOCATION_CL_EXHIBITION)
},	//UEFA CHAMPIONS LEAGUE FINALE 10
{
	"\x55\x45\x46\x41\x20\x43\x48\x41\x4d\x50\x49\x4f\x4e\x53\x20\x4c\x45\x41\x47\x55\x45\x20\x50\x4f\x57\x45\x52\x4f\x52\x41\x4e\x47\x45",
	145,
	MAKER_ADIDAS,
	0,
	(1<<BALL_LOCATION_CL_EXHIBITION)
},	//UEFA CHAMPIONS LEAGUE POWERORANGE
{
	"\x54\x6f\x74\x61\x6c\x20\x39\x30\x20\x41\x53\x43\x45\x4e\x54\x45\x20\x4c\x69\x62\x65\x72\x74\x61\x64\x6f\x72\x65\x73",
	409,
	MAKER_NIKE,
	0,
	(1<<BALL_LOCATION_COPA_LIBERTADORES_NOMAL)
},	//Total 90 ASCENTE Libertadores
{
	"\x4c\x69\x67\x75\x65\x20\x31\x20\x4f\x66\x66\x69\x63\x69\x61\x6c\x20\x42\x61\x6c\x6c",
	508,
	MAKER_PUMA,
	0,
	(1<<BALL_LOCATION_FRANCE_LEAGUE_DIV_1_NOMAL)
}	//Ligue 1 Official Ball
};



/********************************************************************
 * @brief 条件に一致するボールを検索する
 * @note    ファイルローカル
 * @param[in]   condition   条件
 * @return      条件に一致したファイルローカルのボールデータ
 *              見つからなければ NULL
 *******************************************************************/
const ModeBallInformation* const getBallDataByCondition(int condition) {
	for (int i = 0; i < MNBALL_TYPE_MAX; ++i) {
		if (ballData[i].condition_ == condition) {
			return &ballData[i];
		}
	}

	return NULL;
}



}   // namespace



/********************************************************************
 * @brief ボール情報を取得する
 * @param[in]   ballID      取得したいボール情報
 *******************************************************************/
const ModeBallInformation* const getBallDataByID(MNBallTypeID ballID) {
	if (ballID >= MNBALL_TYPE_MAX) { return NULL; }
	return &ballData[ballID];
}



/********************************************************************
 * @brief 条件を与えて使えるボールリストを取得する
 * @param[in, out]  searchCondition     条件と、その結果の出力先
 *******************************************************************/
void getBallDataListByCondition(BallSearchCondition* const searchCondition)
{
	if (searchCondition == NULL) { return; }

	int condition = (1 << searchCondition->location_);

	searchCondition->validSize_ = 0;
	for (unsigned int i = 0u; i < MNBALL_TYPE_MAX; ++i) {
		// 論理積で整理して比較
		if ((ballData[i].condition_ & condition) == condition) {
			searchCondition->ballList_[searchCondition->validSize_] = static_cast<MNBallTypeID>(i);
			++searchCondition->validSize_;
		}
	}
}


