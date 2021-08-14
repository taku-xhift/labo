//-----------------------------------------------------------------------
//! @file	LibHeader.h
//! @brief	���C�u�����p�e��錾�E�ėp����
//!	@author	�ɓ��M�� 
//
//! @date	07/07/15�F�ĕ�
//! @date	07/09/01�F�X���b�v�����ǉ�
//!	@date	07/09/02�F�ő奍ŏ��A�l�N�����v��ǉ�
//-----------------------------------------------------------------------

/* !! double�^�͌�������Ȃ��̂Ŏg�p���ɂ͒��� !! */

#ifndef ___LIB_HEADER___
#define ___LIB_HEADER___


#define _CRT_SECURE_NO_DEPRECATE						// ���`���̊֐��g�p
#pragma warning (disable : 4819)						// �t�@�C���́A���݂̃R�[�h �y�[�Wx �ŕ\���ł��Ȃ��������܂�ł��܂�


#include <cmath>
#include <cstdlib>
#include <cassert>


//-----------------------------------------------------------//
// �}�N���ݒ�
//-----------------------------------------------------------//
#define ___USE_RADIAN___		//�p�x�Ƃ��ă��W�A�����g��
#define ___USE_D3DX___
//#define ___USE_OPEN_GL___


#define ZERO		0.0001f		// ���e�����덷�ő�l
#define SLERP_MAX	.95f		// ���ʐ��`��Ԃ�����`��Ԃɕς���{�[�_�[�l


//-----------------------------------------------------------//
// �^��`
//-----------------------------------------------------------//

// �z��Q�ƌ^
#ifdef  _WIN64
typedef __int64			differ_type;		// �Y�����A�N�Z�X�p
#else
typedef _W64 int		differ_type;
#endif

// �|�C���^�^
#ifdef _WP64
typedef unsigned __int64	ptr_type; 
#else
typedef	size_t				ptr_type;
#endif



//-----------------------------------------------------------//
// DirectX�g�p���̐ݒ� 
//-----------------------------------------------------------//
#ifdef ___USE_D3DX___


#include <d3dx9math.h>

#define	 _PI				D3DX_PI


#define ___USE_HLSL___					// �V�F�[�_�`��
//#define ___USE_ASM_SHADER___			// �œK���̂��߁A�`���ɂ���ăf�[�^�̎�������ς���K�v���� 


#ifdef ___USE_HLSL___

#define ___USE_MTX_COL_MAJOR___			// �񏇂ɍs����i�[
//#define ___USE_MTX_ROW_MAJOR___			// �s���ɍs����i�[

#elif	defined(___USE_ASM_SHADER___)

#define ___USE_MTX_ROW_MAJOR___			// �s���ɍs����i�[

#endif	// ifdef ___USE_HLSL___



//-----------------------------------------------------------//
// OpenGL�g�p���̐ݒ�
//-----------------------------------------------------------//
#elif  defined(___USE_OPEN_GL___)


#define _PI				3.1415926535897932384626433832795f
#define NULL			0

#define ___USE_MTX_COL_MAJOR___			// �񏇂ɍs����i�[


#endif //___USE_D3DX___


//-----------------------------------------------------------//
// windef.h�̃f�[�^��`
//-----------------------------------------------------------//
#ifndef _WINDEF_
#include <windef.h>
#endif	// ifndef _WINDEF_


//-----------------------------------------------------------//
// �萔�l
//-----------------------------------------------------------//
const float	_e		= 2.71828182845904523536f;
const float _log2	= 1.44269504088896340736f;
const float	_log10	= 0.434294481903251827651f;
const float _root2	= (float)1.4142135623730950488016887242097;
const float _root3	= (float)1.7320508075688772935274463415059;
const float _s60c30 = 2.0f / _root3;	// �T�C��60���R�T�C��30�x
const float _sc45   = 1.0f / _root2;	// �T�C���E�R�T�C��45�x



//-----------------------------------------------------------//
// float �^�Ńr�b�g��������邽�߂̋��p��
//-----------------------------------------------------------//
typedef union uINT_FLOAT
{
	//---------------------//
	// �����o
	//---------------------//
	int		iVal;
	float	fVal;


	//---------------------//
	// �R���X�g���N�^
	//---------------------//
	uINT_FLOAT( float f ) : fVal(f) {}
	uINT_FLOAT( int   i ) : iVal(i) {}


	// �����擾
	static int FloatSign( float f )		{ return (iFloat( f ).iVal >> 31);}

	// �w�����擾
	static int FloatIndex( float f )	{ return (iFloat( f ).iVal >> 23) & 0x0FF;}

	// �������擾
	static int FloatMantissa( float f )	{ return (iFloat( f ).iVal & 0x007FFFFF);}

	// NaN�������ݒ肷��
	static float &SetNaN( float &f )	{ *((int*)&f) = 0x7FFFFFFF;	return f;}

	// NaN�����ׂ�
	static bool IsNaN( float f )		{ return (*((int*)&f) & 0x7F800000) && (*((int*)&f) & 0x007FFFFF);}

	// QNaN�������ݒ肷��
	static float &SetQNaN( float &f )	{ *((int*)&f) = 0x7FFFFFFF;	return f;}

	// QNaN�����ׂ�
	static bool IsQNaN( float f )		{ return !!(*((int*)&f) & 0x7FC00000);}

	// SNaN�������ݒ肷��
	static float &SetSNaN( float &f )	{ *((int*)&f) = 0x7FBFFFFF;	return f;}

	// SNaN�����ׂ�
	static bool IsSNaN( float f )		{ return (*((int*)&f) & 0x7F000000) && (*((int*)&f) & 0x003FFFFF);}

	// �����ݒ�
	static float &SetInfinity( float &f, bool minus )
	{
		*((int*)&f) = minus ? 0x7F800000 : 0xFF800000;
		return f;
	}

	// ���������ׂ�
	static bool IsInfinity( float f )	{ return (*((int*)&f) & 0x7FFFFFFF) == 0x7F800000;}

}iFloat;



//-----------------------------------------------------------//
// �����֘A
//-----------------------------------------------------------//

// �����̔���i���̂Ƃ�true 0�͐��Ɋ܂܂�� �j
inline bool IsSigned( char x )
{
	return !( (x>>7) & 1);
}

inline bool IsSigned( short x )
{
	return !( (x>>15) & 1);
}

inline bool IsSigned( int x )
{
	return !( (x>>31) & 1);
}

inline bool IsSigned( long x )
{
	return !( (x>>31) & 1);
}

inline bool IsSigned( float x )
{
	return !( (iFloat( x ).iVal>>31) & 1);
}


// 2�̈����̕����������ł��邩�`�F�b�N
template <typename T1, typename T2> inline bool EqualSign( T1 x, T2 y )
{
	return IsSigned( x ) & IsSigned( y );
}



//-----------------------------------------------------------//
// ��Βl�쐬
//-----------------------------------------------------------//
template <typename T> inline T Abs( T x )
{
	return IsSigned( x ) ? x : -x;
}

template <> inline float Abs <float> ( float x )
{
	iFloat f( x );
	f.iVal &= 0x7FFFFFFF;
	return f.fVal; 
}


//-----------------------------------------------------------//
// 0�`�F�b�N (0�̎��^)
//-----------------------------------------------------------//
template < typename T > inline bool IsZero( T val )
{
	return !val;
}

template <> inline bool IsZero < float > ( float val )
{
	return Abs( val ) <= ZERO;		// �����ɂ͎኱��肠�肾���A�ő��ɂ͕\�ʉ����Ȃ��̂ł����
}


//-----------------------------------------------------------//
// ���W�A���g�p�p���[�e�B���e�B	
//-----------------------------------------------------------//

// �e�탉�W�A���p
const float _360rad	= _PI*2;
const float _90rad	= _PI/2;
const float _60rad	= _PI/3;
const float _45rad	= _PI/4;
const float _30rad	= _PI/6;
const float _div360 = 1.0f / _360rad;
const float _divPI  = 1.0f / _PI;


//--------------------------------------
// ���W�A���p�͈͕̔␳
//--------------------------------------

// -�΁`�΂ɕ␳
inline float ClampRadian( float f )
{
	if( Abs( f ) > _PI )
	{
		f -= (_360rad * (short)(f * _div360));
		if( Abs( f ) > _PI )
			f -= iFloat( (int)((iFloat( f ).iVal & 0x80000000) | iFloat( _360rad ).iVal) ).fVal;
	}
	return f; 
}


// 0�`2�΂ɕ␳
inline float ClampRadian2Pi( float f )
{
	float rad =  ClampRadian( f );
	return  IsSigned( rad ) ? rad : rad + _360rad;
}


//--------------------------------------
// ���W�A���E�x�����ݕϊ�
//--------------------------------------

// �x�����烉�W�A���p�ɕϊ�
const float toRadConst = _PI / 180.0f;

inline float toRAD( float f )
{
	return f * toRadConst;
}

// ���W�A���p����x���@�ɕϊ�
const float toDegConst = 180.0f * _divPI;

inline float toDEG( float f )
{
	return f * toDegConst;
}

//--------------------------------------
// �؂�ւ��p�}�N��
//--------------------------------------
#ifdef ___USE_RADIAN___			// ���W�A���g�p��
#define RAD( rad )		rad
#define DEG( rad )		toDEG( rad )
#define ANGLE_TYPE( f ) RAD( f ) // �g�p���̌^�ɍ��킹��
#else							// �x���@�g�p��
#define RAD( deg )		toRAD( deg )
#define DEG( deg )		deg
#define ANGLE_TYPE( f ) DEG( f )
#endif		// #ifdef ___USE_RADIAN___



//-----------------------------------------------------------//
// �����͈͕␳
//-----------------------------------------------------------//
const float RAND_DIV   = 1.0f / (RAND_MAX+1);
const float RAND_DIV_F = 1.0f / RAND_MAX;


// 0�`�w��ő�l�܂ł̗������擾
template <typename T> inline T Rand( T max )
{
	return static_cast<T> (std::rand() * (max + 1) * RAND_DIV);
}


template <> inline float Rand <float> ( float max )
{
	return std::rand() * max * RAND_DIV_F;
}


// �w��ŏ��l�`�w��ő�l�܂ł̗������擾
template <typename T> inline T Rand( T max, T min )
{
	T range = max - min;
	return static_cast<T> (std::rand() * (range + 1) * RAND_DIV) + min;
}


template <> inline float Rand <float> ( float max, float min )
{
	float range = max - min;
	return (std::rand() * range * RAND_DIV_F) + min;
}


//-----------------------------------------------------------//
// �X���b�v����
//-----------------------------------------------------------//
template <typename T> inline void Swap( T &a, T &b )
{
	T c = a;
	a = b;
	b = c;
}


//-----------------------------------------------------------//
// �ő�E�ŏ�
// �C���X�^���X������h�����߁A�Q�Ƃ�Ԃ�
//-----------------------------------------------------------//
template <typename T> inline const T &Max( const T &a, const T &b )
{
	return a > b ? a : b;
}

template <typename T> inline const T &Min( const T &a, const T &b )
{
	return a < b ? a : b;
}


//-----------------------------------------------------------//
// ��Βl�ɂ��ő�ŏ�
// �C���X�^���X������h�����߁A�Q�Ƃ�Ԃ�
//-----------------------------------------------------------//
template <typename T> inline const T &AbsMax( const T &a, const T &b )
{
	return Abs(a) > Abs(b) ? a : b;
}

template <typename T> inline const T &AbsMin( const T &a, const T &b )
{
	return Abs(a) < Abs(b) ? a : b;
}



//-----------------------------------------------------------//
// �z����̍ő�E�ŏ�
// �i�K�؂Ȓl��Ԃ��Ȃ����߁jNULL�`�F�b�N��T�C�Y�`�F�b�N��
// �s��Ȃ��̂ŁA�Ăяo���O�Ƀ`�F�b�N���邱��
//-----------------------------------------------------------//
template <typename T> inline const T &MaxInAry( const T *ary, size_t length )
{
	const T *temp = &ary[0];
	for( size_t i = 1; i < length; i++ )
	{
		if( ary[i] > *temp )
			temp = &ary[i];
	}
	return *temp;
}


template <typename T> inline const T &MinInAry( const T *ary, size_t length )
{
	const T	*temp = &ary[0];
	for( size_t i = 1; i < length; i++ )
	{
		if( ary[i] < *temp )
			temp = &ary[i];
	}
	return *temp;
}


//-----------------------------------------------------------//
// ��Βl�ɂ��z����̍ő�E�ŏ�
// �i�K�؂Ȓl��Ԃ��Ȃ����߁jNULL�`�F�b�N��T�C�Y�`�F�b�N��
// �s��Ȃ��̂ŁA�Ăяo���O�Ƀ`�F�b�N���邱��
//-----------------------------------------------------------//
template <typename T> inline const T &AbsMaxInAry( const T *ary, size_t length )
{
	const T *temp  = &ary[0];
	T		absMax = Abs( ary[0] );
	for( size_t i = 1; i < length; i++ )
	{
		if( Abs(ary[i]) > absMax )
		{
			temp   = &ary[i];
			absMax = Abs( ary[i] );
		}
	}
	return *temp;
}


template <typename T> inline const T &AbsMinInAry( const T *ary, size_t length )
{
	const T *temp  = &ary[0];
	T		absMin = Abs( ary[0] );
	for( size_t i = 1; i < length; i++ )
	{
		if( Abs(ary[i]) < absMin )
		{
			temp   = &ary[i];
			absMin = Abs( ary[i] );
		}
	}
	return *temp;
}



//-----------------------------------------------------------//
// �x�N�^��
// �ő�E�ŏ��v�f�擾
//-----------------------------------------------------------//
#ifdef _VECTOR_		// if included std::vector

#define _TEMPLATE_VECTOR	std::vector<T>

template <typename T> inline const T &MaxVector( const _TEMPLATE_VECTOR &vct )
{
	_TEMPLATE_VECTOR::const_iterator	iter = vct.begin();
	_TEMPLATE_VECTOR::const_iterator	end  = vct.end();
	const T		*temp = &(*iter);

	while( iter != end )
	{
		if( *iter > *temp )
			temp = &(*iter);
		iter++;
	}
	return *temp;
}


template <typename T> inline const T &MinVector( const _TEMPLATE_VECTOR &vct )
{
	_TEMPLATE_VECTOR::const_iterator	iter = vct.begin();
	_TEMPLATE_VECTOR::const_iterator	end  = vct.end();
	const T		*temp = &(*iter);

	while( iter != end )
	{
		if( *iter < *temp )
			temp = &(*iter);
		iter++;
	}
	return *temp;
}
#undef	_TEMPLATE_VECTOR
#endif	// #ifdef _VECTOR_


//-----------------------------------------------------------//
// ���X�g��
// �ő�E�ŏ��v�f�擾
//-----------------------------------------------------------//
#ifdef _LIST_	// if included std::list

#define _TEMPLATE_LIST	std::list<T>

template <typename T> inline const T &MaxList( const _TEMPLATE_LIST &list )
{
	_TEMPLATE_LIST::const_iterator	iter = list.begin();
	_TEMPLATE_LIST::const_iterator	end  = list.end();
	const T		*temp = &(*iter);

	while( iter != end )
	{
		if( *iter > *temp )
			temp = &(*iter);
		iter++;
	}
	return *temp;
}


template <typename T> inline const T &MinList( const _TEMPLATE_LIST &list )
{
	_TEMPLATE_LIST::const_iterator	iter = list.begin();
	_TEMPLATE_LIST::const_iterator	end  = list.end();
	const T		*temp = &(*iter);

	while( iter != end )
	{
		if( *iter < *temp )
			temp = &(*iter);
		iter++;
	}
	return *temp;
}
#undef _TEMPLATE_LIST
#endif	// #ifdef _LIST_


//-----------------------------------------------------------//
// �}�b�v��
// �ő�E�ŏ��v�f�擾
//-----------------------------------------------------------//
#ifdef _MAP_ // if included std::map

#define _TEMPLATE_MAP	std::map<T, T2>

// �L�[��Ԃ��o�[�W����
template <typename T, typename T2> inline const T &MaxMapKey( const _TEMPLATE_MAP &m )
{
	_TEMPLATE_MAP::const_iterator	iter = m.begin();
	_TEMPLATE_MAP::const_iterator	end  = m.end();
	const T		*temp = &iter->first;

	while( iter != end )
	{
		if( iter->first > *temp )
			temp = &iter->first;
		iter++;
	}
	return *temp;
}


template <typename T, typename T2> inline const T &MinMapKey( const _TEMPLATE_MAP &m )
{
	_TEMPLATE_MAP::const_iterator	iter = m.begin();
	_TEMPLATE_MAP::const_iterator	end  = m.end();
	const T		*temp = &iter->first;

	while( iter != end )
	{
		if( iter->first < *temp )
			temp = &iter->first;
		iter++;
	}
	return *temp;
}


// �l��Ԃ��o�[�W����
template <typename T, typename T2> inline const T2 &MaxMapVal( const _TEMPLATE_MAP &m )
{
	_TEMPLATE_MAP::const_iterator	iter = m.begin();
	_TEMPLATE_MAP::const_iterator	end  = m.end();
	const T		*temp1 = &iter->first;
	const T2	*temp2 = &iter->second;

	while( iter != end )
	{
		if( iter->first > *temp1 )
			temp2 = &iter->second;
		iter++;
	}
	return *temp2;
}


template <typename T, typename T2> inline const T2 &MinMapVal( const _TEMPLATE_MAP &m )
{
	_TEMPLATE_MAP::const_iterator	iter = m.begin();
	_TEMPLATE_MAP::const_iterator	end  = m.end();
	const T		*temp1 = &iter->first;
	const T2	*temp2 = &iter->second;

	while( iter != end )
	{
		if( iter->first < *temp1 )
			temp2 = &iter->second;
		iter++;
	}
	return *temp2;
}
#undef _TEMPLATE_MAP
#endif	// #ifdef _MAP_


//-----------------------------------------------------------//
// �l�N�����v
//-----------------------------------------------------------//

// �����𒼐ڃN�����v����o�[�W����
template <typename T> inline T &ClampSet( T &val, const T max, const T min )
{
	if( val > max )
		val = max;
	else if( val < min )
		val = min;
	return val;
}

template <typename T> inline T &ClampMaxSet( T &val, const T max )
{
	if( val > max )
		val = max;
	return val;
}

template <typename T> inline T &ClampMinSet( T &val, const T min )
{
	if( val < min )
		val = min;
	return val;
}

// �N�����v�l���擾����o�[�W����
template <typename T> inline const T ClampRtn( const T val, const T max, const T min )
{
	if( val > max )
		return max;
	else if( val < min )
		return min;
	return val;
}

template <typename T> inline const T ClampMaxRtn( const T val, const T max )
{
	if( val > max )
		return  max;
	return val;
}

template <typename T> inline const T ClampMinRtn( const T val, const T min )
{
	if( val < min )
		return min;
	return val;
}


//-----------------------------------------------------------//
// �F�萔
//-----------------------------------------------------------//
const DWORD WHITE		= 0xFFFFFFFF;
const DWORD RED			= 0xFFFF0000;
const DWORD GREEN		= 0xFF00FF00;
const DWORD BLUE		= 0xFF0000FF;
const DWORD YELLOW		= 0xFFFFFF00;
const DWORD LIGHTBLUE	= 0xFF00FFFF;
const DWORD PURPLE		= 0xFFFF00FF;
const DWORD BLACK		= 0xFF000000;



#endif // ___LIB_HEADER___