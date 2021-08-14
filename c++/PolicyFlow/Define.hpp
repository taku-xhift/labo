
#ifndef DEFINE_HPP_INCLUDED
#define DEFINE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <list>
#include <memory>


//! \brief �I�u�W�F�N�g�Ǘ��p�̎���Q
enum Question {
	Question_MayIKillYou,
	Question_LeaveAMessage,
	Question_WannaTakeARest,
	Question_WannaGiveBirthToChildren,
	Question_Max,
};


//! \brief �[�����͎󂯕t���p
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

