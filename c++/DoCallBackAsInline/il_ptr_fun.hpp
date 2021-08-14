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

// Primary template. ��`���Ȃ��D
template<class F, F f>
struct il_ptr_fun;

// CRY_IL_PTR_FUN_NO_PREPROCESSED����`����Ă���ƃv���v���Z�b�T�[�ɂ��
// il_ptr_fun�̓��ꉻ�̐������s���D��`����Ă��Ȃ��ƒP��il_ptr_fun�̓��ꉻ��
// �������t�@�C����include���邾���D
#if defined(CRY_IL_PTR_FUN_NO_PREPROCESSED)

#if !defined(CRY_IL_PTR_FUN_MAX_ARITY)
#define CRY_IL_PTR_FUN_MAX_ARITY 10
#endif

// �ȉ��Cil_ptr_fun�̓��ꉻ�𐶐����邽�߂̌J��Ԃ��C���N���[�h�D
// BOOST_PP_ITERATION_PARAMS�̑�4�����iBOOST_PP_ITERATION_FLAGS�Ŏ擾�ł���j
// �̈Ӗ��͈ȉ��D
//
//   (function_type, result_type)
//   function_type : 0 -> �֐��|�C���^�ł̓��ꉻ
//                   1 -> �֐��Q�Ɣł̓��ꉻ
//                   2 -> �����o�֐��|�C���^�ł̓��ꉻ
//                   3 -> const�����o�֐��|�C���^�ł̓��ꉻ
//   result_type   : 0 -> �߂�l��void�ȊO
//                   1 -> �߂�l��void
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

// �v���v���Z�X�ς݃w�b�_�[�D�v���v���Z�b�T�[�łɐ����������R�[�h�����s��
// ����������D
#include "il_ptr_fun_preprocessed.hpp"

#endif // defined(CRY_IL_PTR_FUN_NO_PREPROCESSED)

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
// �@VC++7.1�ł͂���󋵉��ŕW�������̃R�[�h�ł���ɂ�������炸�C
// �R���p�C���G���[�ƂȂ�D�N���X�e���v���[�g�̃����o�֐��e���v���[�g��
// ��^�p�����[�^�����ꍇ�ŁC���̌^���O���̃N���X�e���v���[�g�̌^�p�����[�^��
// �ˑ������^���ƃR���p�C�����]���\�Ȃ͂��̒l���C���̈����Ƃ��邱�Ƃ�
// �o���Ȃ��D
// �@��̓I�ɂ͈ȉ��̂悤�ȃR�[�h�D
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
//    C<int (*)(int)>().f<&square>(); // �R���p�C���G���[���N�����D
//                                    // �i&square�̓R���p�C�����]���\�łȂ�
//                                    // �Ƃ�����j
//
// �@class X<class T, T t>�Ƃ�����ނ̃N���X�e���v���[�g
//�i��̓I�ɂ�il_ptr_fun�j�ɑ΂���I�u�W�F�N�g�W�F�l���[�^���������邽�߂�
// ���̎�@���g�����������̂����CVC++7.1�ł͂ǂ��������݂����Ȃ̂ő�֎�@��
// �l�Ă����D���̎�@�ɂ��'il_ptr_fun'�̃I�u�W�F�N�g�W�F�l���[�^�̎�����
// work-around�łȂ����̎����i���Ȃ艺�̂ق��ɂ���j���Q�l�ɂ��ė~�����D
// �@���ɏ�̃o�O�Ƃ͕ʂɕ��G�Ȋ֐��e���v���[�g�̈������_���o���Ȃ��Ƃ����o�O
// ������D��̓I�ȏ󋵂͎��O�D
// �@�ȉ��̃R�[�h��VC++7.1�ɑ΂����֎�@�ƂȂ�D�ȉ��̃R�[�h���ɂ�
// reinterpret_cast���������o�Ă��邪�C����͑S�Č^���S���W��������
// �g�p���@�ł���i�Ƃ������W�������ł��邱�Ƃɂ�����������߂ɂ����܂�
// ���G�ɂȂ����Ƃ����Ă��ǂ��j�D
// �@��{�I�ɂ͊֐��|�C���^����Uvoid (*)()��reinterpret_cast���ĕێ����C
// ����Ŋ֐��e���v���[�g�ɂ��^���_�Ō^�𐄒肵��reinterpret_cast��
// ���̌^�ɖ߂��C�Ƃ��������ɂȂ��Ă���D�����o�֐��ւ̃|�C���^�̏ꍇ��
// ��Uvoid (dummy_for_typeless_pmf::*)()��reinterpret_cast���Ă���D���̂悤��
// �ʂ́i�����o�j�֐��ւ̃|�C���^�^��reinterpret_cast���Č��ɖ߂��Ƃ��������
// �W���ł��̈��S�����ۏ؂���Ă���D
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
//     �i�ȉ����j
//
// �@�܂��C�֐��|�C���^�^���邢�̓����o�֐��|�C���^�^�̃I�u�W�F�N�g��������
// ���̊֐��̎�ʂ��擾���邽�߂ɁC�֐��e���v���[�g�ɂ������̌^���_��
// ���̖߂�l�̌^�ɑ΂���sizeof��g�ݍ��킹����@��p���Ă���D
// �@�B�ꕪ����Ȃ��_�̓R���p�C�����]���\�Ȓl��reinterpret_cast�����l��
// �R���p�C�����]���Ȃ̂��ǂ����C�Ƃ������ƁD�ł��R���p�C���ł��Ă�����Ă��Ƃ�
// ���v�Ȃ�ł��傤�D�m��񂯂ǁD

namespace detail{

class dummy_for_typeless_pmf{ };

typedef void (*typeless_ptr_fun_t)();
typedef void (&typeless_ref_fun_t)();
typedef void (dummy_for_typeless_pmf::*typeless_pmf_t)();
typedef void (dummy_for_typeless_pmf::*typeless_pcmf_t)() const;



// �@��1������typeless�Ȍ^�ivoid (*)()�Ƃ��j�̃I�u�W�F�N�g��ێ����C
// ��2�����ɂ��̃I�u�W�F�N�g�̎��ۂ̌^��ێ�����holder�D���̂����
// ���肭�ǂ����Ƃ����Ȃ���΂Ȃ�Ȃ��̂��͐����������̂ŏȗ��D���ۂ�
// class X<class T, T t>�Ƃ����N���X�̃I�u�W�F�N�g�W�F�l���[�^������Ă݂��
// ���̓���������邩���D������il_ptr_fun�����o�֐��ɂ���čŏI�I��
// �擾������il_ptr_fun�̌^�𐶐�����D
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



// �I�u�W�F�N�g���炻�̊֐��̎�ނ����ʂ��邽�߂����̃N���X�D
// C++�̑S�ẴI�u�W�F�N�g��sizeof��1�ȏ�ł��邱�Ƃ��ۏ؂���Ă���̂ŁC
// �ȉ���4�̃N���X�͑S��sizeof�̌��ʂ��قȂ邱�Ƃ��ۏ؂����D�����ŁC
// �֐��e���v���[�g�i���ɂ���discriminate_function_type�j�ɂ���ăI�u�W�F�N�g��
// �^�𐄘_�����C���̎�ނɂ���Ė߂�l��ς��āC����ɂ����sizeof���邱�Ƃ�
// ����āC�I�u�W�F�N�g�̎�ނ����ʂ���R���p�C��������Ȑ����萔���擾�ł���D
//
//   sizeof(discriminate_function_type(f))
//   // f���֐��ւ̃|�C���^�Ȃ�sizeof(ptr_fun_disc)
//   // �֐��ւ̎Q�ƂȂ�sizeof(ref_fun_disc)
//   // �����o�֐��ւ̎Q�ƂȂ�sizeof(pmf_disc)
//   // const�����o�֐��ւ̎Q�ƂȂ�sizeof(pcmf_disc)
//
// ���̎�@�ɂ���Ď擾�����R���p�C�����萔�́Ctypeless_cast�e���v���[�g�C
// function_type_tag�e���v���[�g�̓��ꉻ�Ɏg���Ă���D
// ���̎�@�͓����type traits��typeof�G�~�����[�V�����ɂ��g���Ă���D

struct ptr_fun_disc{                    };
struct ref_fun_disc{ ptr_fun_disc a[2]; };
struct pmf_disc    { ptr_fun_disc a[3]; };
struct pcmf_disc   { ptr_fun_disc a[4]; };



// �֐��̌^����Ή�����discriminator���v�Z���郁�^�֐�
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



// �l�X�Ȋ֐��̌^�̃I�u�W�F�N�g����Ή�����discriminator�𐶐�����
// �֐��e���v���[�g
template<class F>
inline
typename function_type_discriminator<F>::type
discriminate_function_type(F)
{
  typedef typename function_type_discriminator<F>::type discriminator;
  return discriminator();
}



// �֐��̃^�C�v�����ʂ���^�O�Dmake_typeless_holder�̃f�B�X�p�b�`�Ɏg�p�D
struct ptr_fun_tag{ };
struct ref_fun_tag{ };
struct pmf_tag    { };
struct pcmf_tag   { };



// sizeof��discriminate_function_type�̑g�ݍ��킹�Ő��������萔���g����
// ���̃I�u�W�F�N�g�ɑΉ�����^�O���v�Z����N���X�e���v���[�g�D
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



// �֐��̌^�ɂ����reinterpret_cast�o����^���قȂ�̂ŁC�Ή�����^���v�Z����
// �N���X�e���v���[�g�Ddiscriminate_function_type + sizeof�Ŏ擾����
// �R���p�C�����萔���g���D
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



// typeless_*****_with_type�𐶐�����֐��e���v���[�g
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



// �ȏ�𑍍����Ċ֐��|�C���^�E�֐��Q�ƁE�����o�֐��|�C���^
// �Econst�����o�֐��̊e�I�u�W�F�N�g����Ή�����il_ptr_fun�̌^�𐄘_����
// ���̃I�u�W�F�N�g��Ԃ��}�N���D
// �֐��̎�ނɂ���ČX�Ƀ}�N���p�ӂ����ق����������ȒP������ǁC����ς�
// generic�Ɉ�����Œ񋟂����������̂Ŋ撣���Ă݂܂����D
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

// ��̃o�O�����Ȃ���΂����܂ŊȒP�ɏ�����̂ɁE�E�E�D

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
