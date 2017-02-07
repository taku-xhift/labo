/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.10.07 15:20:08
 *
 * @version 0.01, Shishido Takuya, 2010.10.07 15:20:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <limits>
#include "Controler.hpp"
#include "Modeler.hpp"
#include "Viewer.hpp"
#include "Utility.hpp"

unsigned int ControlerInterface::serialNumber = 0;

//! \brief constructor
//! \param[in]  parentID_   親の ID。メッセージ用
ControlerInterface::ControlerInterface(unsigned int parentID_ /*= std::numeric_limits<unsigned int>::max()*/)
	: uniqueID(ControlerInterface::serialNumber)
	, parentID(parentID_)
{
	this->flagSet.reset();

	// 40 億使い切った場合の処理を考えとく？
	++ControlerInterface::serialNumber;
}

//! \brief destructor
//! \note   継承用
ControlerInterface::~ControlerInterface() {
	for (ModelerInterfaceContainer::iterator ite = this->modelContainer.begin(); ite != this->modelContainer.end(); ++ite) {
		delete *ite;
	}
}

//! \brief 自分が所有する Model で取得するデータ等があればその処理を走らせる
//! \note   オーバーロード禁止
void ControlerInterface::processing() { 
	std::for_each(this->modelContainer.begin(), this->modelContainer.end(), Executioner<ModelerInterface>());
	this->modelContainer.remove_if(EqualityWithQuestion(Question_MayIKillYou));
}

//! \brief Model にメッセージがあればこれで。解析は Model の仕事
//! \param[in]  ID_         Model の ID。
//                          管理する時点で必要になりそうなものは各自継承先で
//                          ID をメンバとして保存しておくこと。
//! \param[in]  message_    伝えるメッセージ。解析は Model の仕事。
//! \retval     true        メッセージを正常に伝えた
//! \retval     false       ID_ が見つからなかった
bool ControlerInterface::sendMessageToModel(unsigned int ID_, std::string message_) {
	bool result = true;
	ModelerInterfaceContainer::iterator model = std::find_if(this->modelContainer.begin(), this->modelContainer.end(), FindByID(ID_));
	if (model != this->modelContainer.end()) {
		result = false;
	} else {
		(*model)->setMessage(message_);
	}

	return result;
}


//! \brief 所持しているオブジェクトを評価する
//! \note       メッセージ処理もここ
//! \param[in]  input_  入力
void ControlManager::execute(const Input& input_) {
	Executioner<ControlerInterface> newControlList = std::for_each(this->controlList.begin(), this->controlList.end(), Executioner<ControlerInterface>(input_));
	this->controlList.remove_if(EqualityWithQuestion(Question_MayIKillYou));
}

LeagueFlow::LeagueFlow(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
	: ControlerInterface(parentID_)
{
}

//!< \brief method 実装
//!< \note  いくつかの Model を作ってみてそれを返す
//              Model の大きさ(処理単位)は実装による。
ControlerInterfaceContainer LeagueFlow::update(const Input& input_)
{
	if ((step%2) == 0) {
		//Modeler<Chat<Cout> >* temp = new Chat<Cout>("Oh, Shit!");
		//temp->sendMessage("Oh, Shit!");
		this->addModelContainer(new Chat<Cout>("Oh, Shit!"));
	}
	if ((step%3) == 0) {
		this->addModelContainer(new AskDataBase<Cout>());
	}

	if (input_ == 0) {
		this->setFlagSet(Question_MayIKillYou, true);
	}

	++this->step;
	return ControlerInterfaceContainer();
}

