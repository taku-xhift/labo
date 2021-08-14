
#ifndef PM_MODE_TYPE_TRAITS_TYPETRAITS_HPP_INCLUDED
#define PM_MODE_TYPE_TRAITS_TYPETRAITS_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------


namespace pm_mode {


template<typename T>
class TypeTraits
{
private:


	// Determine if type is const
	template <class U> struct UnConst {
		typedef U Result;
		static const int isConst = 0;
	};

	template <class U> struct UnConst<const U> {
		typedef U Result;
		static const int isConst = 1;
	};

	template <class U> struct UnConst<const U&> {
		typedef U& Result;
		static const int isConst = 1;
	};


	// Remove Const
	template<typename T>
	struct RemoveConst {
		typedef T Type;
	};
	template<typename T>
	struct RemoveConst<const T> {
		typedef T Type;
	};
	template<typename T>
	struct RemoveConst<const T[]> {
		typedef T Type[];
	};
	template<typename T, unsigned size>
	struct RemoveConst<const T[size]> {
		typedef T Type[size];
	};


	// Remove Reference
	template<typename T>
	struct RemoveReference {
		typedef T Type;
	};
	template<typename T>
	struct RemoveReference<T&> {
		typedef T Type;
	};

public:

	static const int isConst = UnConst<T>::isConst;

	typedef typename RemoveConst<T>::Type ConstRemovedType;
	typedef typename RemoveReference<T>::Type ReferenceRemovedType;
};



}    // namespace pm_mode


#endif

