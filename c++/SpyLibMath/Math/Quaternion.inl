//-----------------------------------------------------------
//! @fiule	CQuaternion.inl
//! @brief	�N�H�[�^�I��
//! @author �ɓ��M��
//! @date	07/07/28�F�ҏW
//! @date	08/02/11�F�S�̂𐮗�
//-----------------------------------------------------------


#ifndef ___QUATERNION_INL___
#define ___QUATERNION_INL___


//===============================================================================//
// �N�H�[�^�j�I��
//===============================================================================//

/********************************************************************/
// �N�H�[�^�j�I���N���X���\�b�h
/********************************************************************/

//--------------------------------------------------------------
//!	@brief	�e��R���X�g���N�^
//--------------------------------------------------------------

inline Quat::CQuaternion() : v(.0f,.0f,.0f), w(1.0f)
{
}

inline Quat::CQuaternion( const Vec3 &V, float w )
{ 
	Set( V, w );
}

inline Quat::CQuaternion( float x, float y, float z, float w )
{
	Set( x, y, z, w );
}

inline Quat::CQuaternion( const float *p )
{
	Set( p );
}

inline Quat::CQuaternion( const CQuaternion &q )
{
	*this = q;
}

inline Quat::CQuaternion( const Mtx &M )
{
	Set( M );
}

// D3DX
#ifdef ___USE_D3DX___
inline Quat::CQuaternion( const D3DXVECTOR3 &V, float w )
{
	Set( V, w );
}

inline Quat::CQuaternion( const D3DXVECTOR4 &V )
{
	Set( V );
}

inline Quat::CQuaternion( const D3DXQUATERNION &Q )
{
	Set( Q );
}

inline Quat::CQuaternion( const D3DXMATRIX	 &M )
{
	Set( M );
}
#endif	// D3DX


//--------------------------------------------------------------
//!	@brief	�f�X�g���N�^
//--------------------------------------------------------------
inline Quat::~CQuaternion()
{
}



//--------------------------------------------------------------
//!	@brief	�e��Z�b�g
//--------------------------------------------------------------

inline Quat &Quat::Set( const Vec3 &V, float _w )
{
	v = V;
	w = _w;
	return *this;
}

inline Quat &Quat::Set( float _x, float _y, float _z, float _w )
{
	v.Set( _x, _y, _z  );
	w = _w;
	return *this;
}

inline Quat &Quat::Set( const float *p )
{
assert(
	NULL_CHECK( p, *this );
#endif

	memcpy( val, p, sizeof(float)*4 );
	return *this;
}

// �ȉ��b����D3DX�^�݊��p
#ifdef ___USE_D3DX___
inline Quat &Quat::Set( const D3DXVECTOR3 &V, float _w )
{
assert(
	NULL_CHECK( V, *this );
#endif

	v = V;
	w = _w;
	return *this;
}

inline Quat &Quat::Set( const D3DXVECTOR4 &V )
{
assert(
	NULL_CHECK( V, *this );
#endif

	memcpy( val, V, sizeof(float)*4 );
	return *this;
}

inline Quat &Quat::Set( const D3DXQUATERNION &Q )
{
assert(
	NULL_CHECK( Q, *this );
#endif

	memcpy( val, Q, sizeof(float)*4 );
	return *this;
}



//------------------------------------------------------------------//
//!	@brief	D3DX�^�݊�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�֐����g�p�����ϊ�
//--------------------------------------------------------------
inline D3DXQUATERNION &Quat::toD3DQuat( D3DXQUATERNION &Q )		const
{
	memcpy( Q, val, sizeof(float)*4 );
	return Q;
}		

inline D3DXMATRIX &Quat::toD3DMtx( D3DXMATRIX &M )				const
{
	return Mtx( *this ).toD3DMTX( M );
}


//--------------------------------------------------------------
//! @brief	���Z�q�ϊ�
//--------------------------------------------------------------
inline Quat::operator D3DXQUATERNION ()		const
{
	return D3DXQUATERNION( v.x, v.y, v.z, w );
}

inline Quat::operator D3DXMATRIX	 ()		const
{
	return Mtx( *this );
}


//------------------------------------------------------------------//
//!	@brief	���
//------------------------------------------------------------------//
inline Quat &Quat::operator = ( const D3DXQUATERNION &q )
{
	return Set( q );
}

inline Quat &Quat::operator = ( const D3DXMATRIX &m )
{
	return Set( m );
}
#endif	// #ifdef ___USE_D3DX___



//------------------------------------------------------------------//
//!	@brief	���
//------------------------------------------------------------------//
inline Quat &Quat::operator = ( const Quat & Q )
{
	memcpy( val, Q.val, sizeof(float)*4 );
	return *this;
}

inline Quat &Quat::operator = ( const Mtx &  M )
{
	return Set( M );
}



//------------------------------------------------------------------//
//!	@brie	�傫���A�����Ȃ�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�Y����
//--------------------------------------------------------------
inline float &Quat::operator [] ( differ_type i )
{
assert(
	ClampSet( i, 3, 0 );
#endif
	return val[i];
}

inline float Quat::operator [] ( differ_type i )				const
{
assert(
	ClampSet( i, 3, 0 );
#endif
	return val[i];
}


//--------------------------------------------------------------
//! @brief	�������]
//--------------------------------------------------------------
inline Quat Quat::operator - ()							const
{
	return Quat( -v.x, -v.y, -v.z, -w );
}

//--------------------------------------------------------------
//! @brief	�傫���̂Q��
//--------------------------------------------------------------
inline float Quat::Norm2()								const
{
	return ( v.x*v.x + v.y*v.y + v.z*v.z + w*w);
}


//--------------------------------------------------------------
//! @brief	�傫��
//--------------------------------------------------------------
inline float Quat::Norm()								const
{
	return sqrtf( Norm2() );
}


//--------------------------------------------------------------
//! @brief	�z��擾
//--------------------------------------------------------------
inline const float *Quat::Ptr()							const
{
	return val;
}

inline Quat::operator const float * ()					const
{
	return val;
}

inline Quat::operator float * ()
{
	return val;
}


//------------------------------------------------------------------//
//!	@brie	�W���l�����Z
//------------------------------------------------------------------//

// ���Z
inline Quat Quat::operator + ( const Quat &Q )					const
{
	return Quat( v.x+Q.v.x, v.y+Q.v.y, v.z+Q.v.z, w+Q.w );
}

// ���Z
inline Quat Quat::operator - ( const Quat &Q )					const
{
	return Quat( v.x-Q.v.x, v.y-Q.v.y, v.z-Q.v.z, w-Q.w );
}

// �X�J���[��Z
inline Quat Quat::operator * ( float f )						const
{
	return Quat( v.x*f, v.y*f, v.z*f, w*f );
}

// �X�J���[���Z
inline Quat Quat::operator / ( float f )						const
{
assert(
	if( IsZero( f ) )
		return Quat( *this );
#endif
	float fa = 1.0f / f;
	return Quat( v.x*fa, v.y*fa, v.z*fa, w*fa );
}

// �N�H�[�^�j�I�����m�̏�Z
inline Quat Quat::operator * ( const Quat &Q )					const
{
	return Quat( w*Q.v.x + v.x*Q.w   + v.y*Q.v.z - v.z*Q.v.y,
				 w*Q.v.y - v.x*Q.v.z + v.y*Q.w   + v.z*Q.v.x,
				 w*Q.v.z + v.x*Q.v.y - v.y*Q.v.x + v.z*Q.w,
				 w*Q.w   - v.x*Q.v.x - v.y*Q.v.y - v.z*Q.v.z );
}


//------------------------------------------------------------------//
//!	@brie	����l�����Z
//------------------------------------------------------------------//

// ���Z���
inline Quat &Quat::operator += ( const Quat &Q )
{
	v += Q.v;
	w += Q.w;
	return *this;
}

// ���Z���
inline Quat &Quat::operator -= ( const Quat &Q )
{
	v -= Q.v;
	w -= Q.w;
	return *this;
}

// �X�J���[��Z���
inline Quat &Quat::operator *= ( float f )
{
	v *= f;
	w *= f;
	return *this;
}

// �X�J���[���Z���
inline Quat &Quat::operator /= ( float f )
{
assert(
	if( IsZero( f ) )
		return *this;
#endif
	float fa = 1.0f / f;
	v *= fa;
	w *= fa;
	return *this;
}

// �N�H�[�^�j�I�����m�̏�Z
inline Quat &Quat::operator *= ( const Quat &Q )
{
	return Set( w*Q.v.x + v.x*Q.w   + v.y*Q.v.z - v.z*Q.v.y,
				w*Q.v.y - v.x*Q.v.z + v.y*Q.w   + v.z*Q.v.x,
				w*Q.v.z + v.x*Q.v.y - v.y*Q.v.x + v.z*Q.w,
				w*Q.w   - v.x*Q.v.x - v.y*Q.v.y - v.z*Q.v.z );
}


//------------------------------------------------------------------//
//!	@brie	�t�����h���Z�q
//------------------------------------------------------------------//

inline Quat  operator * ( float f, const Quat &q )
{
	return Quat( f*q.v.x, f*q.v.y, f*q.v.z, f*q.w );
}



//------------------------------------------------------------------//
//!	@brie	�_�����Z�q
//------------------------------------------------------------------//

//	== ���Z�q
inline bool Quat::operator == ( const Quat &Q  )			const
{
	return !memcmp( val, Q.val, sizeof(float)*4 );
}

//	!= ���Z�q
inline bool Quat::operator != ( const Quat & Q  )			const
{
	return !(!memcmp( val, Q.val, sizeof(float)*4 ));
}



//------------------------------------------------------------------//
//!	@brie	���̑�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @biref	�P�ʉ�
//--------------------------------------------------------------
inline Quat &Quat::Normalize()
{
assert(
	float f = Norm();
	if( IsZero( f ) )
		return *this;
	f = 1.0f / f;
#else
	float f = 1.0f / Norm();
#endif
	*this *= f;
	return *this;
}


//--------------------------------------------------------------
//! @biref	�P�ʉ�����Ă��邩���ׂ�
//--------------------------------------------------------------
inline bool Quat::IsNormal()							const
{
	return IsZero( Abs(this->Norm2() - 1.0f) );
}


//--------------------------------------------------------------
//! @biref	�傫���O���ǂ����m���߂�
//--------------------------------------------------------------
inline bool Quat::Zero()								 const
{
	return ( v.IsZeroVec() && IsZero( w ) );
}



/********************************************************************/
// �N�H�[�^�j�I���N���X�p�֐�
/********************************************************************/

//------------------------------------------------------------------//
//!	@brie	���Z�֐�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @biref	���Z
//--------------------------------------------------------------
inline Quat &QuatAdd( Quat &Qo, const Quat &Qi1, const Quat &Qi2 )
{
	return Qo.Set(  Qi1.v.x + Qi2.v.x,
					Qi1.v.y + Qi2.v.y,
					Qi1.v.z + Qi2.v.z,
					Qi1.w   + Qi2.w   );
}


//--------------------------------------------------------------
//! @biref	���Z
//--------------------------------------------------------------
inline Quat &QuatSub( Quat &Qo, const Quat &Qi1, const Quat &Qi2 )
{
	return Qo.Set(  Qi1.v.x - Qi2.v.x,
					Qi1.v.y - Qi2.v.y,
					Qi1.v.z - Qi2.v.z,
					Qi1.w   - Qi2.w   );

}


//--------------------------------------------------------------
//! @biref	�N�H�[�^�j�I�����m�̏�Z
//--------------------------------------------------------------
inline Quat &QuatMul( Quat &Qo, const Quat &Qi1, const Quat &Qi2 )
{
	return Qo.Set(  Qi1.w  *Qi2.v.x + Qi1.v.x*Qi2.w   +
					Qi1.v.y*Qi2.v.z - Qi1.v.z*Qi2.v.y,
					Qi1.w  *Qi2.v.y - Qi1.v.x*Qi2.v.z +
					Qi1.v.y*Qi2.w   + Qi1.v.z*Qi2.v.x,
					Qi1.w  *Qi2.v.z + Qi1.v.x*Qi2.v.y -
					Qi1.v.y*Qi2.v.x + Qi1.v.z*Qi2.w,
					Qi1.w  *Qi2.w   - Qi1.v.x*Qi2.v.x -
					Qi1.v.y*Qi2.v.y - Qi1.v.z*Qi2.v.z );
}


//--------------------------------------------------------------
//! @biref	�X�J���[��Z
//--------------------------------------------------------------
inline Quat &QuatMul( Quat &Qo, const Quat &Qi, float f )
{
	return Qo.Set(  Qi.v.x * f,
					Qi.v.y * f,
					Qi.v.z * f,
					Qi.w   * f );
}


//--------------------------------------------------------------
//! @biref	�X�J���[���Z
//--------------------------------------------------------------
inline Quat &QuatDiv( Quat &Qo, const Quat &Qi, float fa )
{
assert(
	if( IsZero( fa ) )
		return Qo;
#endif
	float f = 1.0f / fa;
	return Qo.Set( Qi.v.x*f, Qi.v.y*f, Qi.v.z*f, Qi.w*f );
}


//--------------------------------------------------------------
//! @brief	����
//--------------------------------------------------------------
inline float QuatDot( const Quat &Q1, const Quat &Q2 )
{
	return Vec3Dot( Q1.v, Q2.v ) + Q1.w*Q2.w;
}



//------------------------------------------------------------------//
//!	@brie	�e�폈��
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�P�ʉ�
//--------------------------------------------------------------
inline Quat &QuatNormalize( Quat &Qo, const Quat &Qi )
{
	if( Qi.Zero() )
		return Qo;

	float f = 1.0f / Qi.Norm();
	Qo = Qi;
	return Qo *= f;
}


//--------------------------------------------------------------
//! @brief	���]
//--------------------------------------------------------------
inline Quat &QuatReverse( Quat &Qo, const Quat &Qi )
{
	return Qo.Set( -Qi.v.x, -Qi.v.y, -Qi.v.z, -Qi.w );
}


//--------------------------------------------------------------
//! @brief	������Ԃ�
//--------------------------------------------------------------
inline Quat &QuatConjugugate( Quat &Qo, const Quat &Qi )
{
	return Qo.Set( -Qi.v.x, -Qi.v.y, -Qi.v.z, Qi.w );
}


//--------------------------------------------------------------
//! @brief	�t����Ԃ�
//--------------------------------------------------------------
inline Quat &QuatInverse( Quat &Qo, const Quat &Qi )
{
assert(
	if( Qi.Zero() )
		return Qo;
#endif

	float f = 1.0f / Qi.Norm2();

	QuatConjugugate( Qo, Qi );
	Qo *= f;

	return Qo;
}


//--------------------------------------------------------------
//! @brief	�N�H�[�^�j�I����]
//--------------------------------------------------------------
inline Quat &QuatRotation( Quat &Qo, const Vec3  &Vaxis, float rot )
{
	Vec3 axis = Vaxis;
	float s = sinf( RAD(rot * .5f) );
	float c = cosf( RAD(rot * .5f) );

	axis.Normalize();
	return Qo.Set( s*axis.x, s*axis.y, s*axis.z, c );
}

// ���ʂ��s��ɂ��ĕԂ�
inline Mtx &QuatRotation( Mtx &Mo, const Vec3  &Vaxis, float rot )
{
	Quat q;
	Mo = QuatRotation( q, Vaxis, rot );

	return Mo;
}


//--------------------------------------------------------------
//! @brief	���[�s�b�`���[���ŉ�]
//--------------------------------------------------------------
inline Quat &QuatRotationYPR( Quat &Qo, const Vec3  &Rot )
{
	float cY = cosf( RAD(Rot.x * .5f) );
	float sY = sinf( RAD(Rot.x * .5f) );
	float cP = cosf( RAD(Rot.y * .5f) );
	float sP = sinf( RAD(Rot.y * .5f) );
	float cR = cosf( RAD(Rot.z * .5f) );
	float sR = sinf( RAD(Rot.z * .5f) );

	return Qo.Set(  cY * sP * cR + sY * cP * sR,
					sY * cP * cR - cY * sP * sR,
					cY * cP * sR - sY * sP * cR,
				  -(cY * cP * cR + sY * sP * sR) );
}

// ���ʂ��s��ŕԂ�
inline Mtx &QuatRotationYPR( Mtx &Mo, const Vec3  &Rot )
{
	Quat q;
	Mo = QuatRotationYPR( q, Rot);

	return Mo;
}



#endif	// #ifndef ___QUATERNION_INL___