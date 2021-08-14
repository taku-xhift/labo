// See http://www.boost.org/libs/any for Documentation.

#include <iostream>
#include <algorithm>
#include <limits>
#include <assert.h>


namespace pm {
namespace pc {
namespace Task {

class Any;


//! brief �L���X�g���s���������߂̗�O�N���X
class bad_any_cast;



//! brief �C�ӌ^�f�[�^��ۑ�����N���X
class Any
{
	static const unsigned int defaultID = UINT_MAX;//std::numeric_limits<unsigned int>::max();
public:

	//! \brief constructor
	Any() : content(NULL) {}

	//! \brief constructor
	//! \param[in]  value_  �C�ӌ^�̃f�[�^
	template<typename ValueType>
	Any(const ValueType& value_)
		: content(new Holder<ValueType>(value_))
	{
	}

	//! \brief constructor
	//! \param[in]  value_  �C�ӌ^�̃f�[�^
	Any(const Any& other_)
		: content(other_.content ? other_.content->clone() : NULL)
	{
	}

	//! \brief destructor
	~Any() {
		delete content;
	}

public:

	//! \brief ������� Any �Ǝ����̃f�[�^����ւ�
	//! \param[in]  rhs_    ����ւ���
	Any& swap(Any& rhs_) {
		std::swap(this->content, rhs_.content);
		return *this;
	}

	//! \brief operator = (�f�[�^�{�̂� = �łȂ�)
	//! \param[in]  rhs_    ����ւ���
	template<typename ValueType>
	Any& operator=(const ValueType& rhs_) {
		Any(rhs_).swap(*this);
		return *this;
	}

	//! \brief operator = (Any �^�̃f�[�^�Ƃ� =)
	//! \param[in]  rhs_    Any �^�̃f�[�^
	Any& operator=(Any rhs_) {
		rhs_.swap(*this);
		return *this;
	}

public:

	//! \brief �f�[�^�̗L���̃`�F�b�N
	//! \retval     true    �L��
	//! \retval     false   ����
	bool empty() const { return !this->content; }

	//! \brief �����Ă���f�[�^�� typeID ��Ԃ�
	//! \return     �^���Ƀ��j�[�N�� ID�B�Ȃ���� default �� ID (Any �^���Œ�`)
	unsigned int dataTypeID() const             { return content ? content->dataTypeID() : defaultID; }

	//! \brief �����Ƀf�[�^���Z�b�g����Ă��Ȃ��ꍇ�̃f�t�H���g�� ID ���擾
	unsigned int defaultDataTypeID() const      { return Any::defaultID; }

	//! \breif cast ���ē����f�[�^���擾����(��O���g���Ȃ��l�͂����)
	//! \return    �L���X�g�ς݂̃f�[�^�B�L���X�g�o���Ȃ���� NULL(���S�ł͂Ȃ�)
	template<typename ValueType>
	const ValueType& getAs() const throw(bad_any_cast) {
		if (this->content->dataTypeID() != ValueType::typeID) {
			assert(0);
			throw bad_any_cast();
		}
		return static_cast<Holder<ValueType>*>(this->content)->held;
	}

	//! \brief cast �ς݂̃f�[�^���擾����(�n�����f�[�^�^�Ɏ����ŕϊ�)
	//! \param[out] out_    �f�[�^�o�͐�
	//! \retval     true    �L���X�g�\������
	//! \retval     false   �L���X�g�s�\������
	template<typename ValueType>
	bool store(ValueType& out_) {
		if (this->content.dataTypeID() != ValueType::typeID) {
			return false;
		}
		out_ = static_cast<Holder<ValueType>*>(this->content)->held;
		return true;
	}


private:

	//! brief �f�[�^�z���_�[�̃C���^�[�t�F�[�X�^
	class PlaceHolder
	{
	public:

		//! \brief destructor
		virtual ~PlaceHolder() {}

		//! \brief �����Ă���f�[�^�� typeID ��Ԃ�
		//! \return     �^���Ƀ��j�[�N�� ID�B�Ȃ���� default �� ID (Any �^���Œ�`)
		virtual unsigned int dataTypeID() const = 0;

		//! \brief �f�[�^�̃N���[����Ԃ�
		virtual PlaceHolder* clone() const = 0;
	};

	//! \brief �f�[�^�z���_�[�̎���
	template<typename ValueType>
	class Holder
		: public PlaceHolder
	{
	public:

		//! \brief copy constructor
		Holder(const ValueType& value_)
			: held(value_)
		{
		}

		//! \brief �f�[�^�� ID �擾
		//! \return     �^ ID
		virtual unsigned int dataTypeID() const {
			return held.dataTypeID();
		}

		//! \brief �f�[�^�{�̂̃R�s�[
		//! \return     new �����l
		virtual PlaceHolder* clone() const {
			return new Holder(held);
		}

	public:

		ValueType held;     //!< �f�[�^�{��

	private:
		//! \brief operator = �̋֎~
		Holder& operator=(const Holder &);
	};

private:

	//! \brief cast �֐��ɑ΂���f�[�^�̌��J
	template<typename ValueType>
	friend ValueType* any_cast(Any*);

	PlaceHolder* content;   //!< �C�ӌ^��ۑ����邽�߂̃f�[�^�z���_�[
};

//! brief �L���X�g���s���������߂̗�O�N���X
class bad_any_cast : public std::bad_cast {
public:
	//! \brief ��O�����擾����
	//! return ��O���
	virtual const char* what() const throw() {
		return "boost::bad_any_cast: "
		       "failed conversion using boost::any_cast";
	}
};

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B�|�C���^�Enon-const �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
template<typename ValueType>
ValueType* any_cast(Any* operand_) {
	return operand_ && (operand_->dataTypeID() == ValueType::typeID)
	        ? &static_cast<Any::Holder<ValueType>*>(operand_->content)->held : NULL;
}

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B�|�C���^�Econst �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
template<typename ValueType>
inline const ValueType* any_cast(const Any* operand_) {
	return any_cast<ValueType>(const_cast<Any*>(operand_));
}

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B���t�@�����X�Enon-const �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
template<typename ValueType>
ValueType any_cast(Any& operand_) {
	ValueType* result = any_cast<ValueType>(&operand_);
	if(!result) {
		throw;
	}
	return *result;
}

//! \brief Any �^����L���X�g���邽�߂̃��\�b�h�B���t�@�����X�Econst �p�B
//! \param[in]  operand_    ���o������ Any �^�̃I�u�W�F�N�g
//! \return     �ϊ��ς݃f�[�^�B���s����� NULL �^�f�[�^
template<typename ValueType>
inline ValueType any_cast(const Any& operand_) {
	typedef remove_reference<ValueType>::type nonref;
	return any_cast<const nonref &>(const_cast<Any&>(operand_));
}


}   // Task
}   // pc
}   // pm

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
	pm::pc::Task::Any any = Sample(34);

	std::cout << pm::pc::Task::any_cast<Sample>(any).integer << std::endl;
	std::cout << any.getAs<Sample>().integer << std::endl;
}


