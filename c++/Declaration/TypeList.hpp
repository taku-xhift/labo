/**
 * @file  TypeList.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.06.22 11:02:50
 *
 * @version 1.00, Shishido Takuya, 2012.06.22 11:02:50
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef TYPELIST_HPP_INCLUDED
#define TYPELIST_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include <boost/mpl/list.hpp>


class Type;

typedef boost::mpl::list<
    int,
    Type
> TypeList;


struct TypeListHolder {
	TypeList list;
};


#endif

