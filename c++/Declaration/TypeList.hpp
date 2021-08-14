
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

