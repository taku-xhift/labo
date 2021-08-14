//-----------------------------------------------------------------------------------
//! @file	Mtx.inl
//! @brief	4x4の行列
//! @author	伊藤貴徳
//! @date	07/07/28：編集
//! @date	07/08/05：行列メソッドに各種変換行列作成を追加
//! @date	07/08/26：行列のアクセッサを強化
//! @date			  行列のＬＵ分解を追加
//! @date	07/09/01：逆行列計算をＬＵ分解を用いたものに変更
//! @date			  ベクトルの任意軸回転を追加
//! @date	07/09/08：行列に()演算子追加
//! @date	07/10/16：長大化に伴い分離
//! @date	08/02/11：全体を整理
//-----------------------------------------------------------------------------------


// 4*4行列

#ifndef ___MTX_INL___
#define ___MTX_INL___


//===============================================================================//
//	行列
//===============================================================================//

/********************************************************************/
//  4*4行列クラスメソッド
/********************************************************************/

//------------------------------------------------------------------//
//! @brief 各種コンストラクタ
//------------------------------------------------------------------//

inline Mtx::CMatrix44( bool identity )
{
	if( identity )
		Identity();
}

inline Mtx::CMatrix44(	float _11, float _12, float _13, float _14,
						float _21, float _22, float _23, float _24,
						float _31, float _32, float _33, float _34,
						float _41, float _42, float _43, float _44 )
{
	Set( _11, _12, _13, _14,
		 _21, _22, _23, _24,
		 _31, _32, _33, _34,
		 _41, _42, _43, _44 );
}

inline Mtx::CMatrix44( const float *m )
{
	Set( m );
}

inline Mtx::CMatrix44( float x, float y, float z )
{
	Set( x, y, z );
}

inline Mtx::CMatrix44( const Mtx &m )
{
	*this = m;
}

inline Mtx::CMatrix44( const Vec2 &V )
{
	Set( V );
}

inline Mtx::CMatrix44( const Vec3 &V )
{
	Set( V );
}

inline Mtx::CMatrix44( const Vec4 &V )
{
	Set( V );
}

inline Mtx::CMatrix44( const CQuaternion &Q )
{
	Set( Q );
}

// D3DX互換
#ifdef ___USE_D3DX___
inline Mtx::CMatrix44( const D3DXVECTOR2    &V )
{
	assert(V);

	Set( V );
}

inline Mtx::CMatrix44( const D3DXVECTOR3    &V )
{
assert(V);

Set( V );
}

inline Mtx::CMatrix44( const D3DXVECTOR4    &V )
{
assert(V);
	Set( V );
}

inline Mtx::CMatrix44( const D3DXQUATERNION &Q )
{
assert(!Q);

Set( Q );
}

inline Mtx::CMatrix44( const D3DXMATRIX     &M )
{
assert(!M);

Set( M );
}



//------------------------------------------------------------------//
//! @brief デストラクタ
//------------------------------------------------------------------//
inline Mtx::~CMatrix44()
{
}



//------------------------------------------------------------------//
//! @brief D3DX互換処理
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	関数変換
//--------------------------------------------------------------
inline D3DXVECTOR2 &Mtx::toD3DVEC2 ( D3DXVECTOR2	  &V )		const
{
	V.x = XT();
	V.y = YT();
	return V;
}

inline D3DXVECTOR3 &Mtx::toD3DVEC3 ( D3DXVECTOR3	  &V )		const
{
	V.x = XT();
	V.y = YT();
	V.z = ZT();
	return V;
}

inline D3DXVECTOR4 &Mtx::toD3DVEC4 ( D3DXVECTOR4	  &V )		const
{
	V.x = XT();
	V.y = YT();
	V.z = ZT();
	V.w = WT();
	return V;
}

inline D3DXMATRIX &Mtx::toD3DMTX( D3DXMATRIX &M )				const
{
	M._11 = m_m[e11]; M._12 = m_m[e21]; M._13 = m_m[e31]; M._14 = m_m[e41];
	M._21 = m_m[e12]; M._22 = m_m[e22]; M._23 = m_m[e32]; M._24 = m_m[e42];
	M._31 = m_m[e13]; M._32 = m_m[e23]; M._33 = m_m[e33]; M._34 = m_m[e43];
	M._41 = m_m[e14]; M._42 = m_m[e24]; M._43 = m_m[e34]; M._44 = m_m[e44];
	return M;
}


//--------------------------------------------------------------
//! @brief	演算子変換
//--------------------------------------------------------------
inline Mtx::operator D3DXVECTOR2	()						const
{
	return D3DXVECTOR2( XT(), YT() ); 
}

inline Mtx::operator D3DXVECTOR3	()						const
{
	return D3DXVECTOR3( XT(), YT(), ZT() );
}

inline Mtx::operator D3DXVECTOR4	()						const
{
	return D3DXVECTOR4( XT(), YT(), ZT(), WT() );
}

inline Mtx::operator D3DXMATRIX ()							 const
{
	return D3DXMATRIX( m_m[e11], m_m[e21], m_m[e31], m_m[e41],
					   m_m[e12], m_m[e22], m_m[e32], m_m[e42],
					   m_m[e13], m_m[e23], m_m[e33], m_m[e43],
					   m_m[e14], m_m[e24], m_m[e34], m_m[e44] );
}


//--------------------------------------------------------------
//! @brief	代入
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const D3DXVECTOR2	  &v )
{
	Identity();
	m_m[e11] = v.x;
	m_m[e22] = v.y;
	m_m[e33] = 0;
	return *this;
}

inline Mtx &Mtx::operator = ( const D3DXVECTOR3	  &v )
{
	Identity();
	m_m[e11] = v.x;
	m_m[e22] = v.y;
	m_m[e33] = v.z;
	return *this;
}

inline Mtx &Mtx::operator = ( const D3DXVECTOR4	  &v )
{
	Identity();
	m_m[e11] = v.x;
	m_m[e22] = v.y;
	m_m[e33] = v.z;
	m_m[e44] = v.w;
	return *this;
}

inline Mtx &Mtx::operator = ( const D3DXMATRIX &M )
{
	m_m[e11] = M._11; m_m[e21] = M._12; m_m[e31] = M._13; m_m[e41] = M._14;
	m_m[e12] = M._21; m_m[e22] = M._22; m_m[e32] = M._23; m_m[e42] = M._24;
	m_m[e13] = M._31; m_m[e23] = M._32; m_m[e33] = M._33; m_m[e43] = M._34;
	m_m[e14] = M._41; m_m[e24] = M._42; m_m[e34] = M._43; m_m[e44] = M._44;
	return *this;
}


//------------------------------------------------------------------//
//! @brief セット
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	要素を指定してセット
//! @param	num		要素インデックス
//! @param	val		値
//--------------------------------------------------------------
inline void Mtx::SetVal( differ_type num, float val )
{ 
	ClampSet( num, 15, 0 );

	m_m[num] = val;
}


//--------------------------------------------------------------
//! @brief	要素を指定してセット
//! @param	row		行番号(0-3)
//! @param	col		列番号(0-3)
//! @param	val		値
//--------------------------------------------------------------
inline void Mtx::SetVal( differ_type row, differ_type col, float val )
{
	ClampSet( col, 3, 0 );
	ClampSet( row, 3, 0 );

	m_m[row + col*4] = val;
}


//--------------------------------------------------------------
//! @brief	行セット
//! @param	rowNo		行番号(0-3)
//! @param	pV			ベクトルによる値
//! @param	trs			平行移動成分
//--------------------------------------------------------------
inline void Mtx::SetRow( differ_type rowNo, float x, float y, float z, float trs )
{
	m_m[rowNo] = x;	m_m[rowNo+4] = y; m_m[rowNo+8] = z; m_m[rowNo+12] = trs;
}


inline void Mtx::SetRow( differ_type rowNo, const Vec3 &V, float trs )
{
	SetRow( rowNo, V.x, V.y, V.z, trs );
}


//--------------------------------------------------------------
//! @brief	列セット
//! @param	colNo		列番号(0-3)
//! @param	pV			ベクトルによる値
//! @param	w			W成分
//--------------------------------------------------------------
inline void Mtx::SetCol( differ_type colNo, float x, float y, float z, float w )
{
	 differ_type col = colNo*4;
	 m_m[col] = x;	m_m[col+1] = y;	m_m[col+2] = z;	m_m[col+3] = w;
}


inline void Mtx::SetCol( differ_type colNo, const Vec3 &V, float w )
{
	SetCol( colNo, V.x, V.y, V.z, w );
}


//--------------------------------------------------------------
//! @brief	一括セット
//-------------------------------------------------------------
inline Mtx &Mtx::Set( float _11, float _12, float _13, float _14,
					  float _21, float _22, float _23, float _24,
					  float _31, float _32, float _33, float _34,
					  float _41, float _42, float _43, float _44 )
{
	m_m[e11] = _11; m_m[e12] = _12; m_m[e13] = _13; m_m[e14] = _14;
	m_m[e21] = _21; m_m[e22] = _22; m_m[e23] = _23; m_m[e24] = _24;
	m_m[e31] = _31; m_m[e32] = _32; m_m[e33] = _33; m_m[e34] = _34;
	m_m[e41] = _41; m_m[e42] = _42; m_m[e43] = _43; m_m[e44] = _44;
	return *this;
}

inline Mtx &Mtx::Set( const float *pM )
{
assert(pM);

memcpy( m_m, pM, sizeof( float ) << 4 );
	return *this;
}

inline Mtx &Mtx::Set( float x, float y, float z )
{
	Identity();
	m_m[e11] = x;
	m_m[e22] = y; 
	m_m[e33] = z;
	return *this;
}

inline Mtx &Mtx::Set( const Vec2 &V )
{
	Identity();
	m_m[e11] = V.x;
	m_m[e22] = V.y; 
	m_m[e33] = 0;
	return *this;
}

inline Mtx &Mtx::Set( const Vec3 &V )
{
	Identity();
	m_m[e11] = V.x;
	m_m[e22] = V.y; 
	m_m[e33] = V.z;
	return *this;
}

inline Mtx &Mtx::Set( const Vec4 &V )
{
	Identity();
	m_m[e11] = V.x;
	m_m[e22] = V.y; 
	m_m[e33] = V.z;
	m_m[e44] = V.w;
	return *this;
}


// 以下暫くはD3DX型互換処理
inline Mtx &Mtx::Set( const D3DXVECTOR2	&V )
{
	*this = V;
	return *this;	
}

inline Mtx &Mtx::Set( const D3DXVECTOR3	&V )
{
	*this = V;
	return *this;	
}

inline Mtx &Mtx::Set( const D3DXVECTOR4	&V )
{
	*this = V;
	return *this;	
}

inline Mtx &Mtx::Set( const D3DXQUATERNION &Q )
{
	*this = Q;
	return *this;	
}

inline Mtx &Mtx::Set( const D3DXMATRIX	 &M )
{
	*this = M;
	return *this;	
}



//------------------------------------------------------------------//
//! @brief ゲット
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	変更不能な参照を一括取得
//-------------------------------------------------------------
inline const float  *Mtx::GetMatrix()	   const
{
	return m_m;
}


//--------------------------------------------------------------
//! @brief	変更可能な参照を一括取得
//-------------------------------------------------------------
inline float  *Mtx::GetMatrix()
{
	return m_m;
}


//--------------------------------------------------------------
//! @brief	行列データをコピー
//-------------------------------------------------------------
inline float  *Mtx::GetMatrix( float *pMo )  const
{
assert(
	NULL_CHECK( pMo, pMo );
#endif
	return (float*)memcpy( pMo, m_m, sizeof( float ) << 4 );
}


//--------------------------------------------------------------
//!	@brief	ビルトイン変換
//-------------------------------------------------------------
inline Mtx::operator const float*()		const
{
	return m_m;
}

inline Mtx::operator float*()
{
	return m_m;
}


//--------------------------------------------------------------
//! @brief	要素を指定して値を取得
//--------------------------------------------------------------
inline float &Mtx::GetVal( differ_type i )
{
//	return operator[] ( i );
	return m_m[i];
}

inline float Mtx::GetVal( differ_type i )			const
{
//	return operator[] ( i );
	return m_m[i];
}


//--------------------------------------------------------------
//! @brief	要素を指定して値を取得
//! @param	row		行インデックス(0-3)
//! @param	col		列インデックス(0-3)
//--------------------------------------------------------------
inline float &Mtx::GetVal( differ_type row, differ_type col )
{
assert(
	ClampSet( row, 3, 0 );
	ClampSet( col, 3, 0 );
#endif

#ifdef ___USE_MTX_COL_MAJOR___
	return m_m[row + col*4];

#elif	defined(___USE_MTX_ROW_MAJOR___)
	return m_m[row*4 + col];
#endif
}

inline float Mtx::GetVal( differ_type row, differ_type col )		const
{
assert(
	ClampSet( row, 3, 0 );
	ClampSet( col, 3, 0 );
#endif

#ifdef ___USE_MTX_COL_MAJOR___
	return m_m[row + col*4];

#elif	defined(___USE_MTX_ROW_MAJOR___)
	return m_m[row*4 + col];
#endif
}



//--------------------------------------------------------------
//! @brief		添え字演算子
//--------------------------------------------------------------
//inline float &Mtx::operator [] ( differ_type i )
//{
//assert(
//	ClampSet( i, 16, 0 );
//#endif
//	return m_m[i];
//}
//
//inline float Mtx::operator [] ( differ_type i )		const
//{
//assert(
//	ClampSet( i, 16, 0 );
//#endif
//	return m_m[i];
//}


//--------------------------------------------------------------
//! @brief		()演算子
//--------------------------------------------------------------
inline float &Mtx::operator () ( differ_type row, differ_type col )
{
	return GetVal( row, col );
}

inline float Mtx::operator () ( differ_type row, differ_type col )		const
{
	return GetVal( row, col );
}


//--------------------------------------------------------------
//! @brief	行取得
//! @param	pV		行格納ベクトル
//! @param	rowNo	行番号(0-3)
//--------------------------------------------------------------


inline Vec3 &Mtx::GetRow( Vec3 &V, differ_type rowNo )					const
{
assert(
	ClampSet( rowNo, 3, 0 );
#endif

#ifdef ___USE_MTX_COL_MAJOR___
	return V.Set( m_m[rowNo], m_m[rowNo+4], m_m[rowNo+8] ); 
#elif	defined(___USE_MTX_ROW_MAJOR___)
	differ_type row = rowNo*4;
	return V.Set( m_m[row], m_m[row+1], m_m[row+2] );
#endif
}


inline float *Mtx::GetRow( float *pF, differ_type rowNo )				const
{
assert(
	if( !pF )		return pF;
	ClampSet( rowNo, 3, 0 );
#endif

	float *m = const_cast<float *> (m_m);

#ifdef ___USE_MTX_COL_MAJOR___
	pF[0] = m[rowNo];	 pF[1] = m[rowNo+4];	pF[2] = m[rowNo+8];  pF[3] = m[rowNo+12]; 
#elif	defined(___USE_MTX_ROW_MAJOR___)
	memcpy( pF, &m[rowNo*4], sizeof(float)*4 );
#endif

	return pF;
}


//--------------------------------------------------------------
//! @brief	列取得
//! @param	pV		列格納ベクトル
//! @param	colNo	列番号(0-3)
//--------------------------------------------------------------


inline Vec3 &Mtx::GetCol( Vec3 &V, differ_type colNo )					const
{
assert(
	ClampSet( colNo, 3, 0 );
#endif

#ifdef ___USE_MTX_COL_MAJOR___
	differ_type col = colNo*4;
	return V.Set( m_m[col], m_m[col+1], m_m[col+2] );
#elif	defined(___USE_MTX_ROW_MAJOR___)
	return V.Set( m_m[colNo], m_m[colNo+4], m_m[colNo+8] ); 
#endif
}

inline float *Mtx::GetCol( float *pF, differ_type colNo )				const
{
assert(
	if( !pF )		return pF;
	ClampSet( colNo, 3, 0 );
#endif

	float *m = const_cast<float*> (m_m);

#ifdef ___USE_MTX_COL_MAJOR___
	memcpy( pF, &m[colNo*4], sizeof(float)*4 );
#elif	defined(___USE_MTX_ROW_MAJOR___)
	pF[0] =m[colNo];	pF[1] = m[colNo+4];	pF[2] = m[colNo+8];	pF[3] = m[colNo+12]; 
#endif

	return pF;
}



//--------------------------------------------------------------
//! @brief	平行移動込みのベクトル要素として取得
//--------------------------------------------------------------
inline float Mtx::XT()						const
{
	return m_m[e11] + m_m[e12] + m_m[e13] + m_m[e14];
}

inline float Mtx::XT2D()					const
{
	return m_m[e11] + m_m[e12] + m_m[e14];
}

inline float Mtx::YT()						const
{
	return m_m[e21] + m_m[e22] + m_m[e23] + m_m[e24];
}

inline float Mtx::YT2D()					const
{
	return m_m[e21] + m_m[e22] + m_m[e24];
}

inline float Mtx::ZT()						const
{
	return m_m[e31] + m_m[e32] + m_m[e33] + m_m[e34];
}

inline float Mtx::WT()						const
{
	return m_m[e41] + m_m[e42] + m_m[e43] + m_m[e44];
}


//--------------------------------------------------------------
//! @brief	平行移動なしのベクトル要素として取得
//--------------------------------------------------------------
inline float Mtx::XNoT()					const
{
	return m_m[e11] + m_m[e12] + m_m[e13];
}

inline float Mtx::XNoT2D()					const
{
	return m_m[e11] + m_m[e12];
}

inline float Mtx::YNoT()					const
{
	return m_m[e21] + m_m[e22] + m_m[e23];
}

inline float Mtx::YNoT2D()					const
{
	return m_m[e21] + m_m[e22];
}

inline float Mtx::ZNoT()					const
{
	return m_m[e31] + m_m[e32] + m_m[e33];
}

inline float Mtx::WNoT()					const
{
	return m_m[e41] + m_m[e42] + m_m[e43];
}


//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Xを取得
//! @brief	平行移動要素込み
//--------------------------------------------------------------
inline float Mtx::VecXT( const Vec3 &V )			const
{
	return m_m[e11]*V.x + m_m[e12]*V.y + m_m[e13]*V.z + m_m[e14];
}


//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Yを取得
//! @brief	平行移動要素込み
//--------------------------------------------------------------
inline float Mtx::VecYT( const Vec3 &V )			const
{
	return m_m[e21]*V.x + m_m[e22]*V.y + m_m[e23]*V.z + m_m[e24];
}



//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Zを取得
//! @brief	平行移動要素込み
//--------------------------------------------------------------
inline float Mtx::VecZT( const Vec3 &V )			const
{
	return m_m[e31]*V.x + m_m[e32]*V.y + m_m[e33]*V.z + m_m[e34];
}


//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Wを取得
//! @brief	平行移動要素込み
//--------------------------------------------------------------
inline float Mtx::VecWT( const Vec3 &V )			const
{
	return m_m[e41]*V.x + m_m[e42]*V.y + m_m[e43]*V.z + m_m[e44];
}


//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Xを取得
//! @brief	平行移動要素なし
//--------------------------------------------------------------
inline float Mtx::VecXNoT( const Vec3 &V )			const
{
	return m_m[e11]*V.x + m_m[e12]*V.y + m_m[e13]*V.z;
}



//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Yを取得
//! @brief	平行移動要素なし
//--------------------------------------------------------------
inline float Mtx::VecYNoT( const Vec3 &V )			const
{
	return m_m[e21]*V.x + m_m[e22]*V.y + m_m[e23]*V.z;
}


//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Zを取得
//! @brief	平行移動要素なし
//--------------------------------------------------------------
inline float Mtx::VecZNoT( const Vec3 &V )			const
{
	return m_m[e31]*V.x + m_m[e32]*V.y + m_m[e33]*V.z;
}


//--------------------------------------------------------------
//! @brief	引数ベクトルと乗算してベクトル要素Wを取得
//! @brief	平行移動要素なし
//--------------------------------------------------------------
inline float Mtx::VecWNoT( const Vec3 &V )			const
{
	return m_m[e41]*V.x + m_m[e42]*V.y + m_m[e43]*V.z;
}


//------------------------------------------------------------------//
//! @brief 各種代入
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	ベクトル代入
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const Vec3 &rV )
{
	return Set( rV );
}


//--------------------------------------------------------------
//! @brief	クォータニオン代入
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const CQuaternion &rQ )
{
	return Set( rQ );
}


//--------------------------------------------------------------
//! @brief	行列代入
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const Mtx &m )
{
	memcpy( m_m, m.GetMatrix(), sizeof( float ) << 4 );
	return *this;
}



//------------------------------------------------------------------//
//! @brief 各種演算子
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	標準四則演算
//--------------------------------------------------------------

// 加算
inline Mtx  Mtx::operator +  ( const Mtx &M )		const
{
	return Mtx( m_m[e11]+M[e11], m_m[e12]+M[e12], m_m[e13]+M[e13], m_m[e14]+M[e14],
				m_m[e21]+M[e21], m_m[e22]+M[e22], m_m[e23]+M[e23], m_m[e24]+M[e24],
				m_m[e31]+M[e31], m_m[e32]+M[e32], m_m[e33]+M[e33], m_m[e34]+M[e34],
				m_m[e41]+M[e41], m_m[e42]+M[e42], m_m[e43]+M[e43], m_m[e44]+M[e44] );
}

// 減算
inline Mtx  Mtx::operator -  ( const Mtx &M )		const
{
	return Mtx( m_m[e11]-M[e11], m_m[e12]-M[e12], m_m[e13]-M[e13], m_m[e14]-M[e14],
				m_m[e21]-M[e21], m_m[e22]-M[e22], m_m[e23]-M[e23], m_m[e24]-M[e24],
				m_m[e31]-M[e31], m_m[e32]-M[e32], m_m[e33]-M[e33], m_m[e34]-M[e34],
				m_m[e41]-M[e41], m_m[e42]-M[e42], m_m[e43]-M[e43], m_m[e44]-M[e44] );
}

// スカラー乗算
inline Mtx  Mtx::operator * ( float f )				const
{
	return Mtx( m_m[e11]*f, m_m[e12]*f, m_m[e13]*f, m_m[e14]*f,
				m_m[e21]*f, m_m[e22]*f, m_m[e23]*f, m_m[e24]*f,
				m_m[e31]*f, m_m[e32]*f, m_m[e33]*f, m_m[e34]*f,
				m_m[e41]*f, m_m[e42]*f, m_m[e43]*f, m_m[e44]*f );
}

// スカラー除算
inline Mtx  Mtx::operator /  ( float f )			const
{
assert(
	if( IsZero( f ) ) 
		return Mtx( *this );
#endif
	float fa  = 1.0f / f;
	return Mtx( m_m[e11]*f, m_m[e12]*f, m_m[e13]*f, m_m[e14]*f,
				m_m[e21]*f, m_m[e22]*f, m_m[e23]*f, m_m[e24]*f,
				m_m[e31]*f, m_m[e32]*f, m_m[e33]*f, m_m[e34]*f,
				m_m[e41]*f, m_m[e42]*f, m_m[e43]*f, m_m[e44]*f );
}


//--------------------------------------------------------------
//! @brief	代入四則演算
//--------------------------------------------------------------

// 加算代入
inline Mtx &Mtx::operator += ( const Mtx &M )
{
	m_m[e11]+=M[e11]; m_m[e12]+=M[e12]; m_m[e13]+=M[e13]; m_m[e14]+=M[e14];
	m_m[e21]+=M[e21]; m_m[e22]+=M[e22]; m_m[e23]+=M[e23]; m_m[e24]+=M[e24];
	m_m[e31]+=M[e31]; m_m[e32]+=M[e32]; m_m[e33]+=M[e33]; m_m[e34]+=M[e34];
	m_m[e41]+=M[e41]; m_m[e42]+=M[e42]; m_m[e43]+=M[e43]; m_m[e44]+=M[e44];
	return *this;
}

// 減算代入
inline Mtx &Mtx::operator -= ( const Mtx &M )
{
	m_m[e11]+=M[e11]; m_m[e12]+=M[e12]; m_m[e13]+=M[e13]; m_m[e14]+=M[e14];
	m_m[e21]+=M[e21]; m_m[e22]+=M[e22]; m_m[e23]+=M[e23]; m_m[e24]+=M[e24];
	m_m[e31]+=M[e31]; m_m[e32]+=M[e32]; m_m[e33]+=M[e33]; m_m[e34]+=M[e34];
	m_m[e41]+=M[e41]; m_m[e42]+=M[e42]; m_m[e43]+=M[e43]; m_m[e44]+=M[e44];
	return *this;
}

// スカラー乗算代入
inline Mtx &Mtx::operator *= ( float f )
{
	m_m[e11]*=f; m_m[e12]*=f; m_m[e13]*=f; m_m[e14]*=f;
	m_m[e21]*=f; m_m[e22]*=f; m_m[e23]*=f; m_m[e24]*=f;
	m_m[e31]*=f; m_m[e32]*=f; m_m[e33]*=f; m_m[e34]*=f;
	m_m[e41]*=f; m_m[e42]*=f; m_m[e43]*=f; m_m[e44]*=f;
	return *this;
}

// スカラー除算代入
inline Mtx &Mtx::operator /= ( float fa )
{
assert(
	if( IsZero( fa ) )
		return *this;
#endif
	float	f = 1.0f / fa;
	m_m[e11]*=f; m_m[e12]*=f; m_m[e13]*=f; m_m[e14]*=f;
	m_m[e21]*=f; m_m[e22]*=f; m_m[e23]*=f; m_m[e24]*=f;
	m_m[e31]*=f; m_m[e32]*=f; m_m[e33]*=f; m_m[e34]*=f;
	m_m[e41]*=f; m_m[e42]*=f; m_m[e43]*=f; m_m[e44]*=f;
	return *this;
}


//--------------------------------------------------------------
//! @brief	ベクトルとの演算
//! @brief	w 成分での除算は行わない 
//--------------------------------------------------------------
inline Vec3  Mtx::operator *( const Vec3 &v )			const
{
	return Vec3( VecXT( v ), VecYT( v ), VecZT( v ) );
}



//--------------------------------------------------------------
//! @brief	フレンド演算子
//--------------------------------------------------------------
inline Mtx  operator  *( float f, const Mtx &m )
{
	return Mtx( m.m_m[e11]*f, m.m_m[e12]*f, m.m_m[e13]*f, m.m_m[e14]*f,
				m.m_m[e21]*f, m.m_m[e22]*f, m.m_m[e23]*f, m.m_m[e24]*f,
				m.m_m[e31]*f, m.m_m[e32]*f, m.m_m[e33]*f, m.m_m[e34]*f,
				m.m_m[e41]*f, m.m_m[e42]*f, m.m_m[e43]*f, m.m_m[e44]*f );
}


//------------------------------------------------------------------//
//! @brief	論理演算
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	比較
//--------------------------------------------------------------

//	== 演算子
inline bool Mtx::operator == ( const Mtx &m  )			const
{
	return !memcmp( m_m, m.m_m, sizeof(float)*16 );
}

//	 != 演算子
inline bool Mtx::operator != ( const Mtx &m  )			const
{
	return !(!memcmp( m_m, m.m_m, sizeof(float)*16 ));
}



//------------------------------------------------------------------//
//! @brief	その他
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	符号反転
//--------------------------------------------------------------
inline Mtx Mtx::operator - ()						const
{
	return Mtx( -m_m[e11], -m_m[e12], -m_m[e13], -m_m[e14],
				-m_m[e21], -m_m[e22], -m_m[e23], -m_m[e24],
				-m_m[e31], -m_m[e32], -m_m[e33], -m_m[e34],
				-m_m[e41], -m_m[e42], -m_m[e43], -m_m[e44] );
}


//--------------------------------------------------------------
//! @brief	単位行列作成
//--------------------------------------------------------------
inline CMatrix44& Mtx::Identity()
{
	m_m[e11] = m_m[e22] = m_m[e33] = m_m[e44] = 1;
	m_m[e12] = m_m[e13] = m_m[e14] = m_m[e21] = m_m[e23] = m_m[e24] = 
	m_m[e31] = m_m[e32] = m_m[e34] = m_m[e41] = m_m[e42] = m_m[e43] = 0;
	return *this;	
}


//--------------------------------------------------------------
//! @brief	単位行列かどうか調べる
//! @brief	ある程度の誤差を許容するため、memcmpは使わない
//--------------------------------------------------------------
inline bool Mtx::IsIdentity()				const
{
	// 分かり辛いが、キャッシュを活かすため順番にアクセスする
	// マクロ定義による速度の違いを防ぐため、列挙ではなく数字の直打ちで行う
	return ( IsZero( m_m[0]-1.0f ) && IsZero( m_m[1] )      && IsZero( m_m[2] )       && IsZero( m_m[3] )  &&
			 IsZero( m_m[4] )      && IsZero( m_m[5]-1.0f ) && IsZero( m_m[6] )       && IsZero( m_m[7] )  &&
			 IsZero( m_m[8] )      && IsZero( m_m[9] )      && IsZero( m_m[10]-1.0f ) && IsZero( m_m[11] ) &&
			 IsZero( m_m[12] )     && IsZero( m_m[13] )     && IsZero( m_m[14] )      && IsZero( m_m[15]-1.0f ));
}


//------------------------------------------------------------------//
// 行列基本変形処理
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	行入れ替え
//--------------------------------------------------------------
inline Mtx &Mtx::SwapRow( differ_type row1, differ_type row2 )
{
assert(
	if( (row1 < 0) || (row1 > 3) || (row2 < 0) || (row2 > 3) )
		return *this;
#endif

	Vec4	v1, v2;
	
	GetRow( v1, row1 );
	GetRow( v2, row2 );
	SetRow( row2, v1 );
	SetRow( row1, v2 );

	return *this;
}


//--------------------------------------------------------------
//! @brief	列入れ替え
//--------------------------------------------------------------
inline Mtx &Mtx::SwapCol( differ_type col1, differ_type col2 )
{
assert(
	if( (col1 < 0) || (col1 > 3) || (col2 < 0) || (col2 > 3) )
		return *this;
#endif

	Vec4	v1, v2;
	
	GetCol( v1, col1 );
	GetCol( v2, col2 );
	SetCol( col2, v1 );
	SetCol( col1, v2 );

	return *this;
}


//--------------------------------------------------------------
//! @brief	行に係数を掛ける
//--------------------------------------------------------------
inline Mtx &Mtx::MulRow( differ_type rowNo, float f )
{
assert(
	if( (rowNo < 0) || (rowNo > 3) )
		return *this;
#endif
	

#ifdef ___USE_MTX_COL_MAJOR___
	m_m[rowNo] *= f; m_m[rowNo+4] *= f; m_m[rowNo+8] *= f; m_m[rowNo+12] *= f; 

#elif	defined(___USE_MTX_ROW_MAJOR___)
	differ_type row = rowNo *4;
	m_m[row] *= f; m_m[row+1] *= f; m_m[row+2] *= f; m_m[row+3] *= f;
	
#endif
	return *this;
}


//--------------------------------------------------------------
//! @brief	列に係数を掛ける
//--------------------------------------------------------------
inline Mtx &Mtx::MulCol( differ_type colNo, float f )
{
assert(
	if( (colNo < 0) || (colNo > 3) )
		return *this;
#endif
	

#ifdef ___USE_MTX_COL_MAJOR___
	 differ_type col = colNo*4;
	 m_m[col] *= f;	m_m[col+1] *= f;	m_m[col+2] *= f;	m_m[col+3] *= f;

#elif	defined(___USE_MTX_ROW_MAJOR___)
	m_m[colNo] *= f;	m_m[colNo+4] *= f; m_m[colNo+8] *= f; m_m[colNo+12] *= f;

#endif
	return *this;
}



//------------------------------------------------------------------//
// 各種変換行列作成
//------------------------------------------------------------------//

//------------------------------------------------------------------//
//! @brief	X軸回転行列作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationX( float rad )
{
	Identity();
	m_m[e22] = m_m[e33] = cosf( RAD(rad) );
	m_m[e32] = sinf( RAD(rad) );
	m_m[e23] = -m_m[e32];
	return *this;
}

//------------------------------------------------------------------//
//! @brief	Y軸回転行列作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationY( float rad )
{
	Identity();
	m_m[e11] = m_m[e33] = cosf( RAD(rad) );
	m_m[e13] = sinf( RAD(rad) );
	m_m[e31] = -m_m[e13];
	return *this;
}

//------------------------------------------------------------------//
//! @brief	Z軸回転行列作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationZ( float rad )
{
	Identity();
	m_m[e11] = m_m[e22] = cosf( RAD(rad) );
	m_m[e21] = sinf( RAD(rad) );
	m_m[e12] = -m_m[e21];
	return *this;
}


//------------------------------------------------------------------//
//! @brief	指定座標中心X軸回転行列作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationXPivot( const Vec3 &pos, float rad )
{
	return RotationXPivot( pos.x, pos.y, pos.z, rad );
}


//------------------------------------------------------------------//
//! @brief	指定座標中心Y軸回転行列作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationYPivot( const Vec3 &pos, float rad )
{
	return RotationYPivot( pos.x, pos.y, pos.z, rad );
}

//------------------------------------------------------------------//
//! @brief	指定座標中心Z軸回転行列作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationZPivot( const Vec3 &pos, float rad )
{
	return RotationZPivot( pos.x, pos.y, pos.z, rad );
}



//------------------------------------------------------------------//
//! @brief	スケーリング行列の作成
//------------------------------------------------------------------//
inline Mtx &Mtx::Scaling( const Vec3 &Scl )
{
	return Scaling( Scl.x, Scl.y, Scl.z );
}


//------------------------------------------------------------------//
//! @brief	スケーリング行列の作成
//------------------------------------------------------------------//
inline Mtx &Mtx::Scaling( float x, float y, float z )
{
	Identity();
	m_m[e11] = x;
	m_m[e22] = y;
	m_m[e33] = z;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	指定位置中心スケーリング行列の作成
//------------------------------------------------------------------//
inline Mtx &Mtx::ScalingPivot( const Vec3 &pos, const Vec3 &Scl )
{
	Scaling( Scl.x, Scl.y, Scl.z );
	m_m[e14] = pos.x * (1 - Scl.x);
	m_m[e24] = pos.y * (1 - Scl.y);
	m_m[e34] = pos.z * (1 - Scl.z);
	return *this;
}



//------------------------------------------------------------------//
//! @brief	平行移動行列の作成
//------------------------------------------------------------------//
inline Mtx &Mtx::Translate( const Vec3 &Trs )
{
	return Translate( Trs.x, Trs.y, Trs.z );
}


//------------------------------------------------------------------//
//! @brief	平行移動行列の作成
//------------------------------------------------------------------//
inline Mtx &Mtx::Translate( float x, float y, float z )
{
	Identity();
	m_m[e14] = x;
	m_m[e24] = y;
	m_m[e34] = z;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	平行移動パラメータのセット
//! @brief	他の要素は変更しない
//------------------------------------------------------------------//
inline Mtx &Mtx::SetTranslate( const Vec3 &Trs )
{
	return SetTranslate( Trs.x, Trs.y, Trs.z );
}


//------------------------------------------------------------------//
//! @brief	平行移動パラメータのセット
//! @brief	他の要素は変更しない
//------------------------------------------------------------------//
inline Mtx &Mtx::SetTranslate( float x, float y, float z )
{
	m_m[e14] = x;
	m_m[e24] = y;
	m_m[e34] = z;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	平行移動パラメータに加算
//! @brief	他の要素は変更しない
//------------------------------------------------------------------//
inline Mtx &Mtx::AddTranslate( const Vec3 &Trs )
{
	return AddTranslate( Trs.x, Trs.y, Trs.z );
}


//------------------------------------------------------------------//
//! @brief	平行移動パラメータに加算
//! @brief	他の要素は変更しない
//------------------------------------------------------------------//
inline Mtx &Mtx::AddTranslate( float x, float y, float z )
{
	m_m[e14] += x;
	m_m[e24] += y;
	m_m[e34] += z;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	任意軸中心で回転する行列を作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationAxis( float x, float y, float z, float rad )
{
	return RotationAxis( Vec3( x, y, z ), rad );
}

inline Mtx &Mtx::RotationAxis( const CQuaternion &q )
{
	return Set( q );
}


// 回転行列を指定位置中心になるようにする
#define ROTATION_TRANSLATE( pos )	m_m[e14] = -m_m[e11]*pos.x -m_m[e12]*pos.y -m_m[e13]*pos.z +pos.x;	\
									m_m[e24] = -m_m[e21]*pos.x -m_m[e22]*pos.y -m_m[e23]*pos.z +pos.y;	\
									m_m[e34] = -m_m[e31]*pos.x -m_m[e32]*pos.y -m_m[e33]*pos.z +pos.z;
//------------------------------------------------------------------//
//! @brief	指定位置任意軸中心で回転する行列を作成
//! @brief	軸ベクトルは単位化しておくこと
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationAxisPivot( const Vec3 &Axis, float rad, const Vec3 &pos )
{
	RotationAxis( Axis.x, Axis.y, Axis.z, rad );
	ROTATION_TRANSLATE( pos );
	return *this;
}

inline Mtx &Mtx::RotationAxisPivot( const CQuaternion &q, const Vec3 &pos )
{
	Set( q );
	ROTATION_TRANSLATE( pos );
	return *this;
}

inline Mtx &Mtx::RotationAxisPivot( float x, float y, float z, float rad, const Vec3 &pos )
{
	RotationAxis( x, y, z, rad );
	ROTATION_TRANSLATE( pos );
	return *this;
}


//------------------------------------------------------------------//
//! @brief	ヨーピッチロール指定で回転する行列を作成
//! @brief	x=pitch, y =yaw, z=roll で指定すること
//! @brief	尚、実際の計算順序は最もよく使われる Roll Pitch Yaw 
//! @brief	の順で行われる(D3DXMatrixRotationYawPitchRoll関数と同じ)
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationYPR( const Vec3 &YPR )
{
	return RotationYPR( YPR.x, YPR.y, YPR.z );
}


//------------------------------------------------------------------//
//! @brief	指定位置でヨーピッチロール回転する行列を作成
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationYPRPivot( const Vec3 &YPR, const Vec3 &pos )
{
	RotationYPR( YPR.x, YPR.y, YPR.z );
	ROTATION_TRANSLATE( pos );
	return *this;
}

inline Mtx &Mtx::RotationYPRPivot( float pitch, float yaw, float roll, const Vec3 &pos )
{
	RotationYPR( pitch, yaw, roll );
	ROTATION_TRANSLATE( pos );
	return *this;
}


//------------------------------------------------------------------//
//! @brief	変換行列の作成
//! @param	pTrs	平行移動
//! @param	pRot	回転
//! @param	pScl	スケーリング
//! @rtnval		変換後行列	
//------------------------------------------------------------------//
inline Mtx &Mtx::Compose( const Vec3 &Trs, const Vec3 &Rot, const Vec3 &Scl )
{
	MtxMulScaling  ( Scl, *this );
	MtxRotationXYZ ( Rot, *this );
	MtxMulTranslate( Trs, *this );
	return *this;
}


inline Mtx &Mtx::Compose( const Vec3 &Trs, const CQuaternion &Rot, const Vec3 &Scl )
{
	MtxMulScaling  ( Scl, *this );
	MtxRotationQuat( Rot, *this );
	MtxMulTranslate( Trs, *this );
	return *this;
}
#undef ROTATION_TRANSLATE


//--------------------------------------------------------------
//! @brief	平行移動成分のみを取得
//--------------------------------------------------------------
inline Vec3 &Mtx::GetTranslate( Vec3 &V )					const
{
	return V.Set( m_m[e14], m_m[e24], m_m[e34] );
}

//--------------------------------------------------------------
//! @brief	スケール成分のみを取得
//--------------------------------------------------------------
inline Vec3 &Mtx::GetScale( Vec3 &V )						const
{
	CVector3 x( m_m[e11], m_m[e21], m_m[e31] );
	CVector3 y( m_m[e12], m_m[e22], m_m[e32] );
	CVector3 z( m_m[e13], m_m[e23], m_m[e33] );

	return V.Set( x.Norm(), y.Norm(), z.Norm() );
}



/********************************************************************/
//  4*4行列クラス用関数
/********************************************************************/

//------------------------------------------------------------------//
//! @brief	四則演算関数
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	加算
//! @brief	pO = pI1 + pI2;	
//--------------------------------------------------------------
inline Mtx  &MtxAdd( Mtx  &Out, const Mtx  &In1, const Mtx  &In2 )
{
	return Out.Set( In1[e11]+In2[e11], In1[e12]+In2[e12],
					In1[e13]+In2[e13], In1[e14]+In2[e14], 
					In1[e21]+In2[e21], In1[e22]+In2[e22], 
					In1[e23]+In2[e23], In1[e24]+In2[e24], 
					In1[e31]+In2[e31], In1[e32]+In2[e32], 
					In1[e33]+In2[e33], In1[e34]+In2[e34], 
					In1[e41]+In2[e41], In1[e42]+In2[e42], 
					In1[e43]+In2[e43], In1[e44]+In2[e44] );
}


//--------------------------------------------------------------
//! @brief	減算
//! @brief	pO = In1 - In2;	
//--------------------------------------------------------------
inline Mtx  &MtxSub( Mtx  &Out, const Mtx  &In1, const Mtx  &In2 )
{
	return Out.Set( In1[e11]-In2[e11], In1[e12]-In2[e12],
					In1[e13]-In2[e13], In1[e14]-In2[e14], 
					In1[e21]-In2[e21], In1[e22]-In2[e22], 
					In1[e23]-In2[e23], In1[e24]-In2[e24], 
					In1[e31]-In2[e31], In1[e32]-In2[e32], 
					In1[e33]-In2[e33], In1[e34]-In2[e34], 
					In1[e41]-In2[e41], In1[e42]-In2[e42], 
					In1[e43]-In2[e43], In1[e44]-In2[e44] );
}


//--------------------------------------------------------------
//! @brief	乗算
//! @brief	pVo = pMi1 *pVi;
//! @brief	flag	計算方式(デフォルトは平行移動あり w 除算なし)
//--------------------------------------------------------------

// 補助関数
inline Vec3 &MtxMulTNoW( Vec3 &Vo, const Mtx &Mi, const Vec3 &Vi )
{
	return Vo.Set( Mi.VecXT( Vi ), Mi.VecYT( Vi ), Mi.VecZT( Vi ) );
}

inline Vec3 &MtxMulNoTNoW( Vec3 &Vo, const Mtx &Mi, const Vec3 &Vi )
{
	return Vo.Set( Mi.VecXNoT( Vi ), Mi.VecYNoT( Vi ), Mi.VecZNoT( Vi ) );
}

inline Vec3 &MtxMulTW( Vec3 &Vo, const Mtx &Mi, const Vec3 &Vi )
{
assert(
		float w = Mi.VecWT( Vi );
		w = IsZero( w ) ? 1.0f : 1.0f / w;
#else
		float w = 1.0f / Mi.VecWT( Vi );
#endif

	return Vo.Set( Mi.VecXT( Vi )*w, Mi.VecYT( Vi )*w, Mi.VecZT( Vi )*w );
}

inline Vec3 &MtxMulNoTW( Vec3 &Vo, const Mtx &Mi, const Vec3 &Vi )
{
assert(
		float w = Mi.VecWT( Vi );
		w = IsZero( w ) ? 1.0f : 1.0f / w;
#else
		float w = 1.0f / Mi.VecWT( Vi );
#endif

	return Vo.Set( Mi.VecXNoT( Vi )*w, Mi.VecYNoT( Vi )*w, Mi.VecZNoT( Vi )*w );
}


typedef Vec3 &(*MtxXVec)( Vec3 &, const Mtx &, const Vec3 &);

const MtxXVec mtxXvec[4] = { MtxMulTNoW, MtxMulNoTNoW, MtxMulTW, MtxMulNoTW };

// 本体
inline Vec3 &MtxMul( Vec3 &Vo, const Mtx &Mi, const Vec3 &Vi, eMtxToVec flag )
{
assert(
	if( (flag < 0) || (flag > 4) )
		return Vo;
#endif

	return (*(mtxXvec[flag]))( Vo, Mi, Vi );
}



//--------------------------------------------------------------
//! @brief	乗算
//! @brief	pO = f *pMI;
//--------------------------------------------------------------
inline Mtx &MtxMul( Mtx &Out, float f, const Mtx &In )
{
	return Out.Set( In[e11]*f, In[e12]*f, In[e13]*f, In[e14]*f, 
					In[e21]*f, In[e22]*f, In[e23]*f, In[e24]*f, 
					In[e31]*f, In[e32]*f, In[e33]*f, In[e34]*f, 
					In[e41]*f, In[e42]*f, In[e43]*f, In[e44]*f );
}


//--------------------------------------------------------------
//! @brief	乗算
//! @brief	pO = pMI *f;
//--------------------------------------------------------------
inline Mtx &MtxMul( Mtx &Out, const Mtx &In,  float f  )
{
	return MtxMul( Out, f, In );
}


//--------------------------------------------------------------
//! @brief	除算
//! @brief	pO = pMI / f;
//--------------------------------------------------------------
inline Mtx MtxDiv( Mtx Out, const Mtx In, float f)
{
assert(
	if( IsZero( f ) )
		return Out;
#endif
	float fa = 1.0f / f;
	return Out.Set( In[e11]*fa, In[e12]*fa, In[e13]*fa, In[e14]*fa, 
					In[e21]*fa, In[e22]*fa, In[e23]*fa, In[e24]*fa, 
					In[e31]*fa, In[e32]*fa, In[e33]*fa, In[e34]*fa, 
					In[e41]*fa, In[e42]*fa, In[e43]*fa, In[e44]*fa );
}



//------------------------------------------------------------------//
//! @brief	指定座標位置での各軸中心回転行列を計算
//------------------------------------------------------------------//

// 引数行列*回転行列
inline Mtx &MtxMulRotationX( Mtx &Mo, float  r, const Vec3 &v )
{
	return MtxMulRotationX( Mo, r, v.y, v.z );
}


inline Mtx &MtxMulRotationY( Mtx &Mo, float  r, const Vec3 &v )
{
	return MtxMulRotationY( Mo, r, v.x, v.z );
}


inline Mtx &MtxMulRotationZ( Mtx &Mo, float  r, const Vec3 &v )
{
	return MtxMulRotationZ( Mo, r, v.x, v.y );
}


// 回転行列*引数行列
inline Mtx &MtxMulRotationX( float  r, const Vec3 &v, Mtx &Mo )
{
	return MtxMulRotationX( r, v.y, v.z, Mo );
}


inline Mtx &MtxMulRotationY( float  r, const Vec3 &v, Mtx &Mo )
{
	return MtxMulRotationY( r, v.x, v.z, Mo );
}


inline Mtx &MtxMulRotationZ( float  r, const Vec3 &v, Mtx &Mo )
{
	return MtxMulRotationZ( r, v.x, v.y, Mo );
}



//------------------------------------------------------------------//
//! @brief	行列とクォータニオンを用いた回転との演算を行う
//------------------------------------------------------------------//

// 行列 *= クォータニオン
inline Mtx &MtxRotationQuat( Mtx &mtx, const CQuaternion &Quat )
{
	Mtx m( Quat );
	mtx *= m;
	return mtx;
}


// 行列=クォータニオン*行列
inline Mtx &MtxRotationQuat( const CQuaternion &Quat, Mtx &mtx )
{
	Mtx m( Quat );
	m *= mtx;
	mtx = m;
	return mtx;
}


//------------------------------------------------------------------//
//! @brief	行列と指定座標中心のクォータニオンを用いた回転との演算を行う
//------------------------------------------------------------------//

// 行列 *= クォータニオン
inline Mtx &MtxRotationQuatPivot( Mtx &mtx, const CQuaternion &Quat, const Vec3 &pos )
{
	Mtx m( false );
	m.RotationAxisPivot( Quat, pos );
	mtx *= m;
	return mtx;
}


// 行列=クォータニオン*行列
inline Mtx &MtxRotationQuatPivot( const CQuaternion &Quat, const Vec3 &pos, Mtx &mtx )
{
	Mtx m( false );
	m.RotationAxisPivot( Quat, pos );
	m *= mtx;
	mtx = m;
	return mtx;
}



//------------------------------------------------------------------//
//! @brief	平行移動行列との演算を行う
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	引数行列*平行移動行列
//! @brief	pMo *= 移動量(x, y, z)の行列 
//--------------------------------------------------------------
inline Mtx &MtxMulTranslate(  Mtx &Mo,  float x, float y, float z )
{
	Mo.m_m[e14] += Mo.m_m[e11]*x + Mo.m_m[e12]*y + Mo.m_m[e13]*z;
	Mo.m_m[e24] += Mo.m_m[e21]*x + Mo.m_m[e22]*y + Mo.m_m[e23]*z;
	Mo.m_m[e34] += Mo.m_m[e31]*x + Mo.m_m[e32]*y + Mo.m_m[e33]*z;
	Mo.m_m[e44] += Mo.m_m[e41]*x + Mo.m_m[e42]*y + Mo.m_m[e43]*z;
	return Mo;
}

inline Mtx &MtxMulTranslate(  Mtx &Mo,   const Vec3 &v )
{
	return MtxMulTranslate( Mo, v.x, v.y, v.z );
}



//--------------------------------------------------------------
//! @brief	平行移動行列*引数行列
//! @brief	Mo = 移動量(x, y, z)の行列 *Mo
//--------------------------------------------------------------
inline Mtx &MtxMulTranslate( const Vec3 &v, Mtx &Mo )
{
	return MtxMulTranslate( v.x, v.y, v.z, Mo );
}



//------------------------------------------------------------------//
//! @brief	スケーリング行列との演算を行う
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	引数行列*スケーリング行列
//! @brief	Mo *= 拡大率(x, y, z)の行列
//--------------------------------------------------------------
inline Mtx &MtxMulScaling( Mtx &Mo,  float x, float y, float z )
{
	Mo.m_m[e11] *= x;		Mo.m_m[e12] *= y;
	Mo.m_m[e13] *= z;		Mo.m_m[e21] *= x;
	Mo.m_m[e22] *= y;		Mo.m_m[e23] *= z;
	Mo.m_m[e31] *= x;		Mo.m_m[e32] *= y;
	Mo.m_m[e33] *= z;

	return Mo;
}

inline Mtx &MtxMulScaling( Mtx &Mo, const Vec3 &v )
{
	return MtxMulScaling( Mo, v.x, v.y, v.z );
}


//--------------------------------------------------------------
//! @brief	スケーリング行列*引数行列
//! @brief	Mo = 拡大率(x, y, z)の行列 *Mo
//--------------------------------------------------------------
inline Mtx &MtxMulScaling( float x, float y, float z, Mtx &Mo )
{
	Mo.m_m[e11] *= x;		Mo.m_m[e12] *= x;
	Mo.m_m[e13] *= x;		Mo.m_m[e14] *= x;
	Mo.m_m[e21] *= y;		Mo.m_m[e22] *= y;
	Mo.m_m[e23] *= y;		Mo.m_m[e24] *= y;
	Mo.m_m[e31] *= z;		Mo.m_m[e32] *= z;
	Mo.m_m[e33] *= z;		Mo.m_m[e34] *= z;

	return Mo;
}


inline Mtx &MtxMulScaling( const Vec3 &v, Mtx &Mo )
{
	return MtxMulScaling( v.x, v.y, v.z, Mo ); 
}



//------------------------------------------------------------------//
//! @brief	指定座標中心スケーリング行列との演算を行う
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	引数行列*スケーリング行列
//! @brief	Mo *= pos中心で拡大率sclの行列
//--------------------------------------------------------------
inline Mtx &MtxMulScalingPivot( Mtx &Mo, const Vec3 &scl, const Vec3 &pos )
{
	float x = pos.x * (1 - scl.x);
	float y = pos.y * (1 - scl.y);
	float z = pos.z * (1 - scl.z);

	Mo[e11] *= scl.x;	Mo[e12] *= scl.y;	Mo[e13] *= scl.z;
	Mo[e21] *= scl.x;	Mo[e22] *= scl.y;	Mo[e23] *= scl.z;
	Mo[e31] *= scl.x;	Mo[e32] *= scl.y;	Mo[e33] *= scl.z;
	Mo[e14] += Mo[e11]*x + Mo[e12]*y + Mo[e13]*z;
	Mo[e24] += Mo[e21]*x + Mo[e22]*y + Mo[e23]*z;
	Mo[e34] += Mo[e31]*x + Mo[e32]*y + Mo[e33]*z;

	return Mo;
}



//------------------------------------------------------------------//
//! @brief	変換行列の作成
//! @param	pTrs	平行移動
//! @param	pRot	回転
//! @param	pScl	スケーリング
//! @rtnval		変換後行列	
//------------------------------------------------------------------//
inline Mtx &MtxCompose( const Vec3 &Trs, const Vec3 &Rot, const Vec3 &Scl, Mtx &Mtx )
{
	return Mtx.Compose( Trs, Rot, Scl );
}

inline Mtx &MtxCompose( const Vec3 &Trs, const CQuaternion &Rot, const Vec3 &Scl, Mtx &Mtx )
{
	return Mtx.Compose( Trs, Rot, Scl );
}


//------------------------------------------------------------------//
//! @brief	その他
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	符号反転
//--------------------------------------------------------------
inline Mtx &MtxSignReverse  ( Mtx &Mo, const Mtx &M )
{
	return Mo.Set(	-M[e11], -M[e12], -M[e13], -M[e14],
					-M[e21], -M[e22], -M[e23], -M[e24],
					-M[e31], -M[e32], -M[e33], -M[e34],
					-M[e41], -M[e42], -M[e43], -M[e44] );
}


//--------------------------------------------------------------
//! @brief	転置行列の作成
//--------------------------------------------------------------
inline Mtx &MtxTranspose( Mtx &Out,   const Mtx &Src )
{
	return Out.Set( Src[e11], Src[e21], Src[e31], Src[e41],
					Src[e12], Src[e22], Src[e32], Src[e42],
					Src[e13], Src[e23], Src[e33], Src[e43],
					Src[e14], Src[e24], Src[e34], Src[e44] );
}


//----------------------------------------------------------
//! @brief	引数行列をLU分解する
//! @brief	ピボッティングが行われた場合、
//! @brief	引数に置換された行番号が格納される
//! @brief	結果は、
//! @brief			U11 U12 U13 U14
//! @brief			L21 U22 U23 U24
//! @brief			L31 U32 U33 U34
//! @brief			L41 U42 U43 U44
//! @brief	の形で格納される
//
//! @param	pMlu	LU行列
//! @param	pMsrc	元行列
//! @param	pivot	ピボッティングの結果、行順がどう変わったかを格納
//! @rtnval		ピボッティングしたかどうか
//---------------------------------------------------------
inline bool MtxLUDecomp( Mtx &Mlu, const Mtx &Msrc, BYTE *pivot )
{
	return MtxLUDecomp( Mlu, Mlu, Msrc, pivot );
}


//----------------------------------------------------------
//! @brief	引数LU行列の逆行列を求める
//! @param	pMli	L逆行列
//! @param	pMui	U逆行列
//! @param	pMlui	LU逆行列
//! @param	pMl		L行列
//! @param	pMu		U行列
//! @param	pMlu	LU行列
//! @rtnval		逆行列算出ができたかどうか	
//----------------------------------------------------------
inline bool MtxLUInverse( Mtx &Mli, Mtx &Mui, const Mtx &Mlu )
{
	return MtxLUInverse( Mli, Mui, Mlu, Mlu );
}

inline bool MtxLUInverse( Mtx &Mlui, const Mtx &Ml, const Mtx &Mu )
{
	return MtxLUInverse( Mlui, Mlui, Ml, Mu );
}

inline bool MtxLUInverse( Mtx &Mlui, const Mtx &Mlu )
{
	return MtxLUInverse( Mlui, Mlui, Mlu, Mlu );
}


#endif	// #ifndef ___MTX_INL___


