//-----------------------------------------------------------
//! @fiule	CQuaternion.h
//! @brief	クォータオン
//! @author 伊藤貴徳
//! @date	07/07/15：再編
//! @date	08/02/11：全体を整理
//-----------------------------------------------------------


#ifndef ___QUATERNION_H___
#define ___QUATERNION_H___


//#include "Core/Utility/LibHeader.h"
#include "VecMtx.h"


//------------------------------------------------------------------
// クォータニオンクラス
//------------------------------------------------------------------
class CQuaternion
{
public:
	// アクセス用列挙型
	enum { eX, eY, eZ, eW };

private:
	//--------------------------------------------------//
	// メンバ変数
	//--------------------------------------------------//
	union
	{
		float			val[4];
public :
		struct
		{
			Vec3		v;
			float		w;
		};
	};


public:
	//--------------------------------------------------//
	// コンストラクタ
	//--------------------------------------------------//
	CQuaternion();
	CQuaternion( const Vec3 &V, float w );
	CQuaternion( float x, float y, float z, float w );
	CQuaternion( const float * );
	CQuaternion( const CQuaternion &q );
	CQuaternion( const Mtx &M );

	CQuaternion( const D3DXVECTOR3    &V, float w );
	CQuaternion( const D3DXVECTOR4    &V );
	CQuaternion( const D3DXQUATERNION &Q );
	CQuaternion( const D3DXMATRIX	  &M );


	~CQuaternion();


	//--------------------------------------------------//
	// セット用
	//--------------------------------------------------//
	CQuaternion &Set( const Vec3 &V, float w );
	CQuaternion &Set( float x, float y, float z, float w);
	CQuaternion &Set( const float * );
	CQuaternion &Set( const Mtx & );

	CQuaternion &Set( const D3DXVECTOR3 &, float w );
	CQuaternion &Set( const D3DXVECTOR4 & );
	CQuaternion &Set( const D3DXQUATERNION & );
	CQuaternion &Set( const D3DXMATRIX & );


	//--------------------------------------------------//
	// D3DX型との相互互換
	//--------------------------------------------------//
	D3DXQUATERNION &toD3DQuat( D3DXQUATERNION &Q )		const;
	D3DXMATRIX     &toD3DMtx ( D3DXMATRIX     &M )		const;

	operator D3DXQUATERNION ()							const;
	operator D3DXMATRIX		()							const;

	// D3DX型からの代入に対処
	CQuaternion &operator = ( const D3DXQUATERNION & );
	CQuaternion &operator = ( const D3DXMATRIX & );



	//--------------------------------------------------//
	// 代入演算子
	//--------------------------------------------------//
	CQuaternion &operator = ( const CQuaternion &Q  );
	CQuaternion &operator = ( const Mtx & M  );


	//--------------------------------------------------//
	// 大きさ、向きなど
	//--------------------------------------------------//
	float     &operator [] ( differ_type i );
	float      operator [] ( differ_type i )	const;
	CQuaternion operator - ()					const;
	float Norm2()								const;
	float Norm()								const;
	const float *Ptr()							const;
	operator const float * ()					const;
	operator       float * ();


	/***********************************************************/
	// 各種演算子
	/***********************************************************/

	//--------------------------------------------------//
	// ２項演算子
	//--------------------------------------------------//
	
	// 標準演算
	CQuaternion operator + ( const CQuaternion &Q  )	const;
	CQuaternion operator - ( const CQuaternion &Q  )	const;
	CQuaternion operator * ( float f )					const;
	CQuaternion operator / ( float f )					const;

	CQuaternion operator * ( const CQuaternion &Q  )	const;


	// 代入演算
	CQuaternion &operator += ( const CQuaternion &Q  );
	CQuaternion &operator -= ( const CQuaternion &Q  );
	CQuaternion &operator *= ( float f );
	CQuaternion &operator /= ( float f );

	CQuaternion &operator *= ( const CQuaternion &Q  );

	// フレンド
	friend CQuaternion  operator * ( float f, const CQuaternion & );


	//--------------------------------------------------//
	// 論理演算
	//--------------------------------------------------//
	bool operator == ( const CQuaternion &Q  )			const;
	bool operator != ( const CQuaternion &Q  )			const;

	
	//--------------------------------------------------//
	// その他
	//--------------------------------------------------//
	CQuaternion &Normalize();
	bool IsNormal()										const;
	bool Zero()											const;

};

typedef CQuaternion	Quat;



//----------------------------------------------------------//
// クラス外関数
//----------------------------------------------------------//

//-----------------------------------------------------
// 演算関数
//-----------------------------------------------------
Quat &QuatAdd( Quat &Qo, const Quat &Qi1, const Quat &Qi2 );	// 加算
Quat &QuatSub( Quat &Qo, const Quat &Qi1, const Quat &Qi2 );	// 減算
Quat &QuatMul( Quat &Qo, const Quat &Qi1, const Quat &Qi2 );	// 乗算
Quat &QuatMul( Quat &Qo, const Quat &Qi,  float f );
Quat &QuatDiv( Quat &Qo, const Quat &Qi,  float fa );			// 除算
float QuatDot( const Quat &pQ1, const Quat &pQ2 );				// 内積



//-----------------------------------------------------
// 各種処理
//-----------------------------------------------------
Quat &QuatNormalize  ( Quat &Qo, const Quat &Qi );				// 単位化
Quat &QuatReverse    ( Quat &Qo, const Quat &Qi );				// 反転
Quat &QuatConjugugate( Quat &Qo, const Quat &Qi );				// 共役
Quat &QuatInverse    ( Quat &Qo, const Quat &Qi );				// 逆元
Quat &QuatRotation   ( Quat &Qo, const Vec3 &Vaxis, float rot );// 回転  軸は内部で正規化される
Mtx  &QuatRotation   ( Mtx  &Mo, const Vec3 &Vaxis, float rot );
Quat &QuatRotationYPR( Quat &Qo, const Vec3 &Rot );				// ヨーピッチロール回転
Mtx  &QuatRotationYPR( Mtx  &Mo, const Vec3 &Rot );
Quat &QuatSlerp      ( Quat &Qo, const Quat &Qorig, const Quat &Qtgt, float t );	// 球面線形補完


#include "Quaternion.inl"


#endif
