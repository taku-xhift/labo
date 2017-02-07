//-----------------------------------------------------------------------
//! @file	LibHeader.h
//! @brief	ライブラリ用各種宣言・汎用処理
//!	@author	伊藤貴徳 
//
//! @date	07/07/15：再編
//! @date	07/09/01：スワップ処理追加
//!	@date	07/09/02：最大･最小、値クランプを追加
//-----------------------------------------------------------------------

/* !! double型は原則扱わないので使用時には注意 !! */

#ifndef ___LIB_HEADER___
#define ___LIB_HEADER___


#define _CRT_SECURE_NO_DEPRECATE						// 旧形式の関数使用
#pragma warning (disable : 4819)						// ファイルは、現在のコード ページx で表示できない文字を含んでいます


#include <cmath>
#include <cstdlib>
#include <cassert>


//-----------------------------------------------------------//
// マクロ設定
//-----------------------------------------------------------//
#define ___USE_RADIAN___		//角度としてラジアンを使う
#define ___USE_D3DX___
//#define ___USE_OPEN_GL___


#define ZERO		0.0001f		// 許容小数誤差最大値
#define SLERP_MAX	.95f		// 球面線形補間から線形補間に変えるボーダー値


//-----------------------------------------------------------//
// 型定義
//-----------------------------------------------------------//

// 配列参照型
#ifdef  _WIN64
typedef __int64			differ_type;		// 添え字アクセス用
#else
typedef _W64 int		differ_type;
#endif

// ポインタ型
#ifdef _WP64
typedef unsigned __int64	ptr_type; 
#else
typedef	size_t				ptr_type;
#endif



//-----------------------------------------------------------//
// DirectX使用時の設定 
//-----------------------------------------------------------//
#ifdef ___USE_D3DX___


#include <d3dx9math.h>

#define	 _PI				D3DX_PI


#define ___USE_HLSL___					// シェーダ形式
//#define ___USE_ASM_SHADER___			// 最適化のため、形式によってデータの持ち方を変える必要あり 


#ifdef ___USE_HLSL___

#define ___USE_MTX_COL_MAJOR___			// 列順に行列を格納
//#define ___USE_MTX_ROW_MAJOR___			// 行順に行列を格納

#elif	defined(___USE_ASM_SHADER___)

#define ___USE_MTX_ROW_MAJOR___			// 行順に行列を格納

#endif	// ifdef ___USE_HLSL___



//-----------------------------------------------------------//
// OpenGL使用時の設定
//-----------------------------------------------------------//
#elif  defined(___USE_OPEN_GL___)


#define _PI				3.1415926535897932384626433832795f
#define NULL			0

#define ___USE_MTX_COL_MAJOR___			// 列順に行列を格納


#endif //___USE_D3DX___


//-----------------------------------------------------------//
// windef.hのデータ定義
//-----------------------------------------------------------//
#ifndef _WINDEF_
#include <windef.h>
#endif	// ifndef _WINDEF_


//-----------------------------------------------------------//
// 定数値
//-----------------------------------------------------------//
const float	_e		= 2.71828182845904523536f;
const float _log2	= 1.44269504088896340736f;
const float	_log10	= 0.434294481903251827651f;
const float _root2	= (float)1.4142135623730950488016887242097;
const float _root3	= (float)1.7320508075688772935274463415059;
const float _s60c30 = 2.0f / _root3;	// サイン60＆コサイン30度
const float _sc45   = 1.0f / _root2;	// サイン・コサイン45度



//-----------------------------------------------------------//
// float 型でビット操作をするための共用体
//-----------------------------------------------------------//
typedef union uINT_FLOAT
{
	//---------------------//
	// メンバ
	//---------------------//
	int		iVal;
	float	fVal;


	//---------------------//
	// コンストラクタ
	//---------------------//
	uINT_FLOAT( float f ) : fVal(f) {}
	uINT_FLOAT( int   i ) : iVal(i) {}


	// 符号取得
	static int FloatSign( float f )		{ return (iFloat( f ).iVal >> 31);}

	// 指数部取得
	static int FloatIndex( float f )	{ return (iFloat( f ).iVal >> 23) & 0x0FF;}

	// 仮数部取得
	static int FloatMantissa( float f )	{ return (iFloat( f ).iVal & 0x007FFFFF);}

	// NaNを強制設定する
	static float &SetNaN( float &f )	{ *((int*)&f) = 0x7FFFFFFF;	return f;}

	// NaNか調べる
	static bool IsNaN( float f )		{ return (*((int*)&f) & 0x7F800000) && (*((int*)&f) & 0x007FFFFF);}

	// QNaNを強制設定する
	static float &SetQNaN( float &f )	{ *((int*)&f) = 0x7FFFFFFF;	return f;}

	// QNaNか調べる
	static bool IsQNaN( float f )		{ return !!(*((int*)&f) & 0x7FC00000);}

	// SNaNを強制設定する
	static float &SetSNaN( float &f )	{ *((int*)&f) = 0x7FBFFFFF;	return f;}

	// SNaNか調べる
	static bool IsSNaN( float f )		{ return (*((int*)&f) & 0x7F000000) && (*((int*)&f) & 0x003FFFFF);}

	// 無限設定
	static float &SetInfinity( float &f, bool minus )
	{
		*((int*)&f) = minus ? 0x7F800000 : 0xFF800000;
		return f;
	}

	// 無限か調べる
	static bool IsInfinity( float f )	{ return (*((int*)&f) & 0x7FFFFFFF) == 0x7F800000;}

}iFloat;



//-----------------------------------------------------------//
// 符号関連
//-----------------------------------------------------------//

// 正負の判定（正のときtrue 0は正に含まれる ）
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


// 2つの引数の符号が同じであるかチェック
template <typename T1, typename T2> inline bool EqualSign( T1 x, T2 y )
{
	return IsSigned( x ) & IsSigned( y );
}



//-----------------------------------------------------------//
// 絶対値作成
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
// 0チェック (0の時真)
//-----------------------------------------------------------//
template < typename T > inline bool IsZero( T val )
{
	return !val;
}

template <> inline bool IsZero < float > ( float val )
{
	return Abs( val ) <= ZERO;		// 厳密には若干問題ありだが、滅多には表面化しないのでこれで
}


//-----------------------------------------------------------//
// ラジアン使用用ユーティリティ	
//-----------------------------------------------------------//

// 各種ラジアン角
const float _360rad	= _PI*2;
const float _90rad	= _PI/2;
const float _60rad	= _PI/3;
const float _45rad	= _PI/4;
const float _30rad	= _PI/6;
const float _div360 = 1.0f / _360rad;
const float _divPI  = 1.0f / _PI;


//--------------------------------------
// ラジアン角の範囲補正
//--------------------------------------

// -π～πに補正
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


// 0～2πに補正
inline float ClampRadian2Pi( float f )
{
	float rad =  ClampRadian( f );
	return  IsSigned( rad ) ? rad : rad + _360rad;
}


//--------------------------------------
// ラジアン・度数相互変換
//--------------------------------------

// 度数からラジアン角に変換
const float toRadConst = _PI / 180.0f;

inline float toRAD( float f )
{
	return f * toRadConst;
}

// ラジアン角から度数法に変換
const float toDegConst = 180.0f * _divPI;

inline float toDEG( float f )
{
	return f * toDegConst;
}

//--------------------------------------
// 切り替え用マクロ
//--------------------------------------
#ifdef ___USE_RADIAN___			// ラジアン使用時
#define RAD( rad )		rad
#define DEG( rad )		toDEG( rad )
#define ANGLE_TYPE( f ) RAD( f ) // 使用中の型に合わせる
#else							// 度数法使用時
#define RAD( deg )		toRAD( deg )
#define DEG( deg )		deg
#define ANGLE_TYPE( f ) DEG( f )
#endif		// #ifdef ___USE_RADIAN___



//-----------------------------------------------------------//
// 乱数範囲補正
//-----------------------------------------------------------//
const float RAND_DIV   = 1.0f / (RAND_MAX+1);
const float RAND_DIV_F = 1.0f / RAND_MAX;


// 0～指定最大値までの乱数を取得
template <typename T> inline T Rand( T max )
{
	return static_cast<T> (std::rand() * (max + 1) * RAND_DIV);
}


template <> inline float Rand <float> ( float max )
{
	return std::rand() * max * RAND_DIV_F;
}


// 指定最小値～指定最大値までの乱数を取得
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
// スワップ処理
//-----------------------------------------------------------//
template <typename T> inline void Swap( T &a, T &b )
{
	T c = a;
	a = b;
	b = c;
}


//-----------------------------------------------------------//
// 最大・最小
// インスタンス生成を防ぐため、参照を返す
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
// 絶対値による最大最小
// インスタンス生成を防ぐため、参照を返す
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
// 配列内の最大・最小
// （適切な値を返せないため）NULLチェックやサイズチェックは
// 行わないので、呼び出し前にチェックすること
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
// 絶対値による配列内の最大・最小
// （適切な値を返せないため）NULLチェックやサイズチェックは
// 行わないので、呼び出し前にチェックすること
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
// ベクタ版
// 最大・最小要素取得
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
// リスト版
// 最大・最小要素取得
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
// マップ版
// 最大・最小要素取得
//-----------------------------------------------------------//
#ifdef _MAP_ // if included std::map

#define _TEMPLATE_MAP	std::map<T, T2>

// キーを返すバージョン
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


// 値を返すバージョン
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
// 値クランプ
//-----------------------------------------------------------//

// 引数を直接クランプするバージョン
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

// クランプ値を取得するバージョン
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
// 色定数
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