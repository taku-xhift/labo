
#define Any_ALONETEST 1

#ifndef PM_WEO_TASK_ANY_HPP_INCLUDED
#define PM_WEO_TASK_ANY_HPP_INCLUDED


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include <limits>
#include <assert.h>
//#include <type_traits>
#include <string>

#include "weoSpTypeInfo.h"
#include "weoTypeTraits.h"

#if (Any_ALONETEST == 1)
#include <iostream>
#else
#include "weDebug.h"
#include "weoLexicalCast.h"
#include "weoFlowException.h"
#endif


//-----------------------------------------------------
//  decralation
//-----------------------------------------------------
namespace pm_mode {
	class bad_any_cast;     //!< �L���X�g���s���������߂̗�O�N���X
}



#ifndef NEW
#define NEW new
#endif


namespace pm_mode {


//! brief �C�ӌ^�f�[�^��ۑ�����N���X
class Any
{
public:

	//! \brief constructor
	Any() throw()
		: content(NULL) {}

	//! \brief constructor
	//! \param[in]  value_  �C�ӌ^�̃f�[�^
	template<typename ValueType>
	Any(const ValueType& value_) throw()
		: content(NEW Holder<ValueType>(value_))
	{
	}

	//! \brief constructor
	//! \param[in]  value_  �C�ӌ^�̃f�[�^
	Any(const Any& other_) throw()
		: content(other_.content ? other_.content->clone() : NULL)
	{
	}

	//! \brief destructor
	~Any() throw() {
		if (this->content != NULL) {
			delete this->content;
			this->content = NULL;
		}
	}


	//! \brief ������� Any �Ǝ����̃f�[�^����ւ�
	//! \param[in]  rhs_    ����ւ���
	Any& swap(Any& rhs_) throw() {
		std::swap(this->content, rhs_.content);
		return *this;
	}

	//! \brief operator = (�f�[�^�{�̂� = �łȂ�)
	//! \param[in]  rhs_    ����ւ���
	template<typename ValueType>
	Any& operator=(const ValueType& rhs_) throw() {
		Any(rhs_).swap(*this);
		return *this;
	}

	//! \brief operator = (Any �^�̃f�[�^�Ƃ� =)
	//! \param[in]  rhs_    Any �^�̃f�[�^
	Any& operator=(Any rhs_) throw() {
		rhs_.swap(*this);
		return *this;
	}


	//! \brief �f�[�^�̗L���̃`�F�b�N
	//! \retval     true    �L��
	//! \retval     false   ����
	bool empty() const throw()                              { return !this->content; }

	//! \brief �����Ă���f�[�^�� typeID ��Ԃ�
	//! \return     �^���Ƀ��j�[�N�� ID�B�Ȃ���� ""
	const char* const typeName() const throw()              { return this->content ? this->content->name() : ""; }

	//! \breif cast ���ē����f�[�^���擾����
	//! \return    �L���X�g�ς݂̃f�[�^
	//! \except     bad_any_cast    template �p�����[�^�Ɏw�肳�ꂽ�^�ɕϊ��ł��Ȃ�
	template<typename ValueType>
	const ValueType& getAs() const throw(bad_any_cast) {
		if (this->typeName() != typeid_of(ValueType).name()) {
			throw bad_any_cast(
#if (Any_ALONETEST == 0)
				std::string("Exception is thrown!!\nmessage: "
				    + std::string("bad_any_cast") + "\nfile: "
				    + ::pm_mode::lexical_cast<std::string>(__FILE__)
				    + "\nline: " + ::pm_mode::lexical_cast<std::string>(__LINE__)
				    + "\nfunction: " + ::pm_mode::lexical_cast<std::string>(__FUNCTION__)
				    + "\nmessage: MyType is " + this->typeName() + ", ValueType is " + typeid_of(ValueType).name()
				    + "\n")
#else
				""
#endif
				);
		}
		return static_cast<Holder<ValueType>*>(this->content)->held_;
	}

	//! \brief cast �ς݂̃f�[�^���擾����(�n�����f�[�^�^�Ɏ����ŕϊ�)
	//! \param[out] out_    �f�[�^�o�͐�
	//! \retval     true    �L���X�g���A�i�[�o����
	//! \retval     false   �L���X�g�s�\������
	template<typename ValueType>
	bool store(ValueType& out_) throw() {
		if (this->content.name() != typeid_of(ValueType).name()) {
			return false;
		}
		out_ = static_cast<Holder<ValueType>*>(this->content)->held_;
		return true;
	}


private:

	//! brief �f�[�^�z���_�[�̃C���^�[�t�F�[�X�^
	struct PlaceHolder
	{
		//! \brief destructor
		virtual ~PlaceHolder() {}

		//! \brief �����Ă���f�[�^�̌^�����܂񂾕������Ԃ�
		//! \return     �^���Ƀ��j�[�N�Ȗ��O�B
		virtual const char* const name() const throw() = 0;

		//! \brief �f�[�^�̃N���[����Ԃ�
		virtual PlaceHolder* clone() const throw() = 0;
	};

	//! \brief �f�[�^�z���_�[�̎���
	template<typename ValueType>
	class Holder
		: public PlaceHolder
	{
	public:

		//! \brief copy constructor
		explicit Holder(const ValueType& value_) throw()
			: held_(value_)
			, name_(typeid_of(ValueType).name())
		{
		}

		//! \brief �����Ă���f�[�^�̌^�����܂񂾕������Ԃ�
		//! \return     �^���Ƀ��j�[�N�Ȗ��O�B
		virtual const char* const name() const throw() { return this->name_; }

		//! \brief �f�[�^�{�̂̃R�s�[
		//! \return     new �����l
		virtual PlaceHolder* clone() const throw() {
			return NEW Holder(held_);
		}

	public:

		ValueType           held_;      //!< �f�[�^�{��
		const char* const   name_;      //!< �i�[���Ă���f�[�^�̌^�����܂ޖ��O

	private:
		//! \brief operator = �̋֎~
		Holder& operator=(const Holder&) throw();
	};

private:

	//! \brief cast �֐��ɑ΂���f�[�^�̌��J
	template<typename ValueType>
	friend ValueType* any_cast(Any*);

	PlaceHolder* content;   //!< �C�ӌ^��ۑ����邽�߂̃f�[�^�z���_�[
};


//! \brief �L���X�g���s���������߂̗�O�N���X
//! \note   �z�Q�ƂɂȂ��Ă��܂��̂ŁAFlowException �͌p���ł��Ȃ�
class bad_any_cast
//	: public task::FlowException
	: std::exception
{
public:

#if Any_ALONETEST
	const char* what() const throw() { return ""; }
#endif

	//! \brief constructor
	//! \param[in]  message_    error message
	explicit bad_any_cast(std::string message_ = "") throw()
#if (Any_ALONETEST == 1)
		: std::exception(message_.c_str()) {}
#else
		: task::FlowException(message_) {}
#endif
};


//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B�|�C���^�Enon-const �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
template<typename ValueType>
ValueType* any_cast(Any* operand_) throw () {
	return operand_ && (operand_->typeName() == typeid_of(ValueType).name())
	        ? &static_cast<Any::Holder<ValueType>*>(operand_->content)->held_ : NULL;
}

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B�|�C���^�Econst �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
template<typename ValueType>
const ValueType* any_cast(const Any* operand_) throw () {
	return any_cast<ValueType>(const_cast<Any*>(operand_));
}

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B���t�@�����X�Enon-const �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
//! \except     bad_any_cast    template �p�����[�^�Ɏw�肳�ꂽ�^�ɕϊ��ł��Ȃ�
template<typename ValueType>
ValueType any_cast(Any& operand_) throw (bad_any_cast) {
	typedef typename TypeTraits<ValueType>::ReferenceRemovedType nonref;
	nonref* result = any_cast<nonref>(&operand_);
	if(!result) {
		throw bad_any_cast(
#if (Any_ALONETEST == 0)
				std::string("Exception is thrown!!\nmessage: "
				    + std::string("bad_any_cast") + "\nfile: "
				    + ::pm_mode::lexical_cast<std::string>(__FILE__)
				    + "\nline: " + ::pm_mode::lexical_cast<std::string>(__LINE__)
				    + "\nfunction: " + ::pm_mode::lexical_cast<std::string>(__FUNCTION__)
				    + "\nmessage: MyType is " + this->typeName() + ", ValueType is " + typeid_of(ValueType).name()
				    + "\n")
#else
			""
#endif
			);
	}
	return *result;
}

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B���t�@�����X�Econst �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
//! \except     bad_any_cast    template �p�����[�^�Ɏw�肳�ꂽ�^�ɕϊ��ł��Ȃ�
template<typename ValueType>
ValueType any_cast(const Any& operand_) throw (bad_any_cast) {
	typedef typename RemoveReference<ValueType>::type nonref;
	return any_cast<const nonref&>(const_cast<Any&>(operand_));
}


}   // namespace pm_mode



/*
//---------------------------------------------------------
// �g�p��
//---------------------------------------------------------


class Sample {
public:

	static const unsigned int typeID = 0;       //!< �^ID

	//!< brief �^ ID ��Ԃ�
	unsigned int dataTypeID() const { return Sample::typeID; }

	//! \brief constructor
	//! \param[in]  integer     �f�[�^
	Sample(int integer_ = std::numeric_limits<int>::max()) : integer(integer_) {}

	int integer;
};

int main()
{
	int count = 0;

	pm_mode::Any any = Sample(34);
	pm_mode::Any& anyArias = any;

	std::cout << ++count << " => " << pm_mode::any_cast<Sample>(any).integer << std::endl;
	std::cout << ++count << " => " << any.getAs<Sample>().integer << std::endl;
	std::cout << ++count << " => " << anyArias.getAs<Sample>().integer << std::endl;

	Sample sample = pm_mode::any_cast<Sample>(anyArias);
	std::cout << ++count << " => " << sample.integer << std::endl;

	Sample& sampleArias = sample;
	pm_mode::Any sampleArias_any = pm_mode::Any(sampleArias);
	std::cout << ++count << " => " << sampleArias_any.getAs<Sample>().integer << std::endl;
}




*/

#endif
