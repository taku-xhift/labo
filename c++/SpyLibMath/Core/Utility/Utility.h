//------------------------------------------------------------------
//! @file	Utility.h
//! @brief	各種汎用マクロ処理
//! @author	伊藤貴徳
//! @date	07/07/14
//------------------------------------------------------------------


#ifndef ___UTILITY_H___
#define ___UTILITY_H___


#define ___OPTIMIZE___		// 最適化重視


// マクロに基づく設定
#ifdef ___OPTIMIZE___
#define inline	__forceinline

#else
#define inline	inline

#endif


//---------------------------------------------------//
// 汎用ビットフラグチェック
//---------------------------------------------------//
#ifndef BIT_FLAG_CHECK
#define BIT_FLAG_CHECK( target, flag )			( ( (target) & (flag) ) == (flag) )
#endif


//---------------------------------------------------//
// 汎用エラーチェック
//---------------------------------------------------//

// マクロによるエラーチェック
#ifndef VALUE_CHECK
#define VALUE_CHECK( target, val, rtnCode )		if( (target) == (val) ) return (rtnCode);
#endif

// マクロによるNULLチェック 
#ifndef NULL_CHECK
#define NULL_CHECK( obj, rtnCode )				if( !(obj) ) { \
													SPY_ASSERT( obj, (_T("NULLが見つかりました")) ); \
													return (rtnCode); \
												}
#endif


//---------------------------------------------------//
// 削除
//---------------------------------------------------//

// チェックつき削除
#ifndef SAFE_DELETE
#define SAFE_DELETE( pObj )						if( pObj ) { delete pObj;    pObj = NULL;}
#endif

// チェックつき配列削除
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( pObj )				if( pObj ) { delete [] pObj; pObj = NULL;}
#endif

// チェックつき解放
#ifndef SAFE_FREE
#define SAFE_FREE( pObj )						if( pObj ) { free( pObj );	 pObj = NULL;}
#endif

// ハンドルクローズ
#ifndef SAFE_CLOSE
#define	SAFE_CLOSE( handle )					if( handle ) { ::CloseHandle( handle ); handle = NULL;}
#endif



//---------------------------------------------------//
// D3D用解放
//---------------------------------------------------//
#ifndef SAFE_RELEASE
#define SAFE_RELEASE( pObj )					if( pObj ) { pObj->Release(); pObj = NULL;}
#endif


//---------------------------------------------------//
// 文字列変換
//---------------------------------------------------//
#ifndef TO_STRING
#define TO_STRING( str )	#str
#endif


#endif // #ifndef ___UTILITY_H___