
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <functional>


//-----------------------------------------------------
//  define
//-----------------------------------------------------

//! \brief �^�����擾����B�g�p��͈�ԉ��B
//! \note   name() ���̃A�N�Z�X���@�� type_info �ƕς��Ȃ�
//! \note   ���̃N���X��`�Ȃǂ͂�����g�����߂̕��Ȃ̂ł��� define �����m���Ă�Ώ[��
//! \return sp_typeinfo �^�ŁA
//!             typeid_of(Type).name() �� �N���X���� "�܂�" ������B
//!             ��̓I�ȓ��e�̓R���p�C���� __FUNCTION__ �ɂ��B
#define typeid_of(...) (::pm_mode::sp_typeid_<__VA_ARGS__ >::typeinfo)
#define VA_ARGTEST(...) (__VA_ARGS__)





namespace pm_mode {


//! \brief type_info �N���X�ɕς��^���N���X
class sp_typeinfo
{
public:

	//! \brief constructor
	//! \param[in]  name    �N���X��
	explicit sp_typeinfo(const char* const name) throw()
		: name_(name)
	{
	}

	//! \brief operator == (���l����)
	bool operator==(sp_typeinfo const& rhs) const throw() {
		return (this == &rhs);
	}

	//! \brief operator != (�s��v����)
	bool operator!=(sp_typeinfo const& rhs) const throw() {
		return (this != &rhs);
	}

	//! \brief �h���֌W�͂�����g�p���Ē��ׂ�
	//! \note   type_info �ɃC���^�[�t�F�[�X�����킹�Ă���
	bool before(sp_typeinfo const& rhs) const throw() {
		return std::less< sp_typeinfo const* >()(this, &rhs);
	}

	//! \brief ���O�擾
	const char* name() const throw()        { return this->name_; }

private:

	//! \brief copy constructor �̋֎~
	sp_typeinfo(sp_typeinfo const&);
	//! \brief ����̋֎~
	sp_typeinfo& operator=(sp_typeinfo const&);

	const char* const name_;      //!< �^�Ɋւ��閼�O
};

//! \brief �w�肳�ꂽ�^�̖��O�𐶐�����
//! \note   �^���ƂɃ��j�[�N�� ID �𐶐�������@�̊j�S
//              template �Ŏw�肳�ꂽ�^�� __FUNCTION__ �̏��Ɋ܂܂��̂�
//              �N���X���Ƃ̃��j�[�N�Ȗ��O�������ł���B
//              ���������̓��e�̓R���p�C���ˑ�(__FUNCTION__ �ɂ��)�B
template<typename T> struct sp_typeid_
{
	//! \brief ���O���擾����
	//! \note
	//! \return     template �Ɏw�肳�ꂽ�^�̖��O���܂ޕ�����
	static const char* const name() {
		return __FUNCTION__;
	}

	static sp_typeinfo typeinfo;    //!< �^���i�[��B�w�b�_�ɃI�u�W�F�N�g��u�����߂̃e�N�j�b�N�B
};


//! \brief �O���[�o���ɍ��^�̏����܂ރI�u�W�F�N�g
//! \note   Any �^�Ɋi�[������ޕ������I�u�W�F�N�g�����������B
template<typename Type> sp_typeinfo sp_typeid_<Type>::typeinfo(sp_typeid_<Type>::name());


//! \brief �ȉ��Atemplate �̓��ꉻ
template<typename Type> struct sp_typeid_<Type&>
	: sp_typeid_<Type>
{
};

template<typename Type> struct sp_typeid_<Type const>
	: sp_typeid_<Type>
{
};

template<typename Type> struct sp_typeid_<Type volatile>
	: sp_typeid_<Type>
{
};

template<typename Type> struct sp_typeid_<Type const volatile>
	: sp_typeid_<Type>
{
};


}    // namespace pm_mode




template<typename ValueType>
class Test {
public:
	ValueType integer;
};


int main() {
	std::cout << typeid_of(Test<int>).name() << std::endl;
	//std::cout << VA_ARGTEST(Test<int>) << std::endl;
}

