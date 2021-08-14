

#include <iostream>
#include <boost/static_assert.hpp>

typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template < typename T, typename U, void (T::*)(U) >         struct op_mf1 {};
template < typename T, typename U, void (T::*)(U*) >        struct op_mf2 {};
template < typename T, typename U, void (T::*)(const U*) >  struct op_mf3 {};
template < typename T, typename U, void (T::*)(U&) >        struct op_mf4 {};
template < typename T, typename U, void (T::*)(const U&) >  struct op_mf5 {};

template< typename T, typename U > no_tag has_plus_assignment_helper(...);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf1< T,U,&T::setData >*);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf2< T,U,&T::setData >*);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf3< T,U,&T::setData >*);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf4< T,U,&T::setData >*);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf5< T,U,&T::setData >*);


template< typename T, typename U = T >
struct has_plus_assignment
{
	static const bool value =
		sizeof(has_plus_assignment_helper<T,U>(0)) == sizeof(yes_tag);
};


struct my {};
struct her { void setData(int); };
struct their {
public:
	typedef her requestDataType;

	void setData(const her& her_) {
		this->her_ = her_;
		std::cout << __FUNCTION__ << std::endl;
	}
	her her_;
};

struct Data {
};

struct WithDefaultType {
	typedef int requestDataType;
	void setData(requestDataType value_);
};

struct WithPointerType {
	typedef Data requestDataType;
	void setData(requestDataType* value_);
};

struct WithConstPointerType {
	typedef Data requestDataType;
	void setData(const requestDataType* value_);
};

struct WithConstReferenceType {
	typedef Data requestDataType;
	void setData(const requestDataType& value_);
};



int main() {
	BOOST_STATIC_ASSERT((has_plus_assignment<WithDefaultType, WithDefaultType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_plus_assignment<WithPointerType, WithPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_plus_assignment<WithConstPointerType, WithConstPointerType::requestDataType>::value));
	BOOST_STATIC_ASSERT((has_plus_assignment<WithConstReferenceType, WithConstReferenceType::requestDataType>::value));

	//their their_;
	//their_.setData(her());
}

