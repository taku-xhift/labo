/**
 * @file
 * @brief タイプリスト・コンセプトを使って自動でクラスを作り上げるメタプログラミングライブラリ
 * @note    オリジナルのアイディアは Modern C++ Design の loki ライブラリ
 *
 * @author Takuya Shishido
 * @date   2011.01.18 19:09:39
 *
 * @version 0.01, Shishido Takuya, 2011.01.18 19:09:39
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_TASK_WEOTYPELIST_HPP_INCLUDED
#define PM_MODE_TASK_WEOTYPELIST_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
//#include <type_traits>
#include "weoNullType.h"
#include "weCommonType.h"
#include "weoTypeTraits.h"


namespace pm_mode {
namespace task {


template<typename T, typename U>
struct Typelist {
	typedef T Head;
	typedef U Tail;
};



template
<
typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
typename T16 = NullType, typename T17 = NullType, typename T18 = NullType
> 
struct MakeTypelist
{
private:
	typedef typename MakeTypelist
		<
			T2 , T3 , T4 , 
			T5 , T6 , T7 , 
			T8 , T9 , T10, 
			T11, T12, T13,
			T14, T15, T16, 
			T17, T18
		>
		::Result TailResult;

public:
	typedef Typelist<T1, TailResult> Result;
};

template<>
struct MakeTypelist<>
{
	typedef NullType Result;
};



// Length  ////////////////////////////////////////////////
//! \brief タイプリストの長さ取得
//! \note   Length<>::value で取得。

template<typename TypeList> struct Length;

template<>
struct Length<NullType> {
	static const weInt value = 0;
};

template<typename T, typename U>
struct Length< Typelist<T, U> >
{
	static const weInt value = 1 + Length<U>::value;
};


// TypeAt  ////////////////////////////////////////////////
//! \brief タイプリストの任意の index の型を取得する
//! \note   TypeAt<, 0>::Result で取得。 index は 0 から。
template <typename TypeList, weUint index> struct TypeAt;

template<typename Head, typename Tail>
struct TypeAt<Typelist<Head, Tail>, 0>
{
	typedef Head Result;
};

template<typename Head, typename Tail, weUint i>
struct TypeAt<Typelist<Head, Tail>, i> {
	typedef typename TypeAt<Tail, i-1>::Result Result;
};


// IndexOf  ///////////////////////////////////////////////
//! \brief タイプリストの型を検索する
//! \note       IndexOf<, Type>::value で、内容は retval を参照。
//! \retval     見つかった          登録された番号
//! \retval     見つからなかった    -1
template<typename TypeList, typename T>
struct IndexOf;

template<typename T>
struct IndexOf<NullType, T> {
	static const weInt value = -1;
};

template<typename T, typename Tail>
struct IndexOf<Typelist<T, Tail>, T> {
	static const weInt value = 0;
};

template<typename Head, typename Tail, typename T>
struct IndexOf<Typelist<Head, Tail>, T> {
private:
	static const weInt temp = IndexOf<Tail, T>::value;
public:
	static const weInt value = (temp == -1)? -1 : 1 + temp;
};


// Append  ////////////////////////////////////////////////
//! \brief タイプリストの結合
//! \note   Append<, other>::Result で新しいタイプリスト取得
//! \note   １つでもタイプリスト同士の結合も可能
//typedef Append<SignedIntegrals, TYPELIST_3(float, double, long double)>::Result SignedTypes;


template<typename Typelist, typename T>
struct Append;

template<>
struct Append<NullType, NullType> {
	typedef NullType Result;
};

template<typename T>
struct Append<NullType, T> {
	typedef MakeTypelist<T> Result;
};

template<typename Head, typename Tail>
struct Append<NullType, Typelist<Head, Tail> > {
	typedef Typelist<Head, Tail> Result;
};

template<typename Head, typename Tail, typename T>
struct Append<Typelist<Head, Tail>, T> {
	typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
};


// Erase //////////////////////////////////////////////////
//! \brief タイプリストから特定の型を取り除く
//! \note   Erase<, list>::Result   で除去された後のタイプリスト
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
//! \brief タイプリストを空にする
//! \note   EraseAll<>::Result で空のタイプリスト
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
//! \brief 重複しているタイプリストを除去する
//! \note   NoDuplicates<>::Result で除去された後のタイプリスト取得
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
//! \brief タイプリスト内の特定の型を置換
//! \brief  Replace<, Type>::Result で取得
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
	typedef Typelist<Head, typename ReplaceAll<Tail, T, U>::Result> Result;
};



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
//! \brief TypeList で指定された型と Unit で指定されたクラスを合わせて
//              一つのクラスを作りだすシステム。
//              継承関係は多重継承型。
//         ちなみに template-template 引数の宣言を
//             typename で行うとなぜかコンパイルエラーになるので
//             class で定義している。差は特にないはず。

namespace Private
{
	template<typename, typename> 
	struct ScatterHierarchyTag;
}

template <typename TList, template <typename> class Unit>
class GenScatterHierarchy;

template <typename T1, typename T2, template <typename> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
	: public GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit>
	, public GenScatterHierarchy<T2, Unit>
{
public:
	typedef Typelist<T1, T2> TList;
	typedef GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit> LeftBase;
	typedef GenScatterHierarchy<T2, Unit> RightBase;

	template <typename T> struct Rebind {
		typedef Unit<T> Result;
	};
};


template <typename T1, typename T2, template <typename> class Unit>
class GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit> 
	: public GenScatterHierarchy<T1, Unit>
{
};

template <typename AtomicType, template <typename> class Unit>
class GenScatterHierarchy : public Unit<AtomicType>
{
	typedef Unit<AtomicType> LeftBase;
	template <typename T> struct Rebind {
		typedef Unit<T> Result;
	};
};

template <template <typename> class Unit>
class GenScatterHierarchy<NullType, Unit>
{
	template <typename T> struct Rebind {
		typedef Unit<T> Result;
	};
};


// Tuple  ///////////////////////////////////////////////////////////
//! \brief TypeList を用いて実装したタプルクラス。データを保管する。
//! \note   後の Field で使いたいので実装。
//
//
template <typename T>
struct TupleUnit
{
	T value_;
	operator T&() { return value_; }
	operator const T&() const { return value_; }
};


template <typename TList>
struct Tuple : public GenScatterHierarchy<TList, TupleUnit>
{
};



// Field  ///////////////////////////////////////////////////////////
//! \brief TypeList に格納されているオブジェクトを番号で指定して取得する機構
//! \note   関数自体は Field。
//              しかし実装本体は FieldHelper にて。
//
//

/********************************************************************
 * @brief 番号を指定して TypeList オブジェクトの中から必要なものを検索するファンクタ
 * @tparam  TypeListObject  TypeList 型
 * @tparam  i               検索する番号(コンパイル中に変化する)
 *******************************************************************/
template <typename T, typename H>
typename H::template Rebind<T>::Result& Field(H& obj) {
	return obj;
}

template <typename T, typename H>
const typename H::template Rebind<T>::Result& Field(const H& obj) {
	return obj;
}


/********************************************************************
 * @brief 番号を指定して TypeList オブジェクトの中から必要なものを検索するファンクタ
 * @tparam  TypeListObject  TypeList 型
 * @tparam  i               検索する番号(コンパイル中に変化する)
 *******************************************************************/
// 宣言部
template <typename H, weUint i> struct FieldHelper;


// 末端
template <typename H>
struct FieldHelper<H, 0>
{
	typedef typename H::TList::Head                             ElementType;
	typedef typename H::template Rebind<ElementType>::Result    UnitType;

	static const weInt isTuple = Conversion<UnitType, TupleUnit<ElementType> >::sameType;
	static const weInt isConst = TypeTraits<H>::isConst;

	typedef const typename H::LeftBase                  ConstLeftBase;

	typedef typename Select<isConst, ConstLeftBase, typename H::LeftBase>::Result
	                                                    LeftBase;

	typedef typename Select<isTuple, ElementType, UnitType>::Result
	                                                    UnqualifiedResultType;

	typedef typename Select<isConst, const UnqualifiedResultType,
	        UnqualifiedResultType>::Result              ResultType;


	/****************************************************************
	 * @brief TypeList の中から i 番目のオブジェクトを探し出すメイン部分
	 * @param[in]   obj     検索したい TypeList オブジェクト
	 * @return      見つかったオブジェクト
	 ***************************************************************/
	static ResultType& Do(H& obj) {
		LeftBase& leftBase = obj;
		return leftBase;
	}
};


// 検索部
template <typename H, weUint i>
struct FieldHelper
{
	typedef typename TypeAt<typename H::TList, i>::Result       ElementType;    //!< i で指定された TypeList の型
	typedef typename H::template Rebind<ElementType>::Result    UnitType;       //!< GenScatterHierarchy で定義された型で、所有しているオブジェクトの型

	static const weInt isTuple = Conversion<UnitType, TupleUnit<ElementType> >::sameType;
	static const weInt isConst = TypeTraits<H>::isConst;

	typedef const typename H::RightBase                 ConstRightBase; //!< 型の計算用

	typedef typename Select<isConst, ConstRightBase, typename H::RightBase>::Result
	                                                    RightBase;      //!< const かそうでないのかを判断し、型を決定

	typedef typename Select<isTuple, ElementType, UnitType>::Result
	                                                    UnqualifiedResultType;  //!< とりあえずの戻り型の決定

	typedef typename Select<isConst, const UnqualifiedResultType,
	        UnqualifiedResultType>::Result              ResultType;     //!< こちらが本当の返り型


	/****************************************************************
	 * @brief TypeList の中から i 番目のオブジェクトを探し出すメイン部分
	 * @param[in]   obj     検索したい TypeList オブジェクト
	 * @return      見つかったオブジェクト
	 ***************************************************************/
	static ResultType& Do(H& obj) {
		RightBase& rightBase = obj;
		return FieldHelper<RightBase, i - 1>::Do(rightBase);
	}
};




/********************************************************************
 * @brief TypeList で管理されたオブジェクトから 番号を指定してオブジェクトを取り出す
 * @return  GenScatterHierarchy の第２引数型のオブジェクト
 * @tparam  i   取得したい番号
 * @tparam  H   TypeList 型
 *******************************************************************/
template <weUint i, typename H>
typename FieldHelper<H, i>::ResultType&
Field(H& obj)
{
	return FieldHelper<H, i>::Do(obj);
}


/****************************************************************
 * @brief get の型計算用
 * @note    const 参照の返却。
 *            データをセットしたい場合は素直に set を呼ぶこと
 * @return      クラスオブジェクト
 * @tparam      TypeList    タイプリスト
 * @tparam      modeID      タイプリストの中で取り出したい型の番号
 ***************************************************************/
template<typename TypeList, weUint modeID>
struct CulcResultType {
	typedef typename pm_mode::task::FieldHelper<TypeList, modeID>::ResultType::DataType Result;
};


/****************************************************************
 * @brief get の型計算用
 * @note    const 参照の返却。
 *            データをセットしたい場合は素直に set を呼ぶこと
 * @return      クラスオブジェクト
 * @tparam      TypeList    タイプリスト
 * @tparam      modeID      タイプリストの中で取り出したい型の番号
 ***************************************************************/
template<typename TypeList, weUint modeID, weUint objectID>
struct CulcGetterResultType {
	typedef typename
		pm_mode::task::CulcResultType<
			typename pm_mode::task::FieldHelper<TypeList, modeID>::ResultType::DataType::TypeList, objectID>::Result
				Result;
};



}    // namespace task
}    // namespace pm_mode


#endif

