
#ifndef PM_PC_TASK_SPTYPEINFO_HPP_INCLUDED
#define PM_PC_TASK_SPTYPEINFO_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

#include <iostream>
#include <functional>

namespace pm {
namespace pc {
namespace Task {

class sp_typeinfo
{
public:

	explicit sp_typeinfo(const char* name): name_(name)    {}

	bool operator==(sp_typeinfo const& rhs) const {
		return (this == &rhs);
	}

	bool operator!=(sp_typeinfo const& rhs) const {
		return (this != &rhs);
	}

	bool before(sp_typeinfo const& rhs) const {
		return std::less< sp_typeinfo const* >()(this, &rhs);
	}

	const char* name() const        { return this->name_; }

private:

	sp_typeinfo(sp_typeinfo const&);
	sp_typeinfo& operator=(sp_typeinfo const&);

	const char* name_;
};

template<class T> struct sp_typeid_
{
	static sp_typeinfo typeinfo;

	static const char* name() {
		return __FUNCTION__;
	}
};

template<class T> sp_typeinfo sp_typeid_< T >::typeinfo(sp_typeid_<T>::name());

template<class T> struct sp_typeid_<T&>
	: sp_typeid_< T >
{
};

template<class T> struct sp_typeid_<T const>
	: sp_typeid_< T >
{
};

template<class T> struct sp_typeid_<T volatile>
	: sp_typeid_< T >
{
};

template<class T> struct sp_typeid_<T const volatile>
	: sp_typeid_< T >
{
};


}    // namespace Task
}    // namespace pc
}    // namespace pm




#define typeid_of(T) (pm::pc::Task::sp_typeid_<T>::typeinfo)

//
//template<typename ValueType>
//class Test {
//public:
//	ValueType integer;
//};
//
//
//int main() {
//	Test<int> test;
//	std::cout << typeid_of(Test<int>).name() << std::endl;
//}



#endif
