
#ifndef VIEWER_HPP_INCLUDED
#define VIEWER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include <bitset>
#include "Utility.hpp"

// <windows.h> �Œ�`����Ă���炵��
#ifdef max
#undef max
#endif


//! \brief �C���^�[�t�F�[�X�N���X
class ViewerInterface {
private:
	friend class EqualityWithQuestion;
public:

	//! \brief constructor
	//! \param[in]  parentID_   �e�� ID�B���b�Z�[�W�p
	ViewerInterface(int parentID_ = std::numeric_limits<unsigned int>::max());

	//! \brief destructor
	//! \note   �p���p
	virtual ~ViewerInterface() {}

	//! \brief �`�揈��
	virtual void draw() = 0;

	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	unsigned int getID() const          { return this->uniqueID; }
	unsigned int getParentID() const    { return this->parentID; }

protected:

	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	bool getFlagState(Question question_) const             { return this->flagSet[question_]; }
	void setFlagSet(Question question_, bool parameter_)    { this->flagSet[question_] = parameter_; }

private:

	static unsigned int serialNumber;   //!< unique �� ID �����p
	unsigned int uniqueID;              //!< ���g�� ID
	unsigned int parentID;              //!< �e������΂��� ID�B���Ȃ��Ȃ� std::numeric_limits<unsigned int>::max()

	std::bitset<Question_Max>   flagSet;            //!< getFl��ԊǗ��p
};


//===============================================================================
// ���[�U�̎�������
//    1. �����K�{ (ControlerInterface �̃C���^�[�t�F�[�X)
//          void method()
//          bool getFlagState(Question question_)
//    2. ��������
//          2.1 �f�X�g���N�^�̃A�N�Z�X���x���� protected �ɂ��邱��
//          2.2 method �Ŏ󂯎��f�[�^�� const Type& �̌`�Ŏ󂯎��A�f�[�^��ύX���Ȃ�����
//          2.3 method �� static �֐��ɂ��邱�ƁBstate �̊Ǘ��� Model �̎d���Bstate �ŏ������ς��Ȃ�N���X����蒼���B
//
//      ��L�̏����𖞂����΂��̑��͎��R�ɍ쐬�\
//          ��{�I�� Controler �̎��Ɠ���
//
//    3. �������e
//          �`�惁�\�b�h�B



//! \brief cout ���g�p���Ă̕\��
class Cout
	: public ViewerInterface {
public:
	template<typename Type>
	static void draw(const Type& data_) {
		std::cout << typeid(Cout).name() << " : " << data_ << std::endl;
	}

	bool getFlagState(Question question_) { return this->flagSet[question_]; }

protected:
	~Cout() {}
private:
	std::bitset<Question_Max>    flagSet;
};

//! \brief printf ���g�p���Ă̕\��
class Printf
	: public ViewerInterface {
public:

	static void draw(const char* data_) { printf("%s : %s", typeid(Printf).name(), data_); }

	bool getFlagState(Question question_) { return this->flagSet[question_]; }

protected:
	~Printf() {}
private:
	std::bitset<Question_Max>    flagSet;
};

#endif  // VIEWER_HPP_INCLUDED
