
#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <memory>
#include "Modeler.hpp"

#include "Define.hpp"


//! \brief �������ꊇ���čs�����߂̃t�@���N�^
//! \note   ���ꉻ���Ďg���Ă�̂Ŏ����͂Ȃ�
template<typename Type>
class Executioner;

//! \brief �������ꊇ���čs�����߂̃t�@���N�^
//! \note   ���ꉻ���ꂽ��B�R���g���[���̃��[�v���܂킷���߂Ɏg�p
template<>
class Executioner<ControlerInterface> {
public:

	//! \brief constructor
	//! \param[in]  input_      ���[�U����̓��͏��
	Executioner(Input input_) : input(input_) {}

	//! \brief operator() (�֐��Ăяo��)
	template<typename Type>
	void operator()(const Type& type) {
		ControlerInterfaceContainer result;
		result = type->update(this->input);
		command.merge(result);
	}

	ControlerInterfaceContainer command;    //!< �쐬���ꂽ�q�̃R���g���[���̊i�[��
	Input input;    //!< ���͏�
};

//! \brief �������ꊇ���čs�����߂̃t�@���N�^
//! \note   ���ꉻ���Ďg���Ă�̂Ŏ����͂Ȃ�
template<>
class Executioner<ModelerInterface> {
public:
	template<typename Type>
	void operator()(const Type& type) {
		type->process();
	}
};


//! \brief �������ꊇ���čs�����߂̃t�@���N�^
//! \note   ���ꉻ���Ďg���Ă�̂Ŏ����͂Ȃ�
template<>
class Executioner<ViewerInterface> {
public:
	template<typename Type>
	void operator()(const Type& type) {
		type->draw();
	}
};


template<typename Type>
class LockUpToSharedPtr {
public:
	void operator()(Type* type) {
		container.push_back(std::tr1::shared_ptr<Type>(type));
	}
	std::list<std::tr1::shared_ptr<Type> > container;
};


class EqualityWithQuestion {
public:
	EqualityWithQuestion(Question question_) : question(question_) {}

	template<typename Type>
	bool operator()(const Type& type) {
		return type->getFlagState(this->question);
	}

	Question question;
};


class FindByID {
public:
	FindByID(unsigned int ID_) : ID(ID_) {}

	template<typename Type>
	bool operator()(const Type& type_) {
		return type_->getID() == this->ID;
	}

	unsigned int ID;
};


#endif  // UTILITY_HPP_INCLUDED
