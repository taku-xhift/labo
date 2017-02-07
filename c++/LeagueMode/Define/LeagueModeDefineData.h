/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 19:40:57
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 19:40:57
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODEDEFINEDATA_H_INCLUDED
#define LEAGUEMODEDEFINEDATA_H_INCLUDED


typedef enum {
	TEAMLIST_ARSENAL,
	TEAMLIST_ASTONVILLA,
	TEAMLIST_BIRMINGHAMCITY,
	TEAMLIST_BLACKBURNROVERS,
	TEAMLIST_BOLTONWANDERERS,
	TEAMLIST_BURNLEYFC,
	TEAMLIST_CHERCY,
	TEAMLIST_EVERTON,
	TEAMLIST_FULHAM,
	TEAMLIST_HULLCITY,
	TEAMLIST_LIVERPOOLFC,
	TEAMLIST_MANCHESTERCITY,
	TEAMLIST_MANCHESTERUNITED,
	TEAMLIST_MAX,
} TeamList;


static const char* dataBaseFileName = "game_para.csv";      //!< チームデータが入っているファイル
static const char* dataBaseResultFileName = "result.txt";   //!< いろいろな結果を書き出すファイル
static const char* resultFileName = "result";               //!< 試合結果を書き出すファイル
static const char* arsenal = "アーセナル";
static const char* astonVilla = "アストン ヴィラ";
static const char* birminghamCity = "バーミンガム シティ";
static const char* blackburnRovers = "ブラックバーン ローヴァーズ";
static const char* boltonWanderers = "ボルトン ワンダラーズ";
static const char* burnleyFC = "バーンリー";
static const char* chercy = "チェルシー";
static const char* everton = "エヴァートン";
static const char* fulham = "フラム";
static const char* hullCity = "ハル シティ";
static const char* liverpoolFC = "リヴァプールFC";
static const char* manchesterCity = "マンチェスター シティ";
static const char* manchesterUnited = "マンチェスター ユナイテッド";
//static const int   teamNumber = 31;                       //!< １チームの人数
#define teamNumber 35
/*
#define dataBaseFileName  "game_para.csv"
#define resultFileName "result"
#define manchesterUnited "マンチェスター ユナイテッド"
#define chercy "チェルシー"
*/
#endif

