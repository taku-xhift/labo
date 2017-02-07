/**
 * @file
 * @brief データベースへのアクセスをイメージした関数群
 *
 * @author Takuya Shishido
 * @date 2010.04.02 15:56:16
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 15:56:16
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef DBACCESS_H_INCLUDED
#define DBACCESS_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <assert.h>


typedef enum
{
	DATATYPE_INT,
	DATATYPE_FLOAT,
	DATATYPE_PLAYERDATA,
	DATATYPE_INVALID,
} ReciprocateDataType;



/**
 * @brief perl と c でデータをやり取りする際の
 *          データを一塊にしたもの。c++ なら DBAccessForCpp.hpp がお勧め。
 * @note    C++ で使う際には TeamForCpp がおすすめ。出力をサポートしてくれる。

 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct
{
	unsigned int    address;            //!< data を作る際に作られるテンポラリデータのアドレス。
	                                    //      data が必要なくなった際に忘れずに free で開放すること。
	ReciprocateDataType     type;       //!< データの型
	int                     num;        //!< データ内に入っている有効データの数
	void**                  data;       //!< データ本体。配列になっている。要素数は num で判断。free で忘れずに開放すること
} ReciprocateData;



#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief dataSet 型の解放関数
 * @note    address、data に関しては free をする。
 *              type は DATATYPE_INVALID にて初期化。
 *              num は INT_MAX にて初期化を行います。
 * @param[out]  dataSet_    データを解放したいもの
 *---------------------------------------------------*/
void releaseReciprocateData(ReciprocateData* reciprocateData_);



#ifdef __cplusplus
}
#endif


#endif

