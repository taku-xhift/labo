
#ifndef CONTROLER_HPP_INCLUDED
#define CONTROLER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <algorithm>
#include <list>
#include <bitset>

#include "Define.hpp"


// <windows.h> �Œ�`����Ă���炵��
#ifdef max
#undef max
#endif


//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
class ModelInterface;


//! \brief �C���^�[�t�F�[�X�N���X
class ControlerInterface {
private:
	friend class EqualityWithQuestion;
public:

	//! \brief constructor
	//! \param[in]  parentID_   �e�� ID�B���b�Z�[�W�p
	ControlerInterface(unsigned int parentID_ = std::numeric_limits<unsigned int>::max());

	//! \brief destructor
	//! \note   �p���p
	virtual ~ControlerInterface();

	//! \brief ���͉�͗p
	//! \param      input_      View �Ŏ擾���ꂽ����
	//! \return     �q�̏��������K�v������΂����Ԃ�
	virtual ControlerInterfaceContainer update(const Input& input_) = 0;

	//! \brief ���������L���� Model �Ŏ擾����f�[�^��������΂��̏����𑖂点��
	//! \note   �I�[�o�[���[�h�֎~
	void processing();

	//! \brief Model �Ƀ��b�Z�[�W������΂���ŁB��͂� Model �̎d��
	//! \param[in]  ID_         Model �� ID�B
	//                          �Ǘ����鎞�_�ŕK�v�ɂȂ肻���Ȃ��̂͊e���p�����
	//                          ID �������o�Ƃ��ĕۑ����Ă������ƁB
	//! \param[in]  message_    �`���郁�b�Z�[�W�B��͂� Model �̎d���B
	//! \retval     true        ���b�Z�[�W�𐳏�ɓ`����
	//! \retval     false       ID_ ��������Ȃ�����
	bool sendMessageToModel(unsigned int ID_, std::string message_);

	//! \brief ���f���I�u�W�F�N�g��o�^����ۂ̑����
	//! \param[in]   model_  �o�^���郂�f��
	void addModelContainer(ModelerInterface* model_)                    { this->modelContainer.push_back(model_); }
	void addModelContainer(ModelerInterfaceContainer modelContainer_)   { this->modelContainer.merge(modelContainer_); }


	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	unsigned int getID() const              { return this->uniqueID; }
	unsigned int getParentID() const        { return this->parentID; }

protected:

	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	bool getFlagState(Question question_) const             { return this->flagSet[question_]; }
	void setFlagSet(Question question_, bool parameter_)    { this->flagSet[question_] = parameter_; }

private:

	static unsigned int serialNumber;   //!< unique �� ID �����p
	unsigned int        uniqueID;       //!< ���g�� ID
	unsigned int        parentID;       //!< �e������΂��� ID�B���Ȃ��Ȃ� std::numeric_limits<unsigned int>::max()

	std::bitset<Question_Max>   flagSet;            //!< ��ԊǗ��p
	ModelerInterfaceContainer   modelContainer;     //!< �`��p�f�[�^�ƕ`����@�̃Z�b�g�R���e�i
};


//! \brief �|���V�[�p�^�[���ɂ��z�X�g
//! \note   template �p�����[�^�ɂ���Ďw�肵���N���X�ɉ����ĐU�镑����ς���
template<typename ControlPolicy>
class Controler
	: public ControlPolicy
{
public:
	//! \brief constructor
	//! \param[in]  parentID_   �e ID
	Controler(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ControlPolicy(parentID_)
	{
	}

	//! \brief �C���^�[�t�F�[�X�̎���
	//! \note   ���[�U����� Model �I�u�W�F�N�g�̃|�C���^�̃��X�g���Ԃ��Ă���̂�
	//          ����� std::shared_ptr �ŊǗ����Ȃ���
	ControlerInterfaceContainer update(const Input& input_) {
		ControlerInterfaceContainer newControlList = this->ControlPolicy::update(input_);
		this->processing();
		return newControlList;
	}

	//! \brief ��ԊǗ��̃C���^�[�t�F�[�X
	//! \note       ���[�U�������������g�����̂܂ܕԂ�
	//! \param[in]  question_   ����̐U�镑���Ɋւ��Ă̎���
	bool getFlagState(Question question_) {
		return this->ControlPolicy::getFlagState(question_);
	}

};


//! \brief Controler �N���X���Ǘ�����B
//! \note   ���b�Z�[�W�����������B
//          �������I�u�W�F�N�g�ɖ₢�����邾���Ŏ�̐��͂��̃N���X
//          �I�u�W�F�N�g�̐e�q�֌W���q�͐e�� ID ��m���Ă��邾���B
//          �e���q��]�������肹���܂������������x���ōs����
class ControlManager {
public:
	//! \brief �������Ă���I�u�W�F�N�g��]������
	//! \note       ���b�Z�[�W����������
	//! \param[in]  input_  ����
	void execute(const Input& input_);

	//! \brief �V������ʊǗ��Ȃǂ���t
	//! \param[in]  control_    �V������ʊǗ��N���X
	void add(ControlerInterface* control_)          { this->controlList.push_back(control_); }

	//! \brief ���g�����L���Ă����ʊǗ��N���X�̐����擾
	//! \note   0 �Ȃ珈�����ׂ����̂����������̂ŏ����Ă����v��������Ȃ�
	unsigned int getControlInterfaceSize() const    { return this->controlList.size(); }

private:
	ControlerInterfaceContainer controlList;     //!< ��ʏ����N���X�Q
};

//====================  Policy �p�^�[���ɂ�����  ==================================
//
// ���[�U�̎�������
//    1. �����K�{ (ControlerInterface �̃C���^�[�t�F�[�X)
//          SpModelerInterfaceContainer update(const Input&)
//          bool getFlagState(Question)
//
//    2. ��������
//          �f�X�g���N�^�̃A�N�Z�X���x���� protected �ɂ��邱��
//
//      ��L�̏����𖞂����΂��̑��͎��R�ɍ쐬�\
//          getFlagState �𖞂������߂̃t���O���D���Ȍ`�ŏ������Ă悢�B
//              (bitset ���g������ bool �ŊǗ�������Ȃ�)
//
//    3. �������e
//          ���e�� Model �]�����@�Ƃ��� View ���@�̎w��B
//          �w����@��
//              Modeler<Chat<Cout> >* temp = new Modeler<Chat<Cout> > ();
//          �̂悤�Ȍ`�BModeler<Model<View>>* �̌`�Ńf�[�^�����
//          std::list �̃R���e�i�Ɋi�[���ĕԂ��ƌ�Ŏ����Ŏ��s�����B



//! \brief �e�X�g�p : ���[�O�t���[�Ǘ��N���X
class LeagueFlow
	: public ControlerInterface
{
public:

	LeagueFlow(unsigned int parentID_ /*= std::numeric_limits<unsigned int>::max()*/);

	//!< \brief method ����
	ControlerInterfaceContainer update(const Input& input_);

protected:
	~LeagueFlow() {}

private:
	int step;       //!< ���g�̃X�e�b�v�Ǘ�
};



#endif  // CONTROLER_HPP_INCLUDED
