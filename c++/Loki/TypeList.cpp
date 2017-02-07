


#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

using namespace std;


struct EmptyType {};
class NullType {};


template<typename Head, typename Tail>
struct Typelist {
	Head head;
	Tail tail;
};


#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) Typelist<T1, TYPELIST_4(T2, T3, T4, T5)>


typedef TYPELIST_4(signed char, short int, int, long int) SignedIntegrals;




// Length  ////////////////////////////////////////////////
template<typename TypeList> struct Length;

template<>
struct Length<NullType> {
	static const int value = 0;
};

template<typename T, typename U>
struct Length< Typelist<T, U> >
{
	static const int value = 1 + Length<U>::value;
};


// TypeAt  ////////////////////////////////////////////////
template <typename TypeList, unsigned int index> struct TypeAt;

template<typename Head, typename Tail>
struct TypeAt<Typelist<Head, Tail>, 0>
{
	typedef Head Result;
};

template<typename Head, typename Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i> {
	typedef typename TypeAt<Tail, i-1>::Result Result;
};


// IndexOf  ///////////////////////////////////////////////
template<typename TypeList, typename T>
struct IndexOf;

template<typename T>
struct IndexOf<NullType, T> {
	static const int value = -1;
};

template<typename T, typename Tail>
struct IndexOf<Typelist<T, Tail>, T> {
	static const int value = 0;
};

template<typename Head, typename Tail, typename T>
struct IndexOf<Typelist<Head, Tail>, T> {
private:
	static const int temp = IndexOf<Tail, T>::value;
public:
	static const int value = (temp == -1)? -1 : 1 + temp;
};


// Append  ////////////////////////////////////////////////
template<typename Typelist, typename T>
struct Append;

template<>
struct Append<NullType, NullType> {
	typedef NullType Result;
};

template<typename T>
struct Append<NullType, T> {
	typedef TYPELIST_1(T) Result;
};

template<typename Head, typename Tail>
struct Append<NullType, Typelist<Head, Tail> > {
	typedef Typelist<Head, Tail> Result;
};

template<typename Head, typename Tail, typename T>
struct Append<Typelist<Head, Tail>, T> {
	typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
};

typedef Append<SignedIntegrals, TYPELIST_3(float, double, long double)>::Result SignedTypes;


// Erase //////////////////////////////////////////////////
template<typename Typelist, typename T>
struct Erase;

template <typename T>
struct Erase<NullType, T> {
	typedef NullType Result;
};

template<typename T, typename Tail>
struct Erase<Typelist<T, Tail>, T> {
	typedef Tail Result;
};

template<typename Head, typename Tail, typename T>
struct Erase<Typelist<Head, Tail>, T> {
	typedef Typelist<Head, typename Erase<Tail, T>::Result> Result;
};


// EraseAll  //////////////////////////////////////////////
template<typename Typelist, typename T>
struct EraseAll;

template<typename T>
struct EraseAll<NullType, T> {
	typedef NullType Result;
};

template<typename T, typename Tail>
struct EraseAll<Typelist<T, Tail>, T> {
	typedef typename EraseAll<Tail, T>::Result Result;
};

template<typename Head, typename Tail, typename T>
struct EraseAll<Typelist<Head, Tail>, T> {
	typedef Typelist<Head, typename EraseAll<Tail, T>::Result> Result;
};


// NoDuplicates  //////////////////////////////////////////
template<typename Typelist>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
	typedef NullType Result;
};

template<typename Head, typename Tail>
struct NoDuplicates< Typelist<Head, Tail> > {
private:
	typedef typename NoDuplicates<Tail>::Result L1;
	typedef typename Erase<L1, Head>::Result    L2;
public:
	typedef Typelist<Head, L2> Result;
};


// Replace  ///////////////////////////////////////////////
template<typename Typelist, typename T, typename U>
struct Replace;

template<typename T, typename U>
struct Replace<NullType, T, U> {
	typedef NullType Result;
};

template<typename Tail, typename T, typename U>
struct Replace<Typelist<T, Tail>, T, U> {
	typedef Typelist<U, Tail> Result;
};

template<typename Head, typename Tail, typename T, typename U>
struct Replace<Typelist<Head, Tail>, T, U> {
	typedef typename Replace<Tail, T, U>::Result Result;
};

// ReplaceAll  ////////////////////////////////////////////
template<typename Typelist, typename T, typename U>
struct ReplaceAll;

template<typename T, typename U>
struct ReplaceAll<NullType, T, U> {
	typedef NullType Result;
};

template<typename Tail, typename T, typename U>
struct ReplaceAll<Typelist<T, Tail>, T, U> {
	typedef Typelist<U, typename ReplaceAll<Tail, T, U>::Result> Result;
};

template<typename Head, typename Tail, typename T, typename U>
struct ReplaceAll<Typelist<Head, Tail>, T, U> {
	typedef typename Typelist<Head, typename ReplaceAll<Tail, T, U>::Result> Result;
};

typedef TYPELIST_3(int, int, double) DoubleInt;
typedef ReplaceAll<DoubleInt, int, float>::Result DoubleFloat;



// Select  ////////////////////////////////////////////////
template<bool flag, typename T, typename U>
struct Select {
	typedef T Result;
};

template<typename T, typename U>
struct Select<false, T, U> {
	typedef U Result;
};


// SUPERSUBCLASS  /////////////////////////////////////////

template<typename T, typename U>
class Conversion {
	typedef char yes;
	struct no { char dummy[2]; };
	static yes helper(U);
	static no  helper(...);
	static T makeT();
public:
	enum { exists = sizeof(helper(makeT())) == sizeof(no),
	       sameType = false };
};

template<typename T>
class Conversion<T, T> {
public:
	enum { exists = 1, sameType = true, };
};

#define SUPERSUBCLASS(T, U) \
	(Conversion<const U*, const T*>::exists && \
	 !Conversion<const T*, const void*>::sameType)


// MostDerived  ///////////////////////////////////////////
template<typename Typelist, typename T>
struct MostDerived;

template<typename T>
struct MostDerived<NullType, T> {
	typedef T Result;
};

template<typename Head, typename Tail, typename T>
struct MostDerived<Typelist<Head, Tail>, T> {
private:
	typedef typename MostDerived<Tail, T>::Result Candicate;
public:
	typedef typename Select<
		SUPERSUBCLASS(Candicate, Head),
			Head, Candicate>::Result Result;
};

// DerivedToFront  ////////////////////////////////////////
template<typename T>
struct DerivedToFront;

template<>
struct DerivedToFront<NullType> {
	typedef NullType Result;
};

template<typename Head, typename Tail>
struct DerivedToFront< Typelist<Head, Tail> > {
private:
	typedef typename MostDerived<Tail, Head>::Result TheMostDerived;
	typedef typename Replace<Tail, TheMostDerived, Head>::Result L;
public:
	typedef Typelist<TheMostDerived, L> Result;
};



// GenScatterHierarchy  ///////////////////////////////////

    namespace Private
    {
        // The following type helps to overcome subtle flaw in the original 
        // implementation of GenScatterHierarchy. 
        // The flaw is revealed when the input type list of GenScatterHierarchy 
        // contains more then one element of the same type (e.g. LOKI_TYPELIST_2(int, int)). 
        // In this case GenScatterHierarchy will contain multiple bases of the same 
        // type and some of them will not be reachable (per 10.3).
        // For example before the fix the first element of Tuple<LOKI_TYPELIST_2(int, int)>
        // is not reachable in any way!
        template<class, class> 
        struct ScatterHierarchyTag;
    }

    template <class TList, template <class> class Unit>
    class GenScatterHierarchy;
     
    template <class T1, class T2, template <class> class Unit>
    class GenScatterHierarchy<Typelist<T1, T2>, Unit>
        : public GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit>
        , public GenScatterHierarchy<T2, Unit>
    {
    public:
        typedef Typelist<T1, T2> TList;
        // Insure that LeftBase is unique and therefore reachable
        typedef GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit> LeftBase;
        typedef GenScatterHierarchy<T2, Unit> RightBase;
        template <typename T> struct Rebind
        {
            typedef Unit<T> Result;
        };
    };
     
    // In the middle *unique* class that resolve possible ambiguity
    template <class T1, class T2, template <class> class Unit>
    class GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit> 
        : public GenScatterHierarchy<T1, Unit>
    {
    };

    template <class AtomicType, template <class> class Unit>
    class GenScatterHierarchy : public Unit<AtomicType>
    {
        typedef Unit<AtomicType> LeftBase;
        template <typename T> struct Rebind
        {
            typedef Unit<T> Result;
        };
    };
    
    template <template <class> class Unit>
    class GenScatterHierarchy<NullType, Unit>
    {
        template <typename T> struct Rebind
        {
            typedef Unit<T> Result;
        };
    };
     


    template
    <
        class TList,
        template <class AtomicType, class Base> class Unit,
        class Root = EmptyType
    >
    class GenLinearHierarchy;
    
    template
    <
        class T1,
        class T2,
        template <class, class> class Unit,
        class Root
    >
    class GenLinearHierarchy<Typelist<T1, T2>, Unit, Root>
        : public Unit< T1, GenLinearHierarchy<T2, Unit, Root> >
    {
    };

    template
    <
        class T,
        template <class, class> class Unit,
        class Root
    >
    class GenLinearHierarchy<Typelist<T, NullType>, Unit, Root>
        : public Unit<T, Root>
    {
    };

    template
    <
        template <class, class> class Unit,
        class Root
    >
    class GenLinearHierarchy<NullType , Unit, Root>
        : public Root // is this better: Unit<NullType, Root> ?
    {
    };





template<typename T>
struct Holder {
	T value_;
};

template<typename T, typename BaseType>
struct Base
	: public BaseType
	, public Holder<T>
{
	
};

typedef GenScatterHierarchy<TYPELIST_3(int, string, vector<int>), Holder>  WidgetInfo;
//typedef GenLinearHierarchy<TYPELIST_3(int, string, vector<int>), Base>  WidgetInfo;




int main() {
	using namespace std;
//	cout << Length<SignedIntegrals>::value << endl;
//	cout << typeid(TypeAt<SignedIntegrals,2>::Result).name() << endl;
//	cout << IndexOf<SignedIntegrals, signed char>::value << endl;
//	cout << typeid(SignedTypes).name() << endl;
//	cout << typeid(DoubleFloat).name() << endl;
	WidgetInfo obj;
	string name = (static_cast<Holder<string>&>(obj)).value_;
	cout << name << endl;
}

