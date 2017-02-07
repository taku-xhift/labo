/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.22 12:52:03
 *
 * @version 0.01, Shishido Takuya, 2010.04.22 12:52:03
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef DBERROR_H_INCLUDED
#define DBERROR_H_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------


typedef enum {
	DB_ERRORTYPE_NOERROR,           //!< エラーなし
	DB_ERRORTYPE_NOTFOUND,          //!< 探しにいったが見つからなかった場合
	DB_ERRORTYPE_COMMANDERROR,      //!< コマンドが不正なものだった
	DB_ERRORTYPE_DBERROR,           //!< DB の方で何かエラーがあったらしい
	DB_ERRORTYPE_INVALIDDATA,       //!< DB に渡したデータが不正なデータだった
	DB_ERRORTYPE_MAX,
} DB_ErrorType;



/**
 * @brief DB からのエラー情報を含んだもの
 *          
 * @author  Takuya Shishido
 * @date    2010.04.22 12:52:03
 * @version 0.01, Shishido Takuya, 2010.04.22 12:52:03
 */
typedef struct
{
	char error[0xff];
} DBError;



/**----------------------------------------------------
 * @brief ErrorType を const char* に変換
 * @param[in]   error_      エラーの内容
 * @return      対応した文字列
 *---------------------------------------------------*/
//const char* convertFromErrorTypeToChar(DB_ErrorType error_);


#endif

