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

#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <memory>
#include "Modeler.hpp"

#include "Define.hpp"


//! \brief 処理を一括して行うためのファンクタ
//! \note   特殊化して使ってるので実装はなし
template<typename Type>
class Executioner;

//! \brief 処理を一括して行うためのファンクタ
//! \note   特殊化された例。コントロールのループをまわすために使用
template<>
class Executioner<ControlerInterface> {
public:

	//! \brief constructor
	//! \param[in]  input_      ユーザからの入力情報
	Executioner(Input input_) : input(input_) {}

	//! \brief operator() (関数呼び出し)
	template<typename Type>
	void operator()(const Type& type) {
		ControlerInterfaceContainer result;
		result = type->update(this->input);
		command.merge(result);
	}

	ControlerInterfaceContainer command;    //!< 作成された子のコントロールの格納先
	Input input;    //!< 入力状況
};

//! \brief 処理を一括して行うためのファンクタ
//! \note   特殊化して使ってるので実装はなし
template<>
class Executioner<ModelerInterface> {
public:
	template<typename Type>
	void operator()(const Type& type) {
		type->process();
	}
};


//! \brief 処理を一括して行うためのファンクタ
//! \note   特殊化して使ってるので実装はなし
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
