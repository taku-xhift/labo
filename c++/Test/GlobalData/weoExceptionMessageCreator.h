/**
 * @file  ExceptionMessageCreator.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.08.16 21:24:00
 *
 * @version 1.02, Shishido Takuya, 2011.08.16 21:24:00
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_EXCEPTIONMESSAGECREATOR_HPP_INCLUDED
#define PM_MODE_EXCEPTIONMESSAGECREATOR_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include <string>
#include "weCommonType.h"
#include "weoDLLModefied.h"


namespace pm_mode {


// 通常メッセージに行数や関数名などを付ける
#define NormalDetailMessage(message_) pm_mode::messageCreator(message_, false, __FILE__, __LINE__, __FUNCTION__).c_str()

// 例外メッセージの生成
#define ExceptionMessage(message_) pm_mode::messageCreator(message_, true, __FILE__, __LINE__, __FUNCTION__).c_str()


/****************************************************************
 * @brief 一定のフォーマットに法った文字列を作成する
 * @note    ExceptionMessage に使用されることを前提としている
 * @param[in]   message     何か残したい特別なメッセージ
 * @param[in]   isException 例外かどうか
 * @param[in]   fileName    文字列を作成したファイルの名前
 * @param[in]   line        文字列を作成した行
 * @param[in]   function    文字列を作成した関数
 * @return      情報をまとめた文字列
 ***************************************************************/
WE_MODE_DLL_EXPORT std::string messageCreator(const std::string& message, bool isException, weString fileName, int line, weString function) throw();


}    // namespace pm_mode


#endif

