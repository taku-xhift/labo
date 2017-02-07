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


#ifdef __cplusplus
#include <iostream>
#endif


/**
 * @brief データの型情報一覧
 */
typedef enum
{
	DATATYPE_INVALID,           /**< 無効なデータ型 */
	DATATYPE_STRING,            /**< 文字列型 */
	DATATYPE_INT,               /**< 整数型 */
	DATATYPE_INTARRAY,          /**< 整数配列型 */
	DATATYPE_FLOAT,             /**< 浮動小数点型 */
	DATATYPE_FLOATARRAY,        /**< 浮動小数点配列型 */
	DATATYPE_STRUCT,            /**< 構造体型 */
	DATATYPE_STRUCTARRAY,       /**< 構造体配列型 */
	DATATYPE_MAX,               /**< 型情報最大値 */
} ReciprocateDataType;



/**
 * @brief perl と c でデータをやり取りする際の
 *          データを一塊にしたもの。c++ なら DBAccessForCpp.hpp がお勧め。
 * @note    C++ で使う際には ForCpp がおすすめ。出力をサポートしてくれる。
 *              ただし、new は禁止。
 * @author  Takuya Shishido
 * @date    2010.04.02 15:12:15
 * @version 0.01, Shishido Takuya, 2010.04.02 15:12:15
 */
typedef struct
{
	ReciprocateDataType     type;       /**< データの型 */
	int                     num;        /**< 自分の要素数。DATATYPE_INTなら1が入っている。構造体ならメンバの数、配列ならその要素数が入っている。 */
	const char*             key;        /**< データの内容を示すキー */
	void**                  value;      /**< データ本体。配列になっている。要素数は num で判断。free で忘れずに開放すること */

#ifdef __cplusplus
	/**
	 * @brief C++ 用に new の禁止
	 * @note    ただし、 malloc は禁止できない
	 *          createReciprocateData() も内部は malloc なのでそこはしょうがない。
	 */
	void* operator new(std::size_t size);
#endif

} ReciprocateData;



#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief ReciprocateData 型のメモリ取得関数
 * @note    中身は calloc() しているだけ。
 *              releaseReciprocateData() とのセットにしている
 * @return  確保されたメモリのアドレス
 *---------------------------------------------------*/
ReciprocateData* createReciprocateData()
{
	return (ReciprocateData*)(calloc(1, sizeof(ReciprocateData)));
}


/**----------------------------------------------------
 * @brief ReciprocateData 型の解放関数
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

