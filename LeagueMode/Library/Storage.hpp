
#ifndef STORAGE_HPP_INCLUDED
#define STORAGE_HPP_INCLUDED

//-----------------------------------------------------
//  includ
//-----------------------------------------------------
#include <vector>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/PlayerData.h"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamData.h"


/**----------------------------------------------------
 * @brief データ格納が済んだデータに error 情報を付加する
 * @note        チェック用。本来Ｃ側から error をつけて格納することはないはず…
 * @param[in]   data_   一通りのデータの格納が済んだデータ
 * @return      data_ に error をつけたデータ
 *---------------------------------------------------*/
ReciprocateData* bindDataOnWithError(ReciprocateData* data_, const char* errorWord_);



/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_Int(int data_, const char* key_);


/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_String(const char* data_, const char* key_);


/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_Error(const char* data_, const char* key_);


/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_PlayerData(const PlayerData& data_, const char* key_);


/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_PlayerDataArray(const std::vector<PlayerData>& data_, const char* key_);


/**----------------------------------------------------
 * @brief データ格納
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_TeamData(const TeamData& data_, const char* key_);


#endif

