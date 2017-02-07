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
	TEAMLIST_PORTSMOUTH,
	TEAMLIST_STOKECITY,
	TEAMLIST_SUNDERLAND,
	TEAMLIST_TOTTENHAMHOTSPUR,
	TEAMLIST_WESTHAMUNITED,
	TEAMLIST_WIGANATHLETIC,
	TEAMLIST_WOLVERHAMPTONWANDERERS,
	TEAMLIST_INVALID,           //!< MAX 以外に何かに使う場合に
	TEAMLIST_MAX,
} TeamList;


static const char* gameEnd = "GameEnd";                     //!< ゲーム脱出用
static const char* nothing = "nothing";                     //!< 無効な文字列であることを示すもの
static const char* dataBaseFileName = "game_para.csv";      //!< チームデータが入っているファイル
static const char* dataBaseResultFileName = "result.txt";   //!< いろいろな結果を書き出すファイル
static const char* resultFileName = "result";               //!< 試合結果を書き出すファイル

// プレミアリーグの登録チーム
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
static const char* portsmouth = "ポーツマス";
static const char* stokeCity = "ストーク シティ";
static const char* sunderland = "サンダーランド";
static const char* tottenhamHotspur  = "トッテナム ホットスパー";
static const char* westHamUnited = "ウェストハム ユナイテッド";
static const char* wiganAthletic = "ウィガン アスレチック";
static const char* wolverhamptonWanderers = "ウォルヴァーハンプトン W.";
//static const int   teamNumber = 31;                       //!< １チームの人数


// キーに関する Define
static const char* key_DBError = "Error";
static const char* key_PlayerData = "playerdata";
static const char* key_PlayerData_player_id = "playerid";
static const char* key_PlayerData_player_name = "playername";
static const char* key_PlayerData_offence = "offence";
static const char* key_PlayerData_defence = "defence";
static const char* key_TeamData = "TeamData";
static const char* key_TeamData_name = "teamname";
static const char* key_TeamData_ID = "teamid";
static const char* key_TeamData_playerNumber = "teamPlayerNumber";
static const char* key_TeamData_players = "teamplayers";


// エラー文字列に対する Define
static const char* DBErr_NoError = "errnoerror";
static const char* DBErr_NotFound = "errnotfound";
static const char* DBErr_CommandError = "errcomand";
static const char* DBErr_InvalidData = "errinvaliddata";
static const char* DBErr_DBError = "errdberror";
static const char* DBErr_CriticalError = "criticalerror";




static const int home = 0;
static const int away = 1;
static const int homeAwayMax = 2;

#define team_playerNumber 35

#endif

