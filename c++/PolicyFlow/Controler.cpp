
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
//! \param[in]  parentID_   �e�� ID�B���b�Z�[�W�p
ControlerInterface::ControlerInterface(unsigned int parentID_ /*= std::numeric_limits<unsigned int>::max()*/)
	: uniqueID(ControlerInterface::serialNumber)
	, parentID(parentID_)
{
	this->flagSet.reset();

	// 40 ���g���؂����ꍇ�̏������l���Ƃ��H
	++ControlerInterface::serialNumber;
}

//! \brief destructor
//! \note   �p���p
ControlerInterface::~ControlerInterface() {
	for (ModelerInterfaceContainer::iterator ite = this->modelContainer.begin(); ite != this->modelContainer.end(); ++ite) {
		delete *ite;
	}
}

//! \brief ���������L���� Model �Ŏ擾����f�[�^��������΂��̏����𑖂点��
//! \note   �I�[�o�[���[�h�֎~
void ControlerInterface::processing() { 
	std::for_each(this->modelContainer.begin(), this->modelContainer.end(), Executioner<ModelerInterface>());
	this->modelContainer.remove_if(EqualityWithQuestion(Question_MayIKillYou));
}

//! \brief Model �Ƀ��b�Z�[�W������΂���ŁB��͂� Model �̎d��
//! \param[in]  ID_         Model �� ID�B
//                          �Ǘ����鎞�_�ŕK�v�ɂȂ肻���Ȃ��̂͊e���p�����
//                          ID �������o�Ƃ��ĕۑ����Ă������ƁB
//! \param[in]  message_    �`���郁�b�Z�[�W�B��͂� Model �̎d���B
//! \retval     true        ���b�Z�[�W�𐳏�ɓ`����
//! \retval     false       ID_ ��������Ȃ�����
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


//! \brief �������Ă���I�u�W�F�N�g��]������
//! \note       ���b�Z�[�W����������
//! \param[in]  input_  ����
void ControlManager::execute(const Input& input_) {
	Executioner<ControlerInterface> newControlList = std::for_each(this->controlList.begin(), this->controlList.end(), Executioner<ControlerInterface>(input_));
	this->controlList.remove_if(EqualityWithQuestion(Question_MayIKillYou));
}

LeagueFlow::LeagueFlow(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
	: ControlerInterface(parentID_)
{
}

//!< \brief method ����
//!< \note  �������� Model ������Ă݂Ă����Ԃ�
//              Model �̑傫��(�����P��)�͎����ɂ��B
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

