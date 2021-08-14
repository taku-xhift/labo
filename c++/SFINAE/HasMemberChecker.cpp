
#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>


// �Q�l
//http://lists.boost.org/Archives/boost/2002/03/27276.php


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
	// ��L�� memberFunction �Q�ꗗ�ɂ���\���ɂȂ��Ă���� Yes ���A
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

struct WithNoTypedef {
	void setData(const Data& value_) {
		cout << "setData(const requestDataType& value_)" << endl;
		this->value = value_;
	}
	Data value;
};




template<typename Collector, typename Data>
void setData(Collector& collector_, Data& data_, typename boost::enable_if<has_setData_checker<Collector, typename Collector::requestDataType> >::type* = 0) {
	cout << "setData(Collector& type_, Data& data_, boost::enable_if<has_setData_checker<Type> >* = 0, ...)" << endl;
}

template<typename Collector, typename Data>
void setData(Collector& type_, Data& data, ...) {
	BOOST_STATIC_ASSERT((!has_setData_checker<Collector, Data>::value));
	cout << "setData(Collector& type_, ...)" << endl;
}


int main() {
	BOOST_STATIC_ASSERT((has_setData_checker<WithDefaultType, WithDefaultType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithPointerType, WithPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstPointerType, WithConstPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_setData_checker<WithConstReferenceType, WithConstReferenceType::requestDataType>::value));

	static const bool checker = has_setData_checker<WithConstReferenceType, typename WithConstReferenceType::requestDataType>::value;
	cout << "checker = " << checker << "\n" << endl;
	cout << typeid(boost::enable_if<has_setData_checker<WithConstReferenceType, typename WithConstReferenceType::requestDataType> >::type).name() << endl;


	static const bool checkerWithNoTypedef = has_setData_checker<WithNoTypedef, Data>::value;
	cout << "checkerWithNoTypedef = " << checkerWithNoTypedef << "\n" << endl;



	WithConstReferenceType value;
	Data data;
	setData(value, data);

	WithNoTypedef noTypedef;
	setData(noTypedef, data);

	class temp_ {
	} temp;

	static const bool checkerTemp_ = has_setData_checker<temp_, Data>::value;
	cout << "checkerTemp_ = " << checkerTemp_ << "\n" << endl;

	setData(temp, data);
	//their their_;
	//their_.setData(her());
}

