
#ifndef MODELER_HPP_INCLUDED
#define MODELER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include <string>
#include <bitset>
#include <limits>
#include "DB.hpp"
#include "Define.hpp"


// <windows.h> �Œ�`����Ă���炵��
#ifdef max
#undef max
#endif



//! \brief �C���^�[�t�F�[�X�N���X
class ModelerInterface {
private:
	friend class EqualityWithQuestion;
public:

	//! \brief constructor
	//! \param[in]  parentID_   �e�� ID�B���b�Z�[�W�p
	ModelerInterface(unsigned int parentID_ = std::numeric_limits<unsigned int>::max());

	//! \brief destructor
	//! \note   �p���p
	virtual ~ModelerInterface() {}

	//! \brief �������������ׂ����e���L�q
	virtual void process() = 0;

	//! \brief ���b�Z�[�W���󂯎�邽�߂̃C���^�[�t�F�[�X
	//! \param[in]  message_    ���e�B��͕͂K�v������Όp����Ŏ����B
	void setMessage(std::string message_)   { this->message = message_; }

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

	std::bitset<Question_Max>   flagSet;        //!< ��ԊǗ��p
	std::string                 message;        //!< control �����烁�b�Z�[�W������Γ����Ă�
};

template<typename ModelPolicy>
class Modeler
	: public ModelPolicy
{
public:
	//! \brief constructor
	//! \param[in]  parentID_   �e ID�B
	Modeler(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelPolicy(parentID_)
	{
	}

	//! \brief �����Ɏ�������Ă��鏈�����s��
	//! \note   �p�����̎������Ăяo������
	void process() {
		this->ModelPolicy::process();
	}
};

//===============================================================================
// ���[�U�̎�������
//    1. �����K�{ (ControlerInterface �̃C���^�[�t�F�[�X)
//          void process()
//          bool getFlagState(Question question_)
//
//    2. ��������
//          �f�X�g���N�^�̃A�N�Z�X���x���� protected �ɂ��邱��
//
//      ��L�̏����𖞂����΂��̑��͎��R�ɍ쐬�\
//          ��{�I�� Controler �̎��Ɠ���
//
//    3. �������e
//          �f�[�^���������ĕ`��ɕK�v�ȃf�[�^����������B
//          �������o������
//              ViewPolicy::method(this->message);
//          �̂悤�Ȍ`�Ńf�[�^�n���� View ��]������B
//          ������O���������� View ��]�����Ȃ���Ε`�悳��Ȃ��B
//          �]�����邵�Ȃ��̔��f���炢�͋�����Ă���B



//! brief �`���b�g����
template<typename ViewPolicy>
class Chat
	: public ModelerInterface {
public:

	//! \brief �������R���X�g���N�^
	//! \note   ����������� Controler ���ŃC���X�^���X���̕��@������Ȃ�B
	//          �s�\�ł͂Ȃ������ꂪ�K�v�Ȃ̂ŁAsetData �̂悤�ȃC���^�[�t�F�[�X��
	//          �������ăZ�b�g���Ă��炤�Ƃ������@�������̂�������Ȃ��B
	Chat(std::string message_, unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelerInterface(parentID_)
		, message(message_)
	{
	}

	//! \brief �����Ȃ��R���X�g���N�^
	//! \note   ��L�̗��R�ň�������������
	Chat(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelerInterface(parentID_)
	{
	}

	void process() {
		std::cout << typeid(Chat).name() << " : ";
		ViewPolicy::draw(this->message);
		this->setFlagSet(Question_MayIKillYou, true);
	}

	void sendMessage(std::string message_) { this->message = message_; }

protected:

	~Chat() {}

private:

	std::string     message;    //!< �`���b�g�p���b�Z�[�W
};


//! \brief DB �A�N�Z�X
template<typename ViewPolicy>
class AskDataBase
	: public ModelerInterface {
public:

	AskDataBase(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelerInterface(parentID_)
	{
	}

	void process() {
		int data = ++userID;
		std::cout << typeid(AskDataBase).name() << " : ";
		ViewPolicy::draw(data);
		this->setFlagSet(Question_MayIKillYou, true);
	}

protected:

	~AskDataBase() {}
};

#endif  // MODELER_HPP_INCLUDED
