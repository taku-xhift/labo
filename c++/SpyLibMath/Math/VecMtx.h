//-----------------------------------------------------------------------------------
//! @file	VecMtx.h
//! @brief	2-4次元ベクトルと4x4の行列
//! @author	伊藤貴徳
//! @date	07/07/15：再編
//! @date	07/08/05：行列メソッドに各種変換行列作成を追加
//! @date	07/08/11：２次元＆４次元ベクトルを追加
//! @date			  ベクトルの追加に伴うオーバーロード強化
//! @date	07/08/26：行列のアクセッサを強化
//! @date			  行列のＬＵ分解を追加
//! @date	07/09/01：逆行列計算をＬＵ分解を用いたものに変更
//! @date			  ベクトルの任意軸回転を追加
//! @date	07/09/08：行列に()演算子追加
//! @date	08/02/11：全体を整理
//-----------------------------------------------------------------------------------

// 2-4次元ベクトル&4*4行列

#ifndef ___VEC_AND_MTX_H___
#define ___VEC_AND_MTX_H___

#include "../Core/Utility/LibHeader.h"


#include <cmath>

#include <cstdlib>
#define _USE_LH_			// ビュー行列とプロジェクション行列の作成時に左手系で作成する
#include <d3dx9math.h>


typedef _W64 int		differ_type;


class CVector3;
class CMatrix44;
class CQuaternion;
// 行列→ベクトル変換時の選択
enum eMtxToVec { kTNoW,		// 平行移動つき、w除算無し（デフォルト）
				 kNoTNoW,	// 平行移動無し、w除算無し（法線計算）
				 kTW,		// 平行移動つき、w除算あり
				 kNoTW		// 平行移動無し、w除算あり
			   };





//===============================================================================//
//  ３次元ベクトルクラス
//===============================================================================//
class CVector3
{
public:
	// アクセス用列挙
	enum { eX, eY, eZ };

private:
	//--------------------------------------------------//
	// メンバ変数
	//--------------------------------------------------//
	union
	{
		float val[3];
public:
		struct
		{
			float x, y, z;
		};
	};


public:
	//--------------------------------------------------//
	// 各種コンストラクタ
	//--------------------------------------------------//
	CVector3();
	CVector3( float x, float y, float z=0 );
	CVector3( const float *);
	CVector3( const CVector3 &v );
	CVector3( const CVector3 &Vto, const CVector3 &Vfor );	///< pVto->pVforベクトルを作成
	CVector3( const CMatrix44&M, eMtxToVec = kTNoW );

	CVector3( const D3DXVECTOR2 &D3dVec, float z=0 );
	CVector3( const D3DXVECTOR3 &D3dVec );
	CVector3( const D3DXVECTOR4 &D3dVec, bool w = false );		///< w=trueでｗ除算を行う
	CVector3( const D3DXVECTOR2 &D3dVto, const D3DXVECTOR2 &D3dVfor, float z=0 );
	CVector3( const D3DXVECTOR3 &D3dVto, const D3DXVECTOR3 &D3dVfor );
	CVector3( const D3DXMATRIX  &DxMtx, eMtxToVec = kTNoW );

	~CVector3();


	//--------------------------------------------------//
	// セット
	//--------------------------------------------------//
	CVector3 &Set( float x, float y, float z=0.0f );
	CVector3 &Set( const float *p );
	CVector3 &Set( const CVector3 &Vto, const CVector3 &Vfor );
	CVector3 &Set( const CMatrix44&, eMtxToVec = kTNoW );

	CVector3 &Set( const D3DXVECTOR2 &D3dVec, float z=0 );
	CVector3 &Set( const D3DXVECTOR3 &D3dVec );
	CVector3 &Set( const D3DXVECTOR4 &D3dVec, bool w = false );///< w=trueでｗ除算を行う
	CVector3 &Set( const D3DXVECTOR2 &D3dVto, const D3DXVECTOR2 &D3dVfor, float z=0 );
	CVector3 &Set( const D3DXVECTOR3 &D3dVto, const D3DXVECTOR3 &D3dVfor );
	CVector3 &Set( const D3DXMATRIX  &DxMtx, eMtxToVec = kTNoW );


	//--------------------------------------------------//
	// D3DX型との互換
	//--------------------------------------------------//


	// D3DX型への変換用
	D3DXVECTOR3 &toD3DVEC3( D3DXVECTOR3 &Dv3 )					const;
	D3DXVECTOR4 &toD3DVEC4( D3DXVECTOR4 &Dv3, float w = 1.0f )	const;
	D3DXMATRIX  &toD3DMTX ( D3DXMATRIX  &D3m )					const;

	operator D3DXVECTOR3 ()	const;
	operator D3DXMATRIX	 ()	const;


	// D3DX型からの代入に対処
	CVector3 &operator = ( const D3DXVECTOR2 &v  );
	CVector3 &operator = ( const D3DXVECTOR3 &v  );
	CVector3 &operator = ( const D3DXVECTOR4 &v  );				///< w除算なし
	CVector3 &operator = ( const D3DXMATRIX  &m  );


	//--------------------------------------------------//
	// 代入
	//--------------------------------------------------//
	CVector3 &operator = ( const CVector3  &v  );
	CVector3 &operator = ( const CMatrix44 &m  );


	//--------------------------------------------------//
	// 各種２項演算
	//--------------------------------------------------//

	// 標準演算
	CVector3 operator + ( const CVector3 &v2 )	const;
	CVector3 operator - ( const CVector3 &v2 )	const;
	CVector3 operator * ( float f )				const;
	CVector3 operator / ( float f )				const;

	friend CVector3 operator * ( float f, const CVector3& );
	friend CVector3 operator / ( float f, const CVector3& );


	// 代入演算
	CVector3 &operator += ( const CVector3 &v2 );
	CVector3 &operator -= ( const CVector3 &v2 );
	CVector3 &operator *= ( float f );
	CVector3 &operator /= ( float f );


	// 行列との演算
	CMatrix44 operator *( const CMatrix44 &rM )  const;


	//--------------------------------------------------//
	// 単項演算ほか
	//--------------------------------------------------//
	//float  &operator [] ( differ_type i );
	//float   operator [] ( differ_type i )		const;
	CVector3 operator - ()						const;		// 向きを反転
	float Norm2()								const;		// 大きさの２乗を返す
	float Norm()								const;		// ベクトルの大きさを返す
	const float *Ptr()							const;
	operator const float *()					const;
	operator       float *();


	//--------------------------------------------------//
	// 論理演算
	//--------------------------------------------------//
	bool operator == ( const CVector3 &v2 )		const;
	bool operator != ( const CVector3 &v2 )		const;


	//--------------------------------------------------//
	// 極座標との互換
	//--------------------------------------------------//

	// 極座標を作成
	// (0,0,1)を基準(回転角θ、仰角φが共に0)とする
	CVector3 &PolarCoordinate( float r, float theta, float phi );

	// 中心までの距離を変更する
	CVector3 &ChangePolarCoordinateR( float r );


	//--------------------------------------------------//
	// その他
	//--------------------------------------------------//
	CVector3 &Normalize();								// 単位化
	bool IsNormal()								const;	// 単位ベクトルであるか判定
	bool IsZeroVec()							const;	// ゼロベクトルであるか判定
	float Dist ( const CVector3 & )				const;	// 距離を求める
	float Dist2( const CVector3 & )				const;	// 距離の2乗を求める

	void MakeFloor( const CVector3 &v2 )
	{
		if (v2.x < x) x = v2.x;
		if (v2.y < y) y = v2.y;
		if (v2.z < z) z = v2.z;
	}

	void MakeCeil( const CVector3 &v2 )
	{
		if (v2.x > x) x = v2.x;
		if (v2.y > y) y = v2.y;
		if (v2.z > z) z = v2.z;
	}

	// 佐藤@
	CVector3 Normal() const;
	CVector3 Vertical() const;

};

typedef CVector3	Vec3;



//-----------------------------------------------------------------------//
// 各種２項演算
//-----------------------------------------------------------------------//
Vec3 &Vec3Add( Vec3 &pVo, const Vec3 &pVi, const Vec3 &pVi2);		// 加算
Vec3 &Vec3Sub( Vec3 &pVo, const Vec3 &pVi, const Vec3 &pVi2);		// 減算
Vec3 &Vec3Mul( Vec3 &pVo, const Vec3 &pVi, float  f );		// 乗算
Vec3 &Vec3Div( Vec3 &pVo, const Vec3 &pVi, float  f );		// 除算



//-----------------------------------------------------------------------//
// ベクトル演算
//-----------------------------------------------------------------------//
Vec3 &Vec3Reverse    ( Vec3 & pVo,  const Vec3 &pVi );				// 逆向きを作成
Vec3 &Vec3Normalize  ( Vec3 & pVo,  const Vec3 &pVi );				// 単位化
float Vec3Dot        ( const Vec3 &pV1,  const Vec3 &pV2 );				// 内積
Vec3 &Vec3Cross      ( Vec3 & pVo,  const Vec3 &pVi,  const Vec3 &pVi2);	// 外積
float Vec3CrossAngle ( const Vec3 &pV1,  const Vec3 &pV2 );				// 交角（角度はラジアン又は度数）
Vec3 &Vec3RotationAxisX( Vec3 &pVout, const Vec3 &pVin, float  rot );	// ベクトルを回転
Vec3 &Vec3RotationAxisY( Vec3 &pVout, const Vec3 &pVin, float  rot );
Vec3 &Vec3RotationAxisZ( Vec3 &pVout, const Vec3 &pVin, float  rot );
Vec3 &Vec3RotationAxis ( Vec3 &pVout, const Vec3 &pVin, const Vec3 &pVaxis, float rot );
Vec3 &Vec3Lerp       ( Vec3 &pVout, const Vec3 &pVin1, const Vec3 &pVin2, float t );	// 線形補間
Vec3 &Vec3Hermite    ( Vec3 &pVout, const Vec3 &pVin1, const Vec3 &pVtan1, 
					  const Vec3 &pVin2, const Vec3 &pVtan2, float t );	// エルミート補間







//===============================================================================//
// 4*4行列クラス
//===============================================================================//

// 行列要素アクセス用列挙型

enum{ e11, e21, e31, e41, e12, e22, e32, e42, e13, e23, e33, e43, e14, e24, e34, e44 };


class CMatrix44
{
private :
	//--------------------------------------------------//
	// メンバ変数
	// 一次配列で用意
	// データの受け渡しを考え、
	// 列単位、行単位をdefineで変更可能にしてある
	//--------------------------------------------------//
	float m_m[16];


public :
	/*-----------------------------------------------------*/
	// 各種コンストラクタ
	/*-----------------------------------------------------*/
	CMatrix44( bool identity = true);							// 必要ならば単位行列で初期化する
	CMatrix44(	float _11, float _12, float _13, float _14,		// 全ての要素を明示的に指定
				float _21, float _22, float _23, float _24,
				float _31, float _32, float _33, float _34,
				float _41, float _42, float _43, float _44 );
	CMatrix44( const float *m );								//同上 配列で渡す
	CMatrix44( float x, float y, float z );						//ベクトルとして渡す
	CMatrix44( const CMatrix44 & );
	CMatrix44( const CVector3 &V );
	CMatrix44( const CQuaternion &Q );

	CMatrix44( const D3DXVECTOR2    &V );
	CMatrix44( const D3DXVECTOR3    &V );
	CMatrix44( const D3DXVECTOR4    &V );
	CMatrix44( const D3DXQUATERNION &Q );
	CMatrix44( const D3DXMATRIX     &M );


	~CMatrix44();



	/*-----------------------------------------------------*/
	// D3DX互換
	/*-----------------------------------------------------*/

	// D3DX型への変換及びD3DX型からの代入
	D3DXVECTOR2 &toD3DVEC2	 ( D3DXVECTOR2	  &V )	const;
	D3DXVECTOR3 &toD3DVEC3	 ( D3DXVECTOR3	  &V )	const;
	D3DXVECTOR4 &toD3DVEC4	 ( D3DXVECTOR4	  &V )	const;
	D3DXMATRIX  &toD3DMTX	 ( D3DXMATRIX	  &M )	const;
	D3DXQUATERNION &toD3DQUAT( D3DXQUATERNION &Q )	const;

	operator D3DXVECTOR2	()						const;
	operator D3DXVECTOR3	()						const;
	operator D3DXVECTOR4	()						const;
	operator D3DXMATRIX		()						const;
	operator D3DXQUATERNION ()						const;


	// 参照型
	CMatrix44 &operator = ( const D3DXVECTOR2	&v );
	CMatrix44 &operator = ( const D3DXVECTOR3	&v );
	CMatrix44 &operator = ( const D3DXVECTOR4	&v );
	CMatrix44 &operator = ( const D3DXMATRIX	&m );
	CMatrix44 &operator = ( const D3DXQUATERNION &q );



	/*-----------------------------------------------------*/
	// セット
	/*-----------------------------------------------------*/
	
	// 要素を指定して値をセット
	void SetVal( differ_type num, float val );
	void SetVal( differ_type row, differ_type col, float val );

	// 行セット
	void SetRow( differ_type colNo, float x, float y, float z, float trs );
	void SetRow( differ_type rowNo, const Vec3 &, float trs );

	// 列セット
	void SetCol( differ_type colNo, float x, float y, float z, float w );
	void SetCol( differ_type colNo, const Vec3 &, float w );

	// 一括セット
	CMatrix44 &Set( float _11, float _12, float _13, float _14,
					float _21, float _22, float _23, float _24,
					float _31, float _32, float _33, float _34,
					float _41, float _42, float _43, float _44 );
	CMatrix44 &Set( const float *pM );
	CMatrix44 &Set( float x, float y, float z );
	CMatrix44 &Set( const CVector3 &V );
	CMatrix44 &Set( const CQuaternion &Q );


	CMatrix44 &Set( const D3DXVECTOR2	 &V );
	CMatrix44 &Set( const D3DXVECTOR3	 &V );
	CMatrix44 &Set( const D3DXVECTOR4	 &V );
	CMatrix44 &Set( const D3DXQUATERNION &Q );
	CMatrix44 &Set( const D3DXMATRIX	 &M );



	/*-----------------------------------------------------*/
	// ゲット
	/*-----------------------------------------------------*/
	
	// 一括
	const float *GetMatrix()					const;
	float		*GetMatrix();
	float		*GetMatrix( float *pM )			const;
	operator const float*()						const;
	operator       float*();

	// 要素を指定して値を取得
	float &GetVal( differ_type i );
	float  GetVal( differ_type i )						const;
	float &GetVal( differ_type row, differ_type col );
	float  GetVal( differ_type row, differ_type col )	const;
	//float &operator [] ( differ_type i );
	//float  operator [] ( differ_type i )				const;
	float &operator () ( differ_type row, differ_type col );
	float  operator () ( differ_type row, differ_type col )		const;

	// 列取得
	Vec3  &GetCol( Vec3 &, differ_type colNo )			const;
	float *GetCol( float*, differ_type colNo )			const;

	// 行取得
	Vec3  &GetRow( Vec3 &, differ_type rowNo )			const;
	float *GetRow( float*, differ_type rowNo )			const;

	// ベクトル要素として取得
	// 平行移動成分含む
	float XT()									const;
	float XT2D()								const;	// z成分を無視する
	float YT()									const;
	float YT2D()								const;	// z成分を無視する
	float ZT()									const;
	float WT()									const;

	// 平行移動成分なし
	float XNoT()								const;
	float XNoT2D()								const;	// z成分を無視する
	float YNoT()								const;
	float YNoT2D()								const;	// z成分を無視する
	float ZNoT()								const;
	float WNoT()								const;

	// 引数ベクトルと乗算してベクトル要素を取得
	// 平行移動成分含む
	float VecXT( const Vec3 & )						const;
	float VecYT( const Vec3 & )						const;
	float VecZT( const Vec3 & )						const;
	float VecWT( const Vec3 & )						const;

	// 平行移動成分なし
	float VecXNoT( const Vec3 & )					const;
	float VecYNoT( const Vec3 & )					const;
	float VecZNoT( const Vec3 & )					const;
	float VecWNoT( const Vec3 & )					const;


	/*-----------------------------------------------------*/
	// 代入
	/*-----------------------------------------------------*/
	CMatrix44 &operator = ( const CVector3	&rV );
 	CMatrix44 &operator = ( const CQuaternion	&rQ );
	CMatrix44 &operator = ( const CMatrix44	&m  );


	/*-----------------------------------------------------*/
	// 各種演算子
	/*-----------------------------------------------------*/
	CMatrix44  operator + ( const CMatrix44 &rM )	const;
	CMatrix44  operator - ( const CMatrix44 &rM )	const;
	CMatrix44  operator * ( float f ) const;
	CMatrix44  operator / ( float f ) const;

	CMatrix44 &operator += ( const CMatrix44 &M  );
	CMatrix44 &operator -= ( const CMatrix44 &M  );
	CMatrix44 &operator *= ( float f );
	CMatrix44 &operator /= ( float fa );

	//行列同士の乗算
	CMatrix44  operator *  ( const CMatrix44 &M  )	const;
	CMatrix44 &operator *= ( const CMatrix44 &M  );

	friend CMatrix44 operator  *( float, const CMatrix44 & );

	// ベクトルとの演算
	// ｗ 値での除算は行わない
	CVector3  operator *(  const CVector3& )		const;


	/*-----------------------------------------------------*/
	// 論理演算
	/*-----------------------------------------------------*/
	bool operator == ( const CMatrix44 & )			const;
	bool operator != ( const CMatrix44 & )			const;


	/*-----------------------------------------------------*/
	// その他
	/*-----------------------------------------------------*/
	CMatrix44 operator - ()							const;			// 符号反転
	CMatrix44 &Identity();											// 単位行列にする
	bool IsIdentity()								const;			// 単位行列であるか判定
	float Det()										const;			// 行列式
	

	/*-----------------------------------------------------*/
	// 基本変換のサポート
	/*-----------------------------------------------------*/
	CMatrix44 &SwapRow( differ_type row1, differ_type row2 );		// 行入れ替え
	CMatrix44 &SwapCol( differ_type col1, differ_type col2 );		// 列入れ替え
	CMatrix44 &MulRow ( differ_type row, float f );					// 指定行に係数を掛ける
	CMatrix44 &MulCol ( differ_type col, float f );					// 指定列に係数を掛ける


	/*-----------------------------------------------------*/
	// 各種変換行列作成
	/*-----------------------------------------------------*/
	CMatrix44 &RotationX( float rad );									// 回転行列作成
	CMatrix44 &RotationY( float rad );
	CMatrix44 &RotationZ( float rad );

	CMatrix44 &RotationXPivot( const Vec3 &pos, float rad );			// 指定座標中心回転行列作成
	CMatrix44 &RotationYPivot( const Vec3 &pos, float rad );
	CMatrix44 &RotationZPivot( const Vec3 &pos, float rad );
	CMatrix44 &RotationXPivot( float x, float y, float z, float rad );
	CMatrix44 &RotationYPivot( float x, float y, float z, float rad );
	CMatrix44 &RotationZPivot( float x, float y, float z, float rad );
	
	CMatrix44 &Scaling( const Vec3 &scl );								// スケーリング行列の作成
	CMatrix44 &Scaling( float x, float y, float z );

	CMatrix44 &ScalingPivot( const Vec3 &pos, const Vec3 &scl );		// 指定位置中心スケーリング行列の作成

	CMatrix44 &Translate( const Vec3 &trs );							// 平行移動行列の作成
	CMatrix44 &Translate( float x, float y, float z );

	CMatrix44 &SetTranslate( const Vec3 &trs );							// （他の要素は変えずに）平行移動パラメータを適用する
	CMatrix44 &SetTranslate( float x, float y, float z );

	CMatrix44 &AddTranslate( const Vec3 &trs );							// （他の要素は変えずに）平行移動パラメータに加算する
	CMatrix44 &AddTranslate( float x, float y, float z );

	CMatrix44 &RotationAxis( const Vec3 &axis, float rad );				// 任意軸周りに回転
	CMatrix44 &RotationAxis( const CQuaternion & );
	CMatrix44 &RotationAxis( float x, float y, float z, float rad );

	CMatrix44 &RotationAxisPivot( const Vec3 &axis, float rad, const Vec3 &pos );	// 指定座標中心任意軸周りに回転
	CMatrix44 &RotationAxisPivot( const CQuaternion &, const Vec3 &pos );
	CMatrix44 &RotationAxisPivot( float x, float y, float z, float rad, const Vec3 &pos );

	CMatrix44 &RotationYPR( const Vec3 &YPR );							// ヨーピッチロール回転
	CMatrix44 &RotationYPR( float pitch, float yaw, float roll );

	CMatrix44 &RotationYPRPivot( const Vec3 &YPR, const Vec3 &pos );	// 指定位置中心ヨーピッチロール回転
	CMatrix44 &RotationYPRPivot( float pitch, float yaw, float roll, const Vec3 &pos );


	/*-----------------------------------------------------*/
	// トランスフォーム作成
	/*-----------------------------------------------------*/
	CMatrix44 &Compose( const Vec3 &Trs, const Vec3 &Rot, const Vec3 &Scl );
	CMatrix44 &Compose( const Vec3 &Trs, const CQuaternion &, const Vec3 &Scl );


	/*-----------------------------------------------------*/
	// トランスフォーム情報の取得
	/*-----------------------------------------------------*/
	Vec3 &GetTranslate( Vec3 & )					const;	// 平行移動成分のみを取得
	Vec3 &GetScale( Vec3 & )						const;	// スケール取得
	CQuaternion &GetRotation( CQuaternion & )		const;	// 回転成分取得
	void Decompose( Vec3 &Scl, CQuaternion &, Vec3 &trs )	const;	// トランスフォーム分解 


	/*-----------------------------------------------------*/
	// 値の代入の関係上フレンドにした関数
	/*-----------------------------------------------------*/
	friend CMatrix44 &MtxMulTranslate( CMatrix44 &, float, float, float );
	friend CMatrix44 &MtxMulTranslate( float, float, float, CMatrix44& );
	friend CMatrix44 &MtxMulScaling  ( CMatrix44 &, float, float, float );
	friend CMatrix44 &MtxMulScaling  ( float, float, float, CMatrix44& );

};

typedef CMatrix44	Mtx;



//--------------------------------------------------------------
// クラス外関数
//--------------------------------------------------------------

/*-----------------------------------------------------*/
// 四則演算関数
/*-----------------------------------------------------*/
Mtx  &MtxAdd( Mtx &O,  const Mtx &In1, const Mtx  &pIn2 );		// 加算
Mtx  &MtxSub( Mtx &O,  const Mtx &In1, const Mtx  &pIn2 );		// 減算
Mtx  &MtxMul( Mtx &O,  const Mtx &In1, const Mtx  &pIn2 );		// 乗算
Vec3 &MtxMul( Vec3 &O, const Mtx &Min, const Vec3 &pVin, eMtxToVec = kTNoW );
Mtx  &MtxMul( Mtx &O,  float f,  const Mtx  &In );
Mtx  &MtxMul( Mtx &O,  const Mtx &In,  float f  );
Mtx  &MtxDiv( Mtx &O,  float f,  const Mtx  &In );		// 除算


/*-----------------------------------------------------*/
// 各種変換処理
/*-----------------------------------------------------*/

//--------------------------------------------------
// 軸中心の回転行列と掛ける
//--------------------------------------------------
Mtx &MtxMulRotationX( Mtx &, float );
Mtx &MtxMulRotationY( Mtx &, float );
Mtx &MtxMulRotationZ( Mtx &, float );
Mtx &MtxMulRotationX( float, Mtx &);
Mtx &MtxMulRotationY( float, Mtx &);
Mtx &MtxMulRotationZ( float, Mtx &);


//--------------------------------------------------
// 指定座標中心の回転行列と掛ける
//--------------------------------------------------

// pM*回転行列をpMに格納
Mtx &MtxMulRotationX( Mtx &pM, float r, float y, float z );	// x軸中心
Mtx &MtxMulRotationY( Mtx &pM, float r, float x, float z );	// y軸中心
Mtx &MtxMulRotationZ( Mtx &pM, float r, float x, float y );	// z軸中心

// 回転行列*MをMに格納
Mtx &MtxMulRotationX( float r, float y, float z, Mtx &M );	// x軸中心
Mtx &MtxMulRotationY( float r, float x, float z, Mtx &M );	// y軸中心
Mtx &MtxMulRotationZ( float r, float x, float y, Mtx &M );	// z軸中心

// それぞれのオーバーロード形式
Mtx &MtxMulRotationX( Mtx &M, float  r, const Vec3 &V );
Mtx &MtxMulRotationY( Mtx &M, float  r, const Vec3 &V );
Mtx &MtxMulRotationZ( Mtx &M, float  r, const Vec3 &V );
Mtx &MtxMulRotationX( float  r, const Vec3 &V, Mtx &M );
Mtx &MtxMulRotationY( float  r, const Vec3 &V, Mtx &M );
Mtx &MtxMulRotationZ( float  r, const Vec3 &V, Mtx &M );


//--------------------------------------------------
// クォータニオンを使った回転を掛ける
//--------------------------------------------------
Mtx &MtxRotationQuat( Mtx &, const CQuaternion & );
Mtx &MtxRotationQuat( const CQuaternion &, Mtx & );


//--------------------------------------------------
// 指定座標中心でクォータニオンを使った回転を掛ける
//--------------------------------------------------
Mtx &MtxRotationQuatPivot( Mtx &, const CQuaternion &, const Vec3 & );
Mtx &MtxRotationQuatPivot( const CQuaternion &, const Vec3 &, Mtx & );


//--------------------------------------------------
// 行列を使ってx,y,z 軸回転を計算
//--------------------------------------------------

enum eMtxRotType { kXYZ, kXZY, kYXZ, kYZX, kZXY, kZYX };

Mtx &MtxRotationXYZ( Mtx &,   const Vec3 &, eMtxRotType = kXYZ );	// 行列*回転
Mtx &MtxRotationXYZ( const Vec3 &, Mtx &,   eMtxRotType = kXYZ );	// 回転*行列


//--------------------------------------------------
// 平行移動行列と掛ける
//--------------------------------------------------
Mtx &MtxMulTranslate( Mtx &,  float, float, float );			// 行列*平行移動行列
Mtx &MtxMulTranslate( Mtx &  M, const Vec3 &V );
Mtx &MtxMulTranslate( float, float, float , Mtx &);				// 平行移動行列*行列
Mtx &MtxMulTranslate( const Vec3 &V, Mtx &  M );


//--------------------------------------------------
// スケーリング行列と掛ける
//--------------------------------------------------
Mtx &MtxMulScaling( Mtx &, float, float, float );				// 行列*スケーリング行列
Mtx &MtxMulScaling( Mtx &, const Vec3 &V );
Mtx &MtxMulScaling( float, float, float, Mtx & );				// スケーリング行列*行列
Mtx &MtxMulScaling( const Vec3 &V, Mtx &M );


//--------------------------------------------------
// 指定座標中心のスケーリング行列と掛ける
//--------------------------------------------------
Mtx &MtxMulScalingPivot( Mtx &, const Vec3 &scl, const Vec3 &pos );	// 行列*スケーリング
Mtx &MtxMulScalingPivot( const Vec3 &scl, const Vec3 &pos, Mtx & );	// スケーリング*行列


//--------------------------------------------------
// 変換行列の作成
//--------------------------------------------------
Mtx &MtxCompose( const Vec3 &Trs, const Vec3 &Rot, const Vec3 &Scl, Mtx &);
Mtx &MtxCompose( const Vec3 &Trs, const CQuaternion &Rot, const Vec3 &Scl, Mtx &);


//--------------------------------------------------
// その他
//--------------------------------------------------

// 符号反転
Mtx &MtxSignReverse( Mtx &pMo, const Mtx &M );

// 転置行列作成
Mtx &MtxTranspose( Mtx &pMo, const Mtx &M );

// 逆行列作成
Mtx &MtxInverse( Mtx &pMo, const Mtx &M, float *pDet=NULL );

// ＬＵ分解を行う
bool MtxLUDecomp( Mtx &pMl, Mtx &pMu, const Mtx &pMsrc, BYTE *pivot=NULL );
bool MtxLUDecomp( Mtx &pMlu, const Mtx &pMsrc, BYTE *pivot=NULL );	// 同上  単一の行列に結果を格納

// LU行列の逆行列を求める
bool MtxLUInverse( Mtx &pMli, Mtx &PMui, const Mtx &pMl, const Mtx &pMu );
bool MtxLUInverse( Mtx &pMli, Mtx &PMui, const Mtx &pMlu );
bool MtxLUInverse( Mtx &pMlui, const Mtx &pMl, const Mtx &pMu );
bool MtxLUInverse( Mtx &pMlui, const Mtx &pMlu );

// ビュー行列作成
Mtx &MtxView( Mtx &pMo, const Vec3 &vEye, const Vec3 &vAt, const Vec3 &vUp );

// プロジェクション行列作成
Mtx &MtxProjection( Mtx &pMo, float fovY, float aspect, float near, float far );

// ピボット探し
BYTE MtxGetPivotRow( const Mtx &M, BYTE row, BYTE st=0 );
BYTE MtxGetPivotCol( const Mtx &M, BYTE col, BYTE st=0 );

// ピボッティング
bool MtxPivottingRow( Mtx &pMo, const Mtx &pMi, BYTE *pivot );
bool MtxPivottingCol( Mtx &pMo, const Mtx &pMi, BYTE *pivot );


#include "Vec3.inl"
#include "Mtx.inl"


#endif

