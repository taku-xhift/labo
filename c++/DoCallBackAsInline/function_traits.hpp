//  Copyright 2000 John Maddock (john@johnmaddock.co.uk)
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.
//
//
//
//  Copyright 2004 Cryolite (cryolite@bb.wakwak.com)
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#if !defined(CRY_FUNCTION_TRAITS_HPP_INCLUDE_GUARD)
#define CRY_FUNCTION_TRAITS_HPP_INCLUDE_GUARD

#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

namespace cry{

namespace detail{

template<class Function> struct function_traits_helper;

template<typename R>
struct function_traits_helper<R (*)(void)>
{
  BOOST_STATIC_CONSTANT(int, arity = 0);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
};

template<typename R, typename T1>
struct function_traits_helper<R (*)(T1)>
{
  BOOST_STATIC_CONSTANT(int, arity = 1);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T1 argument_type;
};

template<typename R, typename T1, typename T2>
struct function_traits_helper<R (*)(T1, T2)>
{
  BOOST_STATIC_CONSTANT(int, arity = 2);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T1 first_argument_type;
  typedef T2 second_argument_type;
};

template<typename R, typename T1, typename T2, typename T3>
struct function_traits_helper<R (*)(T1, T2, T3)>
{
  BOOST_STATIC_CONSTANT(int, arity = 3);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4>
struct function_traits_helper<R (*)(T1, T2, T3, T4)>
{
  BOOST_STATIC_CONSTANT(int, arity = 4);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5)>
{
  BOOST_STATIC_CONSTANT(int, arity = 5);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6)>
{
  BOOST_STATIC_CONSTANT(int, arity = 6);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7)>
{
  BOOST_STATIC_CONSTANT(int, arity = 7);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8)>
{
  BOOST_STATIC_CONSTANT(int, arity = 8);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
{
  BOOST_STATIC_CONSTANT(int, arity = 9);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9,
         typename T10>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
{
  BOOST_STATIC_CONSTANT(int, arity = 10);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
  typedef T10 arg10_type;
};

template<class R, class X>
struct function_traits_helper<R (X::*)(void)>
{
  BOOST_STATIC_CONSTANT(int, arity = 0);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
};

template<class R, class X, class T1>
struct function_traits_helper<R (X::*)(T1)>
{
  BOOST_STATIC_CONSTANT(int, arity = 1);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T1 argument_type;
};

template<class R, class X, class T1, class T2>
struct function_traits_helper<R (X::*)(T1, T2)>
{
  BOOST_STATIC_CONSTANT(int, arity = 2);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T1 first_argument_type;
  typedef T2 second_argument_type;
};

template<class R, class X, class T1, class T2, class T3>
struct function_traits_helper<R (X::*)(T1, T2, T3)>
{
  BOOST_STATIC_CONSTANT(int, arity = 3);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
};

template<class R, class X, class T1, class T2, class T3, class T4>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4)>
{
  BOOST_STATIC_CONSTANT(int, arity = 4);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5)>
{
  BOOST_STATIC_CONSTANT(int, arity = 5);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6)>
{
  BOOST_STATIC_CONSTANT(int, arity = 6);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7)>
{
  BOOST_STATIC_CONSTANT(int, arity = 7);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7, class T8>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7, T8)>
{
  BOOST_STATIC_CONSTANT(int, arity = 8);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7, class T8, class T9>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
{
  BOOST_STATIC_CONSTANT(int, arity = 9);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7, class T8, class T9,
         class T10>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
{
  BOOST_STATIC_CONSTANT(int, arity = 10);
  BOOST_STATIC_CONSTANT(bool, is_const = false);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
  typedef T10 arg10_type;
};

template<class R, class X>
struct function_traits_helper<R (X::*)(void) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 0);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
};

template<class R, class X, class T1>
struct function_traits_helper<R (X::*)(T1) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 1);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T1 argument_type;
};

template<class R, class X, class T1, class T2>
struct function_traits_helper<R (X::*)(T1, T2) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 2);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T1 first_argument_type;
  typedef T2 second_argument_type;
};

template<class R, class X, class T1, class T2, class T3>
struct function_traits_helper<R (X::*)(T1, T2, T3) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 3);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
};

template<class R, class X, class T1, class T2, class T3, class T4>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 4);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 5);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 6);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 7);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7, class T8>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7, T8) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 8);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7, class T8, class T9>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7, T8, T9) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 9);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
};

template<class R, class X, class T1, class T2, class T3, class T4,
         class T5, class T6, class T7, class T8, class T9,
         class T10>
struct function_traits_helper<R (X::*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const>
{
  BOOST_STATIC_CONSTANT(int, arity = 10);
  BOOST_STATIC_CONSTANT(bool, is_const = true);
  typedef R result_type;
  typedef X class_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
  typedef T10 arg10_type;
};

} // namespace detail

template<class Function>
struct function_traits :
  public ::boost::mpl::eval_if<
    ::boost::is_member_function_pointer<Function>,
    ::boost::mpl::identity<detail::function_traits_helper<Function> >,
    ::boost::mpl::eval_if<
      ::boost::is_pointer<Function>,
      ::boost::mpl::identity<detail::function_traits_helper<Function> >,
      ::boost::mpl::identity<
        detail::function_traits_helper<
          typename ::boost::add_pointer<Function>::type
        >
      >
    >
  >::type
{ };

} // namespace cry

#endif // CRY_MEMBER_FUNCTION_TRAITS_HPP_INCLUDE_GUARD
