//-----------------------------------------------------------------------------------
//! @file	Vec3.inl
//! @brief	3次元ベクトルと4x4の行列
//! @author	伊藤貴徳
//! @date	07/07/28：編集
//! @date	07/10/16：長大化に伴い分離
//! @date	08/02/11：全体を整理
//-----------------------------------------------------------------------------------


// 3次元ベクトル

#ifndef ___VEC3_INL___
#define ___VEC3_INL___


//===============================================================================//
//	３次元ベクトル
//===============================================================================//

//--------------------------------------------------------------
// 行列からの変換補助
//--------------------------------------------------------------
inline Vec3 &MtxV3TNoW( Vec3 &v, const Mtx &M )
{
	return v.Set( M.XT(), M.YT(), M.ZT() );
}

inline Vec3 &MtxV3NoTNoW( Vec3 &v, const Mtx &M )
{
	return v.Set( M.XNoT(), M.YNoT(), M.ZNoT() );
}

inline Vec3 &MtxV3TW( Vec3 &v, const Mtx &M )
{
	float w = 1.0f / M.WT();
	return v.Set( M.XT()*w, M.YT()*w, M.ZT()*w );
}

inline Vec3 &MtxV3NoTW( Vec3 &v, const Mtx &M )
{
	float w = 1.0f / M.WT();
	return v.Set( M.XNoT()*w, M.YNoT()*w, M.ZNoT()*w );
}

typedef Vec3 &(*MtxConvV3Fnc)( Vec3 &, const Mtx & );

const MtxConvV3Fnc	mtxCnvV3[4] = { MtxV3TNoW, MtxV3NoTNoW, MtxV3TW, MtxV3NoTW };


// D3DX互換
#ifdef ___USE_D3DX___

inline Vec3 &D3DMtxV3TNoW( Vec3 &v, const D3DXMATRIX &M )
{
	return v.Set(	M._11 + M._21 + M._31 + M._41,
					M._12 + M._22 + M._32 + M._42,
					M._13 + M._23 + M._33 + M._43 );
}

inline Vec3 &D3DMtxV3NoTNoW( Vec3 &v, const D3DXMATRIX &M )
{
	return v.Set(	M._11 + M._21 + M._31,
					M._12 + M._22 + M._32,
					M._13 + M._23 + M._33 );
}

inline Vec3 &D3DMtxV3TW( Vec3 &v, const D3DXMATRIX &M )
{
	float w = 1.0f / ( M._14 + M._24 + M._34 + M._44 );
	return v.Set(	(M._11 + M._21 + M._31 + M._41) *w,
					(M._12 + M._22 + M._32 + M._42) *w,
					(M._13 + M._23 + M._33 + M._43) *w );
}

inline Vec3 &D3DMtxV3NoTW( Vec3 &v, const D3DXMATRIX &M )
{
	float w = 1.0f / ( M._14 + M._24 + M._34 + M._44 );
	return v.Set(	(M._11 + M._21 + M._31) *w,
					(M._12 + M._22 + M._32) *w,
					(M._13 + M._23 + M._33) *w );
}

typedef Vec3 &(*D3DMtxConvV3Fnc)( Vec3 &, const D3DXMATRIX & );

const D3DMtxConvV3Fnc	d3dMtxCnvV3[4] = { D3DMtxV3TNoW, D3DMtxV3NoTNoW, D3DMtxV3TW, D3DMtxV3NoTW };

#endif	// #ifdef ___USE_D3DX___



/********************************************************************/
//  ３次元ベクトルクラスメソッド
/********************************************************************/

//--------------------------------------------------------------
//!	@brief	各種コンストラクタ
//--------------------------------------------------------------

inline Vec3::CVector3()
{
}

inline Vec3::CVector3( float x, float y, float z )
{
	Set( x, y, z );
}

inline Vec3::CVector3( const float *p )
{
	Set( p );
}


inline Vec3::CVector3( const Vec3 &V )
{
	*this = V;
}


inline Vec3::CVector3( const Vec3 &Vto, const Vec3 &Vfor )
{
	Set( Vto, Vfor );
}

inline Vec3::CVector3( const Mtx &M, eMtxToVec toVec )
{
	Set( M, toVec );
}

#ifdef ___USE_D3DX___

inline Vec3::CVector3( const D3DXVECTOR2 &D3dVec, float z )
{
	Set( D3dVec, z );
}

inline Vec3::CVector3( const D3DXVECTOR3 &D3dVec )
{
	Set( D3dVec );
}

inline Vec3::CVector3( const D3DXVECTOR4 &D3dVec, bool w )
{
	Set( D3dVec, w );
}

inline Vec3::CVector3( const D3DXVECTOR2 &D3dVto, const D3DXVECTOR2 &D3dVfor, float z )
{
	Set( D3dVto, D3dVfor, z );
}

inline Vec3::CVector3( const D3DXVECTOR3 &D3dVto, const D3DXVECTOR3 &D3dVfor )
{
	Set( D3dVto, D3dVfor );
}

inline Vec3::CVector3( const D3DXMATRIX  &DxMtx, eMtxToVec toVec )
{
	Set( DxMtx, toVec );
}
#endif	// ___USE_D3DX___


//--------------------------------------------------------------
//!	@brief	デストラクタ
//--------------------------------------------------------------
inline Vec3::~CVector3()
{
}


//------------------------------------------------------------------//
// セット
//------------------------------------------------------------------//

//--------------------------------------------------------------
//!	@brief	各種セット
//--------------------------------------------------------------

inline Vec3 &Vec3::Set( float _x, float _y, float _z )
{
	x = _x;
	y = _y;
	z = _z;

	return *this;
}

inline Vec3 &Vec3::Set( const float *p )
{
	memcpy( val, p, sizeof(float)*3 );
	return *this;
}


inline Vec3 &Vec3::Set( const Vec3 &Vto, const Vec3 &Vfor )
{
	x = Vfor.x - Vto.x;
	y = Vfor.y - Vto.y;
	z = Vfor.z - Vto.z;

	return *this;
}

inline Vec3 &Vec3::Set( const Mtx &Mo, eMtxToVec toVec )
{
	return (*(mtxCnvV3[toVec]))( *this, Mo );
}

// 以下暫くはD3DX型互換処理


inline Vec3 &Vec3::Set( const D3DXVECTOR2 &D3dVec, float _z )
{
	x = D3dVec.x;
	y = D3dVec.y;
	z = _z;

	return *this;
}

inline Vec3 &Vec3::Set( const D3DXVECTOR3 &D3dVec )
{
	x = D3dVec.x;
	y = D3dVec.y;
	z = D3dVec.z;

	return *this;
}

inline Vec3 &Vec3::Set( const D3DXVECTOR4 &D3dVec, bool w )
{
	x = D3dVec.x;
	y = D3dVec.y;
	z = D3dVec.z;

	if( w )
	{
		if( IsZero( D3dVec.w ) )
			return *this;
		*this *= (1.0f / D3dVec.w);
	}

	return *this;
}

inline Vec3 &Vec3::Set( const D3DXVECTOR2 &D3dVto, const D3DXVECTOR2 &D3dVfor, float _z )
{
	x = D3dVfor.x - D3dVto.x;
	y = D3dVfor.y - D3dVto.y;
	z = _z;

	return *this;
}

inline Vec3 &Vec3::Set( const D3DXVECTOR3 &D3dVto, const D3DXVECTOR3 &D3dVfor )
{
	x = D3dVfor.x - D3dVto.x;
	y = D3dVfor.y - D3dVto.y;
	z = D3dVfor.z - D3dVto.z;

	return *this;
}

inline Vec3 &Vec3::Set( const D3DXMATRIX  &DxMtx, eMtxToVec toVec )
{
	if( toVec < 0 || toVec > 4 )
		return *this;

	return (*(d3dMtxCnvV3[toVec]))( *this, DxMtx );
}



//------------------------------------------------------------------//
// 各種D3DX型との互換処理
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	関数変換
//--------------------------------------------------------------

inline D3DXVECTOR3 &Vec3::toD3DVEC3( D3DXVECTOR3 &Dv3 ) const
{
	Dv3.x = x;
	Dv3.y = y;
	Dv3.z = z;

	return Dv3;
}

inline D3DXVECTOR4 &Vec3::toD3DVEC4( D3DXVECTOR4 &Dv3, float w ) const
{
	Dv3.x = x;
	Dv3.y = y;
	Dv3.z = z;
	Dv3.w = w;

	return Dv3;
}

inline D3DXMATRIX &Vec3::toD3DMTX( D3DXMATRIX  &D3m )  const
{
	D3DXMatrixIdentity( &D3m ); 
	D3m._11 = x;
	D3m._22 = y;
	D3m._33 = z;

	return D3m;
}


//--------------------------------------------------------------
//! @brief	演算子変換
//--------------------------------------------------------------

inline Vec3::operator D3DXVECTOR3 ()	const
{
	return D3DXVECTOR3( x, y, z );
}

inline Vec3::operator D3DXMATRIX	 ()	const
{
	return D3DXMATRIX( x, 0, 0, 0,
					   0, y, 0, 0,
					   0, 0, z, 0,
					   0, 0, 0, 1 );
}


//--------------------------------------------------------------
//! @brief	代入
//--------------------------------------------------------------

inline Vec3 &Vec3::operator = ( const D3DXVECTOR2  &v )
{
	return Set( v );
}

inline Vec3 &Vec3::operator = ( const D3DXVECTOR3  &v )
{
	return Set( v );
}

inline Vec3 &Vec3::operator = ( const D3DXVECTOR4  &v )
{
	return Set( v );
}

inline Vec3 &Vec3::operator = ( const D3DXMATRIX    &m )
{
	return Set( m );
}
#endif	// #ifdef ___USE_D3DX___



//--------------------------------------------------------------
//! @brief	代入
//--------------------------------------------------------------
inline Vec3 &Vec3::operator = ( const Vec3 &v )
{
	memcpy( val, v.val, sizeof(float)*3 );
	return *this;
}

inline Vec3 &Vec3::operator = ( const Mtx & m )
{
	return Set( m );
}



//------------------------------------------------------------------//
// 各種２項演算子
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	標準四則演算
//--------------------------------------------------------------

// 加算
inline Vec3 Vec3::operator + ( const Vec3 &v2 )		const
{
	return Vec3( x+v2.x, y+v2.y, z+v2.z );
}

// 減算
inline Vec3 Vec3::operator - ( const Vec3 &v2 )		const
{
	return Vec3( x-v2.x, y-v2.y, z-v2.z );
}

// スカラー乗算
inline Vec3 Vec3::operator *( float f )				const
{
	return Vec3( x*f, y*f, z*f );
}

// スカラー除算
inline Vec3 Vec3::operator / ( float f )			const
{
	assert(f);

	float fa = 1.0f / f;
	return Vec3( x*fa, y*fa, z*fa );
}


// フレンド版
inline Vec3 operator *( float f, const Vec3 &v )
{
	return Vec3( f*v.x, f*v.y, f*v.z );
}

inline Vec3 operator / ( float f, const Vec3 &v )
{
assert(f);

	float fa = 1.0f / f;
	return Vec3( v.x*fa, v.y*fa, v.z*fa );
}


//--------------------------------------------------------------
//! @brief	代入四則演算
//--------------------------------------------------------------

// 加算代入
inline Vec3 &Vec3::operator += ( const Vec3 &v2 )
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
	return *this;
}

// 減算代入
inline Vec3 &Vec3::operator -= ( const Vec3 &v2 )
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
	return *this;
}

// スカラー乗算代入
inline Vec3 &Vec3::operator *= ( float f )
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

// スカラー除算代入
inline Vec3 &Vec3::operator /= ( float f )
{
assert(f);

float fa = 1.0f / f;
	x *= fa;
	y *= fa;
	z *= fa;
	return *this;
}


//--------------------------------------------------------------
//! @brief	行列との演算
//! @brief	ベクトルを a = { x, 0, 0, 0,
//! @brief                   0, y, 0, 0,
//! @brief                   0, 0, z, 0,
//! @brief                   0, 0, 0, 1 }
//! @brief	の行列と見做して、引数行列(b)と a*b の演算を行う
//--------------------------------------------------------------
inline Mtx Vec3::operator *( const Mtx &m )		const
{
	return Mtx( m[e11]*x, m[e12]*x, m[e13]*x, m[e14]*x,
				m[e21]*y, m[e22]*y, m[e23]*y, m[e24]*y,
				m[e31]*z, m[e32]*z, m[e33]*z, m[e34]*z,
				m[e41],   m[e42],	m[e43],   m[e44]   );
}



//------------------------------------------------------------------//
// 単項演算子ほか
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	符号反転 
//--------------------------------------------------------------
inline Vec3 Vec3::operator - ()							const
{
	return Vec3( -x, -y, -z );
}


//--------------------------------------------------------------
//! @brief	大きさの２乗 
//--------------------------------------------------------------
inline float Vec3::Norm2()								const
{
	return (x *x + y *y + z *z);
}


//--------------------------------------------------------------
//! @brief	大きさ 
//--------------------------------------------------------------
inline float Vec3::Norm()						const
{
	return sqrtf( x *x + y *y + z *z );
}


//--------------------------------------------------------------
//!	@brief	ビルトイン変換
//--------------------------------------------------------------
inline const float *Vec3::Ptr()					const
{
	return val;
}

inline Vec3::operator const float *()			const
{
	return val;
}

inline Vec3::operator float *()
{
	return val;
}


//------------------------------------------------------------------//
// 論理演算
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	比較
//--------------------------------------------------------------

//	== 演算子
inline bool Vec3::operator == ( const Vec3 & v2 )				const
{
	return !memcmp( val, v2.val, sizeof(float)*3 );
}

//	!= 演算子
inline bool Vec3::operator != ( const Vec3 & v2 )				const
{
	return !(!memcmp( val, v2.val, sizeof(float)*3 ));
}



//------------------------------------------------------------------//
// その他
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	単位化
//--------------------------------------------------------------
inline Vec3 &Vec3::Normalize()
{
	if( this->IsZeroVec() )
		return *this;

	float n = 1.0f / Norm();
	*this *= n;

	return *this;
}


//--------------------------------------------------------------
//! @brief	単位ベクトルであるか判定
//! @brief	ある程度の誤差を許容するため、memcmpは使わない
//--------------------------------------------------------------
inline bool Vec3::IsNormal()					const
{
	return IsZero( Abs( this->Norm2() - 1.0f ) );
}


//--------------------------------------------------------------
//! @brief	ゼロベクトルであるか判定
//! @brief	ある程度の誤差を許容するため、memcmpは使わない
//--------------------------------------------------------------
inline bool Vec3::IsZeroVec()						const
{
	return ( IsZero( x ) && IsZero( y ) && IsZero( z ) );
}


//--------------------------------------------------------------
//! @brief	引数ベクトルとの距離を求める
//--------------------------------------------------------------
inline float Vec3::Dist( const CVector3 &V )		const
{
	return sqrtf( (x-V.x)*(x-V.x) + (y-V.y)*(y-V.y) + (z-V.z)*(z-V.z) );
}


//--------------------------------------------------------------
//! @brief	引数ベクトルとの距離の2乗を求める
//--------------------------------------------------------------
inline float Vec3::Dist2( const CVector3 &V )		const
{
	return (x-V.x)*(x-V.x) + (y-V.y)*(y-V.y) + (z-V.z)*(z-V.z);
}


//--------------------------------------------------------------
//! @brief	(0,0,1)を基準とした極座標を作成する
//! @param	r		距離
//! @param	theta	回転角
//! @param	phi		仰角
//--------------------------------------------------------------
inline Vec3 &Vec3::PolarCoordinate( float r, float theta, float phi )
{
	float c = cosf(phi)*r;
	x = c*sinf(theta);
	y = sinf(phi)*r;
	z = c*cosf(theta);

	return *this;
}


//--------------------------------------------------------------
//! @brief	極座標に於ける距離Ｒを変更する（極座標前提）
//! @param	r		新規距離
//--------------------------------------------------------------
inline Vec3 &Vec3::ChangePolarCoordinateR( float r )
{
	Normalize();
	*this *= r;

	return *this;
}




/********************************************************************/
//  ３次元ベクトル用関数
/********************************************************************/

//------------------------------------------------------------------//
// 四則演算
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	加算
//--------------------------------------------------------------
inline Vec3 &Vec3Add( Vec3 &vo, const Vec3 &vi, const Vec3 &vi2)
{
	return vo.Set( vi.x+vi2.x, vi.y+vi2.y, vi.z+vi2.z );
}


//--------------------------------------------------------------
//! @brief	減算
//--------------------------------------------------------------
inline Vec3 &Vec3Sub( Vec3 &vo, const Vec3 &vi, const Vec3 &vi2)
{
	return vo.Set( vi.x-vi2.x, vi.y-vi2.y, vi.z-vi2.z );
}


//--------------------------------------------------------------
//! @biref	乗算
//--------------------------------------------------------------
inline Vec3 &Vec3Mul( Vec3 &vo, const Vec3 &vi, float f )
{
	return vo.Set( vi.x*f, vi.y*f, vi.z*f );
}


//--------------------------------------------------------------
//! @brief	除算
//--------------------------------------------------------------
inline Vec3 &Vec3Div( Vec3 &vo, const Vec3 &vi, float f )
{
assert(f);

float fa = 1.0f/f;
	return vo.Set( vi.x*fa, vi.y*fa, vi.z*fa );
}



//------------------------------------------------------------------//
// ベクトル演算
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	逆向きを作成
//--------------------------------------------------------------
inline Vec3 &Vec3Reverse( Vec3 &vo, const Vec3 &vi )
{
	return vo.Set( -vi.x, -vi.y, -vi.z );
}


//--------------------------------------------------------------
//! @brief	単位化
//--------------------------------------------------------------
inline Vec3 &Vec3Normalize( Vec3 &vo, const Vec3 &vi )
{
	if( vi.IsZeroVec() )
		return vo;

	float f = 1.0f / vi.Norm();
	return vo.Set( vi.x*f, vi.y*f, vi.z*f );
}


//--------------------------------------------------------------
//! @brief	内積
//--------------------------------------------------------------
inline float Vec3Dot( const Vec3 &v1, const Vec3 &v2 )
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}


//--------------------------------------------------------------
//! @brief	外積
//--------------------------------------------------------------
inline Vec3 &Vec3Cross( Vec3 &vo, const Vec3 &vi1, const Vec3 &vi2 )
{
	float x = vi1.y*vi2.z - vi1.z*vi2.y; 
	float y = vi1.z*vi2.x - vi1.x*vi2.z;
	float z = vi1.x*vi2.y - vi1.y*vi2.x;
	return vo.Set( x, y, z );
}


//--------------------------------------------------------------
//! @brief	交角（ラジアンor度数）
//!	@brief	引数ベクトルは２つとも単位化しておくこと
//--------------------------------------------------------------
inline float Vec3CrossAngle( const Vec3 &v1, const Vec3 &v2)
{
	float f = v1.Norm() * v2.Norm();
	if( IsZero( f ) )	return 0;

	return ANGLE_TYPE( acosf( Vec3Dot( v1, v2 ) / f ) );
}


//--------------------------------------------------------------
//! @brief	ベクトルを回転
//--------------------------------------------------------------

inline Vec3 &Vec3RotationAxisX( Vec3 &vout, const Vec3 &vin, float rot )
{
	float s = sinf( RAD(rot) );
	float c = cosf( RAD(rot) );

	return vout.Set( vin.x,
					 vin.y*c - vin.z*s,
					 vin.y*s + vin.z*c );
}

inline Vec3 &Vec3RotationAxisY( Vec3 &vout, const Vec3 &vin, float rot )
{
	float s = sinf( RAD(rot) );
	float c = cosf( RAD(rot) );

	return vout.Set( vin.x*c + vin.z*s,
					 vin.y,
					-vin.x*s + vin.z*c );
}

inline Vec3 &Vec3RotationAxisZ( Vec3 &vout, const Vec3 &vin, float rot )
{
	float s = sinf( RAD(rot) );
	float c = cosf( RAD(rot) );

	return vout.Set( vin.x*c - vin.y*s,
					 vin.x*s + vin.y*c,
					 vin.z ); 
}


//--------------------------------------------------------------
//! @brief	線形補間
//--------------------------------------------------------------
inline Vec3 &Vec3Lerp( Vec3 &vout, const Vec3 &vin1, const Vec3 &vin2, float t )
{
	vout = vin1 + vin2*t;
	return vout;
}

// よく使うベクトル		@20081126 by佐藤
#define V30				Vec3( .0f,  .0f,  .0f)
#define V31				Vec3(1.0f, 1.0f, 1.0f)
#define	V3X(x)			Vec3(   x,  .0f,  .0f)
#define	V3Y(y)			Vec3( .0f,    y,  .0f)
#define	V3Z(z)			Vec3( .0f,  .0f,    z)
#define V3R(radius)		Vec3((((float)rand()/(float)RAND_MAX)-.5f)*((float)radius)*2.0f, (((float)rand()/(float)RAND_MAX)-.5f)*((float)radius)*2.0f, (((float)rand()/(float)RAND_MAX)-.5f)*((float)radius)*2.0f)
#define V3R1			(V3R(1.0f).Normalize())

// 佐藤@
inline Vec3 Vec3::Normal() const
{
	Vec3 v = *this;
	return v.Normalize();
}

inline Vec3 Vec3::Vertical() const
{
	Vec3 v;

	Vec3 n = *this;
	n.Normalize();

	Vec3 r;
	do
	{
		r = V3R1;
	} while((n-r).IsZeroVec());

	return Vec3Cross(v, r, n);
}

#endif	// #ifndef ___VEC3_INL___