/**
 * @file  ExceptionMessageCreator.cpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.08.16 21:24:00
 *
 * @version 1.02, Shishido Takuya, 2011.08.16 21:24:00
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include "weoExceptionMessageCreator.h"
#include <sstream>


namespace pm_mode {


/********************************************************************
 * @brief 一定のフォーマットに法った文字列を作成する
 * @note    ExceptionMessage に使用されることを前提としている
 * @param[in]   message     何か残したい特別なメッセージ
 * @param[in]   fileName    文字列を作成したファイルの名前
 * @param[in]   line        文字列を作成した行
 * @param[in]   function    文字列を作成した関数
 * @return      情報をまとめた文字列
 *******************************************************************/
std::string messageCreator(const std::string& message, bool isException, weString fileName, int line, weString function) throw()
{
	std::stringstream ss;
	std::string returnValue;

	if (isException) {
		returnValue += "Exception is thrown!!!\nmessage: " + message;
	} else {
		returnValue += "Have Message!!!\nmessage: " + message;
	}

	returnValue.append("\nfile: ");
	returnValue.append(fileName);

	ss << line;
	returnValue += "\nline: ";
	returnValue += ss.str();

	returnValue.append("\nfunction: ");
	returnValue.append(function);
	returnValue.append("\n");

	return returnValue;
}


}    // namespace pm_mode

