#if !defined(CRY_PTR_FUN_HPP_INCLUDE_GUARD)
#define CRY_PTR_FUN_HPP_INCLUDE_GUARD

#include <boost/preprocessor.hpp>

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>

#include "function_traits.hpp"

#include <boost/mpl/if.hpp>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

namespace cry{

// Primary template. 定義しない．
template<class F, F f>
struct il_ptr_fun;

// CRY_IL_PTR_FUN_NO_PREPROCESSEDが定義されているとプリプロセッサーによる
// il_ptr_funの特殊化の生成を行う．定義されていないと単にil_ptr_funの特殊化を
// 書いたファイルをincludeするだけ．
#if defined(CRY_IL_PTR_FUN_NO_PREPROCESSED)

#if !defined(CRY_IL_PTR_FUN_MAX_ARITY)
#define CRY_IL_PTR_FUN_MAX_ARITY 10
#endif

// 以下，il_ptr_funの特殊化を生成するための繰り返しインクルード．
// BOOST_PP_ITERATION_PARAMSの第4引数（BOOST_PP_ITERATION_FLAGSで取得できる）
// の意味は以下．
//
//   (function_type, result_type)
//   function_type : 0 -> 関数ポインタ版の特殊化
//                   1 -> 関数参照版の特殊化
//                   2 -> メンバ関数ポインタ版の特殊化
//                   3 -> constメンバ関数ポインタ版の特殊化
//   result_type   : 0 -> 戻り値がvoid以外
//                   1 -> 戻り値がvoid
#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(0,0)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(0,1)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(1,0)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(1,1)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(2,0)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(2,1)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(3,0)))
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_1 (4,(0,CRY_IL_PTR_FUN_MAX_ARITY,"il_ptr_fun_aux.hpp",(3,1)))
#include BOOST_PP_ITERATE()

#else // defined(CRY_IL_PTR_FUN_NO_PREPROCESSED)

// プリプロセス済みヘッダー．プリプロセッサーでに生成させたコードから空行を
// 削っただけ．
#include "il_ptr_fun_preprocessed.hpp"

#endif // defined(CRY_IL_PTR_FUN_NO_PREPROCESSED)

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
// 　VC++7.1ではある状況下で標準準拠のコードであるにもかかわらず，
// コンパイルエラーとなる．クラステンプレートのメンバ関数テンプレートが
// 非型パラメータを取る場合で，その型が外側のクラステンプレートの型パラメータに
// 依存した型だとコンパイル時評価可能なはずの値を，その引数とすることが
// 出来ない．
// 　具体的には以下のようなコード．
//
//    int square(int n){ return n * n; }
//
//    template<class F>
//    class C
//    {
//      template<F f>
//      void f() const{ }
//    };
//
//    C<int (*)(int)>().f<&square>(); // コンパイラエラーを起こす．
//                                    // （&squareはコンパイル時評価可能でない
//                                    // といわれる）
//
// 　class X<class T, T t>という種類のクラステンプレート
//（具体的にはil_ptr_fun）に対するオブジェクトジェネレータを実装するために
// この手法を使いたかったのだが，VC++7.1ではどうも無理みたいなので代替手法を
// 考案した．この手法による'il_ptr_fun'のオブジェクトジェネレータの実装は
// work-aroundでない方の実装（かなり下のほうにある）を参考にして欲しい．
// 　他に上のバグとは別に複雑な関数テンプレートの引数推論が出来ないというバグ
// もある．具体的な状況は失念．
// 　以下のコードがVC++7.1に対する代替手法となる．以下のコード中には
// reinterpret_castがいくつか出てくるが，これは全て型安全かつ標準準拠な
// 使用方法である（というか標準準拠であることにこだわったためにここまで
// 複雑になったといっても良い）．
// 　基本的には関数ポインタを一旦void (*)()にreinterpret_castして保持しつつ，
// 一方で関数テンプレートによる型推論で型を推定してreinterpret_castで
// 元の型に戻す，というやり方になっている．メンバ関数へのポインタの場合は
// 一旦void (dummy_for_typeless_pmf::*)()にreinterpret_castしている．このような
// 別の（メンバ）関数へのポインタ型へreinterpret_castして元に戻すという操作は
// 標準でその安全性が保証されている．
// 
//   5.2.10 reinterpret_cast
//   6  A pointer to a function can be explicitly converted to a pointer to a
//     function of a different type. The effect of calling a function through
//     a pointer to a function type (8.3.5) that is not the same as the type
//     used in the definition of the function is undefined. Except that
//     converting an rvalue of type "pointer to T1" to the type
//     "pointer to T2" (where T1 and T2 are function types) and back to its
//     original type yields the original pointer value, the result of such a
//     pointer conversion is unspecified.
//
//   9  An rvalue of type "pointer to member of X of type T1" can be
//     explicitly converted to an rvalue of type "pointer to member of Y of
//     type T2" if T1 and T2 are both function types or both object types.66)
//     The null member pointer value (4.11) is converted to the null member
//     pointer value of the destination type. The result of this conversion is
//     unspecified, except in the following cases:
//
//       - converting an rvalue of type "pointer to member function" to a
//         different pointer to member function type and back to its original
//         type yields the original pointer to member value.
//     （以下略）
//
// 　また，関数ポインタ型あるいはメンバ関数ポインタ型のオブジェクトだけから
// その関数の種別を取得するために，関数テンプレートによる引数の型推論と
// その戻り値の型に対するsizeofを組み合わせた手法を用いている．
// 　唯一分からない点はコンパイル時評価可能な値をreinterpret_castした値も
// コンパイル時評価なのかどうか，ということ．でもコンパイルできているってことは
// 大丈夫なんでしょう．知らんけど．

namespace detail{

class dummy_for_typeless_pmf{ };

typedef void (*typeless_ptr_fun_t)();
typedef void (&typeless_ref_fun_t)();
typedef void (dummy_for_typeless_pmf::*typeless_pmf_t)();
typedef void (dummy_for_typeless_pmf::*typeless_pcmf_t)() const;



// 　第1引数にtypelessな型（void (*)()とか）のオブジェクトを保持しつつ，
// 第2引数にそのオブジェクトの実際の型を保持したholder．何故こんな
// 周りくどいことをしなければならないのかは説明が長いので省略．実際に
// class X<class T, T t>というクラスのオブジェクトジェネレータを作ってみると
// その難しさが分かるかも．これらはil_ptr_funメンバ関数によって最終的に
// 取得したいil_ptr_funの型を生成する．
template<typeless_ptr_fun_t pf, class F>
struct typeless_ptr_fun_with_type
{
  il_ptr_fun<F, reinterpret_cast<F>(pf)>
  make_il_ptr_fun() const
  { return il_ptr_fun<F, reinterpret_cast<F>(pf)>(); }
};

template<typeless_ref_fun_t rf, class F>
struct typeless_ref_fun_with_type
{
  il_ptr_fun<F, reinterpret_cast<F>(rf)>
  make_il_ptr_fun() const
  { return il_ptr_fun<F, reinterpret_cast<F>(rf)>(); }
};

template<typeless_pmf_t pmf, class F>
struct typeless_pmf_with_type
{
  il_ptr_fun<F, reinterpret_cast<F>(pmf)>
  make_il_ptr_fun() const
  { return il_ptr_fun<F, reinterpret_cast<F>(pmf)>(); }
};

template<typeless_pcmf_t pcmf, class F>
struct typeless_pcmf_with_type
{
  il_ptr_fun<F, reinterpret_cast<F>(pcmf)>
  make_il_ptr_fun() const
  { return il_ptr_fun<F, reinterpret_cast<F>(pcmf)>(); }
};



// オブジェクトからその関数の種類を識別するためだけのクラス．
// C++の全てのオブジェクトはsizeofが1以上であることが保証されているので，
// 以下の4つのクラスは全てsizeofの結果が異なることが保証される．そこで，
// 関数テンプレート（下にあるdiscriminate_function_type）によってオブジェクトの
// 型を推論させ，その種類によって戻り値を変えて，さらにそれをsizeofすることに
// よって，オブジェクトの種類を識別するコンパイル時決定な整数定数が取得できる．
//
//   sizeof(discriminate_function_type(f))
//   // fが関数へのポインタならsizeof(ptr_fun_disc)
//   // 関数への参照ならsizeof(ref_fun_disc)
//   // メンバ関数への参照ならsizeof(pmf_disc)
//   // constメンバ関数への参照ならsizeof(pcmf_disc)
//
// この手法によって取得したコンパイル時定数は，typeless_castテンプレート，
// function_type_tagテンプレートの特殊化に使っている．
// この手法は特殊なtype traitsやtypeofエミュレーションにも使われている．

struct ptr_fun_disc{                    };
struct ref_fun_disc{ ptr_fun_disc a[2]; };
struct pmf_disc    { ptr_fun_disc a[3]; };
struct pcmf_disc   { ptr_fun_disc a[4]; };



// 関数の型から対応するdiscriminatorを計算するメタ関数
template<class F>
struct function_type_discriminator
{
  typedef typename
    ::boost::mpl::if_<
      ::boost::is_member_function_pointer<F>,
      typename ::boost::mpl::if_c<
        ::cry::function_traits<F>::is_const,
        pcmf_disc,
        pmf_disc
      >::type,
      typename ::boost::mpl::if_<
        ::boost::is_pointer<F>,
        ptr_fun_disc,
        ref_fun_disc
      >::type
    >::type type;
};



// 様々な関数の型のオブジェクトから対応するdiscriminatorを生成する
// 関数テンプレート
template<class F>
inline
typename function_type_discriminator<F>::type
discriminate_function_type(F)
{
  typedef typename function_type_discriminator<F>::type discriminator;
  return discriminator();
}



// 関数のタイプを識別するタグ．make_typeless_holderのディスパッチに使用．
struct ptr_fun_tag{ };
struct ref_fun_tag{ };
struct pmf_tag    { };
struct pcmf_tag   { };



// sizeofとdiscriminate_function_typeの組み合わせで生成した定数を使って
// そのオブジェクトに対応するタグを計算するクラステンプレート．
template<size_t N>
struct function_type_tag;

template<>
struct function_type_tag<sizeof(ptr_fun_disc)>
{
  typedef ptr_fun_tag type;
};

template<>
struct function_type_tag<sizeof(ref_fun_disc)>
{
  typedef ref_fun_tag type;
};

template<>
struct function_type_tag<sizeof(pmf_disc)>
{
  typedef pmf_tag type;
};

template<>
struct function_type_tag<sizeof(pcmf_disc)>
{
  typedef pcmf_tag type;
};



// 関数の型によってreinterpret_cast出来る型が異なるので，対応する型を計算する
// クラステンプレート．discriminate_function_type + sizeofで取得した
// コンパイル時定数を使う．
template<size_t N>
struct typeless_cast;

template<>
struct typeless_cast<sizeof(ptr_fun_disc)>
{
  typedef typeless_ptr_fun_t type;
};

template<>
struct typeless_cast<sizeof(ref_fun_disc)>
{
  typedef typeless_ref_fun_t type;
};

template<>
struct typeless_cast<sizeof(pmf_disc)>
{
  typedef typeless_pmf_t type;
};

template<>
struct typeless_cast<sizeof(pcmf_disc)>
{
  typedef typeless_pcmf_t type;
};



// typeless_*****_with_typeを生成する関数テンプレート
template<typeless_ptr_fun_t pf, class F>
inline
typeless_ptr_fun_with_type<pf, F>
make_typeless_holder(F, ptr_fun_tag)
{ return typeless_ptr_fun_with_type<pf, F>(); }

template<typeless_ref_fun_t rf, class F>
inline
typeless_ref_fun_with_type<rf, F>
make_typeless_holder(F, ref_fun_tag)
{ return typeless_ref_fun_with_type<rf, F>(); }

template<typeless_pmf_t pmf, class F>
inline
typeless_pmf_with_type<pmf, F>
make_typeless_holder(F, pmf_tag)
{ return typeless_pmf_with_type<pmf, F>(); }

template<typeless_pcmf_t pcmf, class F>
inline
typeless_pcmf_with_type<pcmf, F>
make_typeless_holder(F, pcmf_tag)
{ return typeless_pcmf_with_type<pcmf, F>(); }

} // namespace detail



// 以上を総合して関数ポインタ・関数参照・メンバ関数ポインタ
// ・constメンバ関数の各オブジェクトから対応するil_ptr_funの型を推論して
// そのオブジェクトを返すマクロ．
// 関数の種類によって個々にマクロ用意したほうが実装が簡単だけれど，やっぱり
// genericに一つだけで提供したかったので頑張ってみました．
#define CRY_AS_FUNCTOR(f) \
::cry::detail::make_typeless_holder< \
  reinterpret_cast< \
    ::cry::detail::typeless_cast< \
      sizeof(::cry::detail::discriminate_function_type(f)) \
    >::type \
  >(f) \
>(f, \
  ::cry::detail::function_type_tag< \
    sizeof(::cry::detail::discriminate_function_type(f)) \
  >::type() \
).make_il_ptr_fun()

#else // BOOST_WORKAROUND(BOOST_MSVC, <= 1310)

// 上のバグさえなければここまで簡単に書けるのに・・・．

namespace detail{

template<class F>
struct function_type_deducer
{
  template<F f>
  il_ptr_fun<F, f> make_il_ptr_fun() const
  { return il_ptr_fun<F, f>(); }
};

template<class F>
inline
detail::function_type_deducer<F>
make_function_type_deducer(F)
{ return detail::function_type_deducer<F>(); }

} // namespace detail

#define CRY_AS_FUNCTOR(f) ::cry::detail::make_function_type_deducer(f).make_il_ptr_fun<f>()

#endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1310)

} // namespace cry

#endif // CRY_PTR_FUN_HPP_INCLUDE_GUARD
