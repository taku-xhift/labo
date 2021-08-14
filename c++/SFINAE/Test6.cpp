
#include <iostream>
#include <boost/static_assert.hpp>


//! \brief �����o�֐��`�F�b�J�[
//! \note   void setData(T t_) �̂悤�Ȋ֐�������� value �� true
template<typename T, typename U>
class has_setData_checker {
	typedef char (&No)[1];      //!< No  �p�^�O
	typedef char (&Yes)[2];     //!< Yes �p�^�O

	// ���� Yes No ����p�̃w���p�[�Q�B
	// ������͂��܂Ȃ��� setData �������Ă��Ȃ��N���X��n���ƃR���p�C���G���[���N���Ă��܂�
	// setData �������Ă��Ȃ��f�[�^���n���ăR���p�C���ł��Ȃ���
	// �����Ă���N���X�Ƃ���ȊO�̃N���X�ŏ����̕��򂪍��Ȃ�
	template < typename T, typename U, void (T::*)(U) >         struct memberFunction1 {};
	template < typename T, typename U, void (T::*)(U*) >        struct memberFunciton2 {};
	template < typename T, typename U, void (T::*)(const U*) >  struct memberFunction3 {};
	template < typename T, typename U, void (T::*)(U&) >        struct memberFunction4 {};
	template < typename T, typename U, void (T::*)(const U&) >  struct memberFunction5 {};

	// ����{�́B�֐��錾�B
	// ��L�� memberFunction �Q�ꗗ�ɂ���\���ɂȂ��Ă���� Yes ���B
	// �����łȂ���� No �^��Ԃ��֐��ɂȂ�B
	template< typename T, typename U > static No  has_setData_checker_helper(...);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction1< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunciton2< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction3< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction4< T,U,&T::setData >*);
	template< typename T, typename U > static Yes has_setData_checker_helper(memberFunction5< T,U,&T::setData >*);

public:
	// setData �����o�֐��������Ă���� true �������Ă���
	static const bool value =
		sizeof(has_setData_checker_helper<T,U>(0)) == sizeof(Yes);
};

using namespace std;

struct Data {
};

struct WithDefaultType {
	typedef Data requestDataType;
	void setData(requestDataType value_) {
		cout << "setData(requestDataType value_)" << endl;
		this->value = value_;
	}
	Data value;
};

struct WithPointerType {
	typedef Data requestDataType;
	void setData(requestDataType* value_) {
		cout << "setData(requestDataType* value_)" << endl;
		this->value = *value_;
	}
	Data value;
};

struct WithConstPointerType {
	typedef Data requestDataType;
	void setData(const requestDataType* value_) {
		cout << "setData(const requestDataType* value_)" << endl;
		this->value = *value_;
	}
	Data value;
};

struct WithConstReferenceType {
	typedef Data requestDataType;
	void setData(const requestDataType& value_) {
		cout << "setData(const requestDataType& value_)" << endl;
		this->value = value_;
	}
	Data value;
};





int main() {
	BOOST_STATIC_ASSERT((has_setData_checker<WithDefaultType, WithDefaultType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithPointerType, WithPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstPointerType, WithConstPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstReferenceType, WithConstReferenceType::requestDataType>::value));

	//their their_;
	//their_.setData(her());
}

