/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.10.07 15:57:06
 *
 * @version 0.01, Shishido Takuya, 2010.10.07 15:57:06
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef FLOWDEFINE_HPP_INCLUDED
#define FLOWDEFINE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include <deque>
//#include <typeinfo>
#include "weoSpTypeInfo.h"

#include "weCommonType.h"
#include "weoLexicalCast.h"
//#include "weoCommand.h"

//
////-----------------------------------------------------
////  declaration
////-----------------------------------------------------
//namespace pm_mode {
//	namespace task {
//		class ControlerInterfaceFlow;
//		class ModelerInterfaceFlow;
//		class ViewerInterfaceFlow;
//		class FlowMessage;
//	}
//}


//-----------------------------------------------------
//  define
//-----------------------------------------------------

// コンパイル時アサート。 cond が false だとコンパイルエラーが発生する
// 後でもうちょっと書き換え予定
#define STATIC_ASSERT(cond)             extern weInt assert_function(weInt [(cond)?1:-1])

// 例外メッセージの自動生成
#define ExceptionMessage(message_)\
("Exception is thrown!!\n\
message  : " + std::string(message_) + "\n\
file     : " + ::pm_mode::lexical_cast<std::string, const char*>(__FILE__) + "\n\
line     : " + ::pm_mode::lexical_cast<std::string, weInt>(__LINE__) + "\n\
function : " + ::pm_mode::lexical_cast<std::string, weString>(__FUNCTION__) + "\n").c_str()



//#define typeid_of(Type) typeid(Type)




namespace pm_mode {


//! \brief MVC のフローからの状態管理用
enum Question {
	Question_MayIKillYou,                   //!< 削除してもいい？
	Question_WannaTakeARest,                //!< 休みたい？
	Question_WannaGiveBirthToChildren,      //!< 子供作りたい？
	Question_WannaCheckMail,                //!< メールチェックはしたい？
	Question_Max,
};


//! \brief Model の状態管理。
enum ControlState {
	CONTROLSTATE_INIT,
	CONTROLSTATE_UPDATE,
	CONTROLSTATE_EXIT,
	CONTROLSTATE_MAX,
};


//! \brief Model の状態管理。
enum ViewState {
	VIEWSTATE_LOADFLASH,    //!< フレームワーク用
	VIEWSTATE_INIT,
	VIEWSTATE_UPDATE,
	VIEWSTATE_EXIT,
	VIEWSTATE_MAX,
};



//! \brief Model の状態管理。
enum ModelState {
	MODELSTATE_INIT,
	MODELSTATE_LOAD,
	MODELSTATE_SEND,
	MODELSTATE_MAIN,
	MODELSTATE_EXIT,
	MODELSTATE_MAX,
};
//
//
//
//typedef std::deque<Input>               InputList;      //!< 入力情報のコンテナ
//typedef std::deque<task::FlowMessage>   MessageList;    //!< メッセージのコンテナ
//
//typedef std::vector<task::ControlerInterfaceFlow*>          ControlerInterfaceFlowContainer;    //!< Control のコンテナ
//typedef std::tr1::shared_ptr<task::ControlerInterfaceFlow>  SpControlerInterfaceFlow;           //!< Control のスマートポインタ
//typedef std::vector<SpControlerInterfaceFlow>               SpControlerInterfaceFlowContainer;  //!< Control のスマートポインタのコンテナ
//
//typedef std::vector<task::ModelerInterfaceFlow*>            ModelerInterfaceFlowContainer;      //!< Model のコンテナ
//typedef std::tr1::shared_ptr<task::ModelerInterfaceFlow>    SpModelerInterfaceFlow;             //!< Model のスマートポインタ
//typedef std::vector<SpModelerInterfaceFlow>                 SpModelerInterfaceFlowContainer;    //!< Model のスマートポインタのコンテナ
//
//typedef std::vector<task::ViewerInterfaceFlow*>             ViewerInterfaceFlowContainer;       //!< View のコンテナ
//typedef std::tr1::shared_ptr<task::ViewerInterfaceFlow>     SpViewerInterfaceFlow;              //!< View のスマートポインタ
//typedef std::vector<SpViewerInterfaceFlow>                  SpViewerInterfaceFlowContainer;     //!< View のスマートポインタのコンテナ


}   // namespace pm_mode


#endif

