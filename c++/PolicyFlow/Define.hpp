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

#ifndef DEFINE_HPP_INCLUDED
#define DEFINE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <list>
#include <memory>


//! \brief オブジェクト管理用の質問群
enum Question {
	Question_MayIKillYou,
	Question_LeaveAMessage,
	Question_WannaTakeARest,
	Question_WannaGiveBirthToChildren,
	Question_Max,
};


//! \brief 擬似入力受け付け用
typedef int Input;


class ControlerInterface;
class ModelerInterface;
class ViewerInterface;

typedef std::list<ControlerInterface*>          ControlerInterfaceContainer;
typedef std::tr1::shared_ptr<ControlerInterface> SpControlerInterface;
typedef std::list<SpControlerInterface>         SpControlerInterfaceContainer;

typedef std::list<ModelerInterface*>            ModelerInterfaceContainer;
typedef std::tr1::shared_ptr<ModelerInterface>   SpModelerInterface;
typedef std::list<SpModelerInterface>           SpModelerInterfaceContainer;

typedef std::list<ViewerInterface*>             ViewerInterfaceContainer;
typedef std::tr1::shared_ptr<ViewerInterface>    SpViewerInterface;
typedef std::list<SpViewerInterface>            SpViewerInterfaceContainer;



#endif

