/**
 * @file
 * @brief インターフェース部分。
 * @note    これを介してＣ側ではデータのやり取りを行う。
 *
 * @author Takuya Shishido
 * @date 2010.04.07 14:37:55
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 14:37:55
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Reciprocate.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Parse.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/Converter.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/DB/FileRead.hpp"
//#include "FileWrite.hpp"




/**-------------------------------------------------------------
 * @brief ID を頼りに ＤＢ からデータを取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       command_    コマンド（type=INT,value=playerNumber）
 * @param[out]      data_       データ格納先
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError findPlayerData_by_Number(ReciprocateData* command_, PlayerData* data_)
{
	DBError error;
	return error;
}


/**-------------------------------------------------------------
 * @brief 名前を頼りに ＤＢ からデータを取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       command_    コマンド（type=STRING,value=playerName）
 * @param[out]      data_       データ格納先
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError findPlayerData_by_PlayerName(ReciprocateData* command_, PlayerData* playerData_)
{
	DBError error;
	return error;
}



/**-------------------------------------------------------------
 * @brief チームの名前を頼りに、そのチームに所属する選手のデータ一覧を
 *              ＤＢ から取ってくる
 * @note    イメージ的にはこれの実装が perl とつながっていて、
 *              返り値はそれによって得られたデータ
 * @param[in]       command_    コマンド
 * @param[out]      data_       データ格納先
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
#define USE_PERL 0

DBError findPlayerDataByTeamName(ReciprocateData* command_, TeamData* teamData_)
{
	DBError error;

	// もらったデータが不正であればコマンド作成時に問題あり
	if (command_ == NULL || teamData_ == NULL) {
		strcpy(error.error, DBErr_CommandError);
		return error;
	}

	ReciprocateData* data = createReciprocateData();

	// TODO
	// 千田さんに書き換えをお願いしたい部分
	// data のアドレスにデータを作成してもらいたい
	{
		// チームの名前からとりに行く
		// 見つからなければコマンド作成のエラー
		const char* teamName;
		try {
			teamName = reinterpret_cast<const char*>(getKeyValue(*command_, key_TeamData_name));
		} catch (ParseException) {
			assert(0);
			strcpy(error.error, DBErr_CommandError);
			return error;
		}

		readFile_TeamDataInformation(teamName, data);
	}

#if USE_PERL
	// error を探しにいくが、見つからなければＤＢのエラー
	try {
		strcpy(error.error, reinterpret_cast<const char*>(getKeyValue(*data, key_DBError)));
	} catch (ParseException) {
		strcpy(error.error, DBErr_DBError);
		return error;
	}
#else
	strcpy(error.error, DBErr_NoError);
#endif

	// 問題が無ければデータの格納
	if (strcmp(error.error, DBErr_NoError) == 0) {
#if USE_PERL
		error = convertToDBError(data);
#endif
		const ReciprocateData* temp = reinterpret_cast<const ReciprocateData*>(getKeyValue(*data, key_TeamData));
		*teamData_ = convertToTeamData(temp);
	} else {
		// 問題はあるようだが、想定外のもののよう
		assert(0);
	}

	releaseReciprocateData(data);

	return error;
}


/**-------------------------------------------------------------
 * @brief 試合結果を perl に渡す
 * @note    イメージ的にはこれの実装が perl とつながっている。
 * @param[in]       command_    コマンド（type=string,value=teamName）
 * @return          ＤＢエラーの内容
 *------------------------------------------------------------*/
DBError sendGameResult(ReciprocateData* command_)
{
	assert(command_);
	//writeFile_GameResult(userID_, gameResult_);
	DBError error;
	return error;
}



