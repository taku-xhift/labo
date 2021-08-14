

#include <boost/static_assert.hpp>

//
//typedef char (&no_tag)[1];
//typedef char (&yes_tag)[2];
//
//template < typename T, typename U, void (T::*)(U const&) > struct ptmf_helper {};
//template< typename T , typename U> no_tag has_member_foo_helper(...);
//
//template< typename T , typename U>
//yes_tag has_member_foo_helper(ptmf_helper<T, U, &(T::foo)(U const&)>* p);
//
//template< typename T >
//struct has_member_foo
//{
//	static const bool value =
//		sizeof(has_member_foo_helper<T>(0)) == sizeof(yes_tag);
//};
//
//struct my {};
//struct her {
//public:
//	typedef int value_type;
//	void foo(const value_type& value_);
//};
//
//
//int main() {
//	BOOST_STATIC_ASSERT(!has_member_foo<my>::value);
//	BOOST_STATIC_ASSERT(has_member_foo<her>::value);
//}
//

//=================================================================================
//
//typedef char (&no_tag)[1];
//typedef char (&yes_tag)[2];
//
//template < typename T, typename U, T (T::*)(U) > struct op_mf1 {};
//template < typename T, typename U, T& (T::*)(U) > struct op_mf2 {};
//template < typename T, typename U, T (T::*)(U const&) > struct op_mf3 {};
//template < typename T, typename U, T& (T::*)(U const&) > struct op_mf4 {};
//
//template< typename T, typename U > no_tag has_plus_assignment_helper(...);
//template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf1< T,U,&T::operator+= >*);
//template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf2< T,U,&T::operator+= >*);
//template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf3< T,U,&T::operator+= >*);
//template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf4< T,U,&T::operator+= >*);
//
//template< typename T, typename U = T >
//struct has_plus_assignment
//{
//	static const bool value =
//		sizeof(has_plus_assignment_helper<T,U>(0)) == sizeof(yes_tag);
//};
//
//struct my {};
//struct her { her& operator+=(int); };
//struct their { their& operator+=(their const&); };
//
//int main() {
//	BOOST_STATIC_ASSERT((!has_plus_assignment<my,int>::value));
//	BOOST_STATIC_ASSERT((has_plus_assignment<her,int>::value));
//	BOOST_STATIC_ASSERT((has_plus_assignment<their>::value));
//}
//
//========================================================================================================


typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template < typename T, typename U, void (T::*)(U) > struct op_mf1 {};
//template < typename T, typename U, void (T::*)(U) > struct op_mf2 {};
template < typename T, typename U, void (T::*)(U const&) > struct op_mf3 {};
//template < typename T, typename U, void (T::*)(U const&) > struct op_mf4 {};

template< typename T, typename U > no_tag has_plus_assignment_helper(...);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf1< T,U,&T::setData >*);
//template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf2< T,U,&T::setData >*);
template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf3< T,U,&T::setData >*);
//template< typename T, typename U > yes_tag has_plus_assignment_helper(op_mf4< T,U,&T::setData >*);

template< typename T, typename U = T >
struct has_plus_assignment
{
	static const bool value =
		sizeof(has_plus_assignment_helper<T,U>(0)) == sizeof(yes_tag);
};

struct my {};
struct her { void setData(int); };
struct their { void setData(const her&); };

int main() {
	BOOST_STATIC_ASSERT((!has_plus_assignment<my,int>::value));
	BOOST_STATIC_ASSERT((has_plus_assignment<her,int>::value));
	BOOST_STATIC_ASSERT((has_plus_assignment<their, her>::value));
}

