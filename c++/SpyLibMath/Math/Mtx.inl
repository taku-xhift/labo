//-----------------------------------------------------------------------------------
//! @file	Mtx.inl
//! @brief	4x4�̍s��
//! @author	�ɓ��M��
//! @date	07/07/28�F�ҏW
//! @date	07/08/05�F�s�񃁃\�b�h�Ɋe��ϊ��s��쐬��ǉ�
//! @date	07/08/26�F�s��̃A�N�Z�b�T������
//! @date			  �s��̂k�t������ǉ�
//! @date	07/09/01�F�t�s��v�Z���k�t������p�������̂ɕύX
//! @date			  �x�N�g���̔C�ӎ���]��ǉ�
//! @date	07/09/08�F�s���()���Z�q�ǉ�
//! @date	07/10/16�F���剻�ɔ�������
//! @date	08/02/11�F�S�̂𐮗�
//-----------------------------------------------------------------------------------


// 4*4�s��

#ifndef ___MTX_INL___
#define ___MTX_INL___


//===============================================================================//
//	�s��
//===============================================================================//

/********************************************************************/
//  4*4�s��N���X���\�b�h
/********************************************************************/

//------------------------------------------------------------------//
//! @brief �e��R���X�g���N�^
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

// D3DX�݊�
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
//! @brief �f�X�g���N�^
//------------------------------------------------------------------//
inline Mtx::~CMatrix44()
{
}



//------------------------------------------------------------------//
//! @brief D3DX�݊�����
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�֐��ϊ�
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
//! @brief	���Z�q�ϊ�
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
//! @brief	���
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
//! @brief �Z�b�g
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�v�f���w�肵�ăZ�b�g
//! @param	num		�v�f�C���f�b�N�X
//! @param	val		�l
//--------------------------------------------------------------
inline void Mtx::SetVal( differ_type num, float val )
{ 
	ClampSet( num, 15, 0 );

	m_m[num] = val;
}


//--------------------------------------------------------------
//! @brief	�v�f���w�肵�ăZ�b�g
//! @param	row		�s�ԍ�(0-3)
//! @param	col		��ԍ�(0-3)
//! @param	val		�l
//--------------------------------------------------------------
inline void Mtx::SetVal( differ_type row, differ_type col, float val )
{
	ClampSet( col, 3, 0 );
	ClampSet( row, 3, 0 );

	m_m[row + col*4] = val;
}


//--------------------------------------------------------------
//! @brief	�s�Z�b�g
//! @param	rowNo		�s�ԍ�(0-3)
//! @param	pV			�x�N�g���ɂ��l
//! @param	trs			���s�ړ�����
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
//! @brief	��Z�b�g
//! @param	colNo		��ԍ�(0-3)
//! @param	pV			�x�N�g���ɂ��l
//! @param	w			W����
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
//! @brief	�ꊇ�Z�b�g
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


// �ȉ��b����D3DX�^�݊�����
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
//! @brief �Q�b�g
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�ύX�s�\�ȎQ�Ƃ��ꊇ�擾
//-------------------------------------------------------------
inline const float  *Mtx::GetMatrix()	   const
{
	return m_m;
}


//--------------------------------------------------------------
//! @brief	�ύX�\�ȎQ�Ƃ��ꊇ�擾
//-------------------------------------------------------------
inline float  *Mtx::GetMatrix()
{
	return m_m;
}


//--------------------------------------------------------------
//! @brief	�s��f�[�^���R�s�[
//-------------------------------------------------------------
inline float  *Mtx::GetMatrix( float *pMo )  const
{
assert(
	NULL_CHECK( pMo, pMo );
#endif
	return (float*)memcpy( pMo, m_m, sizeof( float ) << 4 );
}


//--------------------------------------------------------------
//!	@brief	�r���g�C���ϊ�
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
//! @brief	�v�f���w�肵�Ēl���擾
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
//! @brief	�v�f���w�肵�Ēl���擾
//! @param	row		�s�C���f�b�N�X(0-3)
//! @param	col		��C���f�b�N�X(0-3)
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
//! @brief		�Y�������Z�q
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
//! @brief		()���Z�q
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
//! @brief	�s�擾
//! @param	pV		�s�i�[�x�N�g��
//! @param	rowNo	�s�ԍ�(0-3)
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
//! @brief	��擾
//! @param	pV		��i�[�x�N�g��
//! @param	colNo	��ԍ�(0-3)
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
//! @brief	���s�ړ����݂̃x�N�g���v�f�Ƃ��Ď擾
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
//! @brief	���s�ړ��Ȃ��̃x�N�g���v�f�Ƃ��Ď擾
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
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fX���擾
//! @brief	���s�ړ��v�f����
//--------------------------------------------------------------
inline float Mtx::VecXT( const Vec3 &V )			const
{
	return m_m[e11]*V.x + m_m[e12]*V.y + m_m[e13]*V.z + m_m[e14];
}


//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fY���擾
//! @brief	���s�ړ��v�f����
//--------------------------------------------------------------
inline float Mtx::VecYT( const Vec3 &V )			const
{
	return m_m[e21]*V.x + m_m[e22]*V.y + m_m[e23]*V.z + m_m[e24];
}



//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fZ���擾
//! @brief	���s�ړ��v�f����
//--------------------------------------------------------------
inline float Mtx::VecZT( const Vec3 &V )			const
{
	return m_m[e31]*V.x + m_m[e32]*V.y + m_m[e33]*V.z + m_m[e34];
}


//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fW���擾
//! @brief	���s�ړ��v�f����
//--------------------------------------------------------------
inline float Mtx::VecWT( const Vec3 &V )			const
{
	return m_m[e41]*V.x + m_m[e42]*V.y + m_m[e43]*V.z + m_m[e44];
}


//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fX���擾
//! @brief	���s�ړ��v�f�Ȃ�
//--------------------------------------------------------------
inline float Mtx::VecXNoT( const Vec3 &V )			const
{
	return m_m[e11]*V.x + m_m[e12]*V.y + m_m[e13]*V.z;
}



//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fY���擾
//! @brief	���s�ړ��v�f�Ȃ�
//--------------------------------------------------------------
inline float Mtx::VecYNoT( const Vec3 &V )			const
{
	return m_m[e21]*V.x + m_m[e22]*V.y + m_m[e23]*V.z;
}


//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fZ���擾
//! @brief	���s�ړ��v�f�Ȃ�
//--------------------------------------------------------------
inline float Mtx::VecZNoT( const Vec3 &V )			const
{
	return m_m[e31]*V.x + m_m[e32]*V.y + m_m[e33]*V.z;
}


//--------------------------------------------------------------
//! @brief	�����x�N�g���Ə�Z���ăx�N�g���v�fW���擾
//! @brief	���s�ړ��v�f�Ȃ�
//--------------------------------------------------------------
inline float Mtx::VecWNoT( const Vec3 &V )			const
{
	return m_m[e41]*V.x + m_m[e42]*V.y + m_m[e43]*V.z;
}


//------------------------------------------------------------------//
//! @brief �e����
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�x�N�g�����
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const Vec3 &rV )
{
	return Set( rV );
}


//--------------------------------------------------------------
//! @brief	�N�H�[�^�j�I�����
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const CQuaternion &rQ )
{
	return Set( rQ );
}


//--------------------------------------------------------------
//! @brief	�s����
//--------------------------------------------------------------
inline Mtx &Mtx::operator = ( const Mtx &m )
{
	memcpy( m_m, m.GetMatrix(), sizeof( float ) << 4 );
	return *this;
}



//------------------------------------------------------------------//
//! @brief �e�퉉�Z�q
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�W���l�����Z
//--------------------------------------------------------------

// ���Z
inline Mtx  Mtx::operator +  ( const Mtx &M )		const
{
	return Mtx( m_m[e11]+M[e11], m_m[e12]+M[e12], m_m[e13]+M[e13], m_m[e14]+M[e14],
				m_m[e21]+M[e21], m_m[e22]+M[e22], m_m[e23]+M[e23], m_m[e24]+M[e24],
				m_m[e31]+M[e31], m_m[e32]+M[e32], m_m[e33]+M[e33], m_m[e34]+M[e34],
				m_m[e41]+M[e41], m_m[e42]+M[e42], m_m[e43]+M[e43], m_m[e44]+M[e44] );
}

// ���Z
inline Mtx  Mtx::operator -  ( const Mtx &M )		const
{
	return Mtx( m_m[e11]-M[e11], m_m[e12]-M[e12], m_m[e13]-M[e13], m_m[e14]-M[e14],
				m_m[e21]-M[e21], m_m[e22]-M[e22], m_m[e23]-M[e23], m_m[e24]-M[e24],
				m_m[e31]-M[e31], m_m[e32]-M[e32], m_m[e33]-M[e33], m_m[e34]-M[e34],
				m_m[e41]-M[e41], m_m[e42]-M[e42], m_m[e43]-M[e43], m_m[e44]-M[e44] );
}

// �X�J���[��Z
inline Mtx  Mtx::operator * ( float f )				const
{
	return Mtx( m_m[e11]*f, m_m[e12]*f, m_m[e13]*f, m_m[e14]*f,
				m_m[e21]*f, m_m[e22]*f, m_m[e23]*f, m_m[e24]*f,
				m_m[e31]*f, m_m[e32]*f, m_m[e33]*f, m_m[e34]*f,
				m_m[e41]*f, m_m[e42]*f, m_m[e43]*f, m_m[e44]*f );
}

// �X�J���[���Z
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
//! @brief	����l�����Z
//--------------------------------------------------------------

// ���Z���
inline Mtx &Mtx::operator += ( const Mtx &M )
{
	m_m[e11]+=M[e11]; m_m[e12]+=M[e12]; m_m[e13]+=M[e13]; m_m[e14]+=M[e14];
	m_m[e21]+=M[e21]; m_m[e22]+=M[e22]; m_m[e23]+=M[e23]; m_m[e24]+=M[e24];
	m_m[e31]+=M[e31]; m_m[e32]+=M[e32]; m_m[e33]+=M[e33]; m_m[e34]+=M[e34];
	m_m[e41]+=M[e41]; m_m[e42]+=M[e42]; m_m[e43]+=M[e43]; m_m[e44]+=M[e44];
	return *this;
}

// ���Z���
inline Mtx &Mtx::operator -= ( const Mtx &M )
{
	m_m[e11]+=M[e11]; m_m[e12]+=M[e12]; m_m[e13]+=M[e13]; m_m[e14]+=M[e14];
	m_m[e21]+=M[e21]; m_m[e22]+=M[e22]; m_m[e23]+=M[e23]; m_m[e24]+=M[e24];
	m_m[e31]+=M[e31]; m_m[e32]+=M[e32]; m_m[e33]+=M[e33]; m_m[e34]+=M[e34];
	m_m[e41]+=M[e41]; m_m[e42]+=M[e42]; m_m[e43]+=M[e43]; m_m[e44]+=M[e44];
	return *this;
}

// �X�J���[��Z���
inline Mtx &Mtx::operator *= ( float f )
{
	m_m[e11]*=f; m_m[e12]*=f; m_m[e13]*=f; m_m[e14]*=f;
	m_m[e21]*=f; m_m[e22]*=f; m_m[e23]*=f; m_m[e24]*=f;
	m_m[e31]*=f; m_m[e32]*=f; m_m[e33]*=f; m_m[e34]*=f;
	m_m[e41]*=f; m_m[e42]*=f; m_m[e43]*=f; m_m[e44]*=f;
	return *this;
}

// �X�J���[���Z���
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
//! @brief	�x�N�g���Ƃ̉��Z
//! @brief	w �����ł̏��Z�͍s��Ȃ� 
//--------------------------------------------------------------
inline Vec3  Mtx::operator *( const Vec3 &v )			const
{
	return Vec3( VecXT( v ), VecYT( v ), VecZT( v ) );
}



//--------------------------------------------------------------
//! @brief	�t�����h���Z�q
//--------------------------------------------------------------
inline Mtx  operator  *( float f, const Mtx &m )
{
	return Mtx( m.m_m[e11]*f, m.m_m[e12]*f, m.m_m[e13]*f, m.m_m[e14]*f,
				m.m_m[e21]*f, m.m_m[e22]*f, m.m_m[e23]*f, m.m_m[e24]*f,
				m.m_m[e31]*f, m.m_m[e32]*f, m.m_m[e33]*f, m.m_m[e34]*f,
				m.m_m[e41]*f, m.m_m[e42]*f, m.m_m[e43]*f, m.m_m[e44]*f );
}


//------------------------------------------------------------------//
//! @brief	�_�����Z
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	��r
//--------------------------------------------------------------

//	== ���Z�q
inline bool Mtx::operator == ( const Mtx &m  )			const
{
	return !memcmp( m_m, m.m_m, sizeof(float)*16 );
}

//	 != ���Z�q
inline bool Mtx::operator != ( const Mtx &m  )			const
{
	return !(!memcmp( m_m, m.m_m, sizeof(float)*16 ));
}



//------------------------------------------------------------------//
//! @brief	���̑�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�������]
//--------------------------------------------------------------
inline Mtx Mtx::operator - ()						const
{
	return Mtx( -m_m[e11], -m_m[e12], -m_m[e13], -m_m[e14],
				-m_m[e21], -m_m[e22], -m_m[e23], -m_m[e24],
				-m_m[e31], -m_m[e32], -m_m[e33], -m_m[e34],
				-m_m[e41], -m_m[e42], -m_m[e43], -m_m[e44] );
}


//--------------------------------------------------------------
//! @brief	�P�ʍs��쐬
//--------------------------------------------------------------
inline CMatrix44& Mtx::Identity()
{
	m_m[e11] = m_m[e22] = m_m[e33] = m_m[e44] = 1;
	m_m[e12] = m_m[e13] = m_m[e14] = m_m[e21] = m_m[e23] = m_m[e24] = 
	m_m[e31] = m_m[e32] = m_m[e34] = m_m[e41] = m_m[e42] = m_m[e43] = 0;
	return *this;	
}


//--------------------------------------------------------------
//! @brief	�P�ʍs�񂩂ǂ������ׂ�
//! @brief	������x�̌덷�����e���邽�߁Amemcmp�͎g��Ȃ�
//--------------------------------------------------------------
inline bool Mtx::IsIdentity()				const
{
	// ������h�����A�L���b�V�������������ߏ��ԂɃA�N�Z�X����
	// �}�N����`�ɂ�鑬�x�̈Ⴂ��h�����߁A�񋓂ł͂Ȃ������̒��ł��ōs��
	return ( IsZero( m_m[0]-1.0f ) && IsZero( m_m[1] )      && IsZero( m_m[2] )       && IsZero( m_m[3] )  &&
			 IsZero( m_m[4] )      && IsZero( m_m[5]-1.0f ) && IsZero( m_m[6] )       && IsZero( m_m[7] )  &&
			 IsZero( m_m[8] )      && IsZero( m_m[9] )      && IsZero( m_m[10]-1.0f ) && IsZero( m_m[11] ) &&
			 IsZero( m_m[12] )     && IsZero( m_m[13] )     && IsZero( m_m[14] )      && IsZero( m_m[15]-1.0f ));
}


//------------------------------------------------------------------//
// �s���{�ό`����
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�s����ւ�
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
//! @brief	�����ւ�
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
//! @brief	�s�ɌW�����|����
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
//! @brief	��ɌW�����|����
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
// �e��ϊ��s��쐬
//------------------------------------------------------------------//

//------------------------------------------------------------------//
//! @brief	X����]�s��쐬
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
//! @brief	Y����]�s��쐬
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
//! @brief	Z����]�s��쐬
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
//! @brief	�w����W���SX����]�s��쐬
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationXPivot( const Vec3 &pos, float rad )
{
	return RotationXPivot( pos.x, pos.y, pos.z, rad );
}


//------------------------------------------------------------------//
//! @brief	�w����W���SY����]�s��쐬
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationYPivot( const Vec3 &pos, float rad )
{
	return RotationYPivot( pos.x, pos.y, pos.z, rad );
}

//------------------------------------------------------------------//
//! @brief	�w����W���SZ����]�s��쐬
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationZPivot( const Vec3 &pos, float rad )
{
	return RotationZPivot( pos.x, pos.y, pos.z, rad );
}



//------------------------------------------------------------------//
//! @brief	�X�P�[�����O�s��̍쐬
//------------------------------------------------------------------//
inline Mtx &Mtx::Scaling( const Vec3 &Scl )
{
	return Scaling( Scl.x, Scl.y, Scl.z );
}


//------------------------------------------------------------------//
//! @brief	�X�P�[�����O�s��̍쐬
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
//! @brief	�w��ʒu���S�X�P�[�����O�s��̍쐬
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
//! @brief	���s�ړ��s��̍쐬
//------------------------------------------------------------------//
inline Mtx &Mtx::Translate( const Vec3 &Trs )
{
	return Translate( Trs.x, Trs.y, Trs.z );
}


//------------------------------------------------------------------//
//! @brief	���s�ړ��s��̍쐬
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
//! @brief	���s�ړ��p�����[�^�̃Z�b�g
//! @brief	���̗v�f�͕ύX���Ȃ�
//------------------------------------------------------------------//
inline Mtx &Mtx::SetTranslate( const Vec3 &Trs )
{
	return SetTranslate( Trs.x, Trs.y, Trs.z );
}


//------------------------------------------------------------------//
//! @brief	���s�ړ��p�����[�^�̃Z�b�g
//! @brief	���̗v�f�͕ύX���Ȃ�
//------------------------------------------------------------------//
inline Mtx &Mtx::SetTranslate( float x, float y, float z )
{
	m_m[e14] = x;
	m_m[e24] = y;
	m_m[e34] = z;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	���s�ړ��p�����[�^�ɉ��Z
//! @brief	���̗v�f�͕ύX���Ȃ�
//------------------------------------------------------------------//
inline Mtx &Mtx::AddTranslate( const Vec3 &Trs )
{
	return AddTranslate( Trs.x, Trs.y, Trs.z );
}


//------------------------------------------------------------------//
//! @brief	���s�ړ��p�����[�^�ɉ��Z
//! @brief	���̗v�f�͕ύX���Ȃ�
//------------------------------------------------------------------//
inline Mtx &Mtx::AddTranslate( float x, float y, float z )
{
	m_m[e14] += x;
	m_m[e24] += y;
	m_m[e34] += z;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	�C�ӎ����S�ŉ�]����s����쐬
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationAxis( float x, float y, float z, float rad )
{
	return RotationAxis( Vec3( x, y, z ), rad );
}

inline Mtx &Mtx::RotationAxis( const CQuaternion &q )
{
	return Set( q );
}


// ��]�s����w��ʒu���S�ɂȂ�悤�ɂ���
#define ROTATION_TRANSLATE( pos )	m_m[e14] = -m_m[e11]*pos.x -m_m[e12]*pos.y -m_m[e13]*pos.z +pos.x;	\
									m_m[e24] = -m_m[e21]*pos.x -m_m[e22]*pos.y -m_m[e23]*pos.z +pos.y;	\
									m_m[e34] = -m_m[e31]*pos.x -m_m[e32]*pos.y -m_m[e33]*pos.z +pos.z;
//------------------------------------------------------------------//
//! @brief	�w��ʒu�C�ӎ����S�ŉ�]����s����쐬
//! @brief	���x�N�g���͒P�ʉ����Ă�������
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
//! @brief	���[�s�b�`���[���w��ŉ�]����s����쐬
//! @brief	x=pitch, y =yaw, z=roll �Ŏw�肷�邱��
//! @brief	���A���ۂ̌v�Z�����͍ł��悭�g���� Roll Pitch Yaw 
//! @brief	�̏��ōs����(D3DXMatrixRotationYawPitchRoll�֐��Ɠ���)
//------------------------------------------------------------------//
inline Mtx &Mtx::RotationYPR( const Vec3 &YPR )
{
	return RotationYPR( YPR.x, YPR.y, YPR.z );
}


//------------------------------------------------------------------//
//! @brief	�w��ʒu�Ń��[�s�b�`���[����]����s����쐬
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
//! @brief	�ϊ��s��̍쐬
//! @param	pTrs	���s�ړ�
//! @param	pRot	��]
//! @param	pScl	�X�P�[�����O
//! @rtnval		�ϊ���s��	
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
//! @brief	���s�ړ������݂̂��擾
//--------------------------------------------------------------
inline Vec3 &Mtx::GetTranslate( Vec3 &V )					const
{
	return V.Set( m_m[e14], m_m[e24], m_m[e34] );
}

//--------------------------------------------------------------
//! @brief	�X�P�[�������݂̂��擾
//--------------------------------------------------------------
inline Vec3 &Mtx::GetScale( Vec3 &V )						const
{
	CVector3 x( m_m[e11], m_m[e21], m_m[e31] );
	CVector3 y( m_m[e12], m_m[e22], m_m[e32] );
	CVector3 z( m_m[e13], m_m[e23], m_m[e33] );

	return V.Set( x.Norm(), y.Norm(), z.Norm() );
}



/********************************************************************/
//  4*4�s��N���X�p�֐�
/********************************************************************/

//------------------------------------------------------------------//
//! @brief	�l�����Z�֐�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	���Z
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
//! @brief	���Z
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
//! @brief	��Z
//! @brief	pVo = pMi1 *pVi;
//! @brief	flag	�v�Z����(�f�t�H���g�͕��s�ړ����� w ���Z�Ȃ�)
//--------------------------------------------------------------

// �⏕�֐�
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

// �{��
inline Vec3 &MtxMul( Vec3 &Vo, const Mtx &Mi, const Vec3 &Vi, eMtxToVec flag )
{
assert(
	if( (flag < 0) || (flag > 4) )
		return Vo;
#endif

	return (*(mtxXvec[flag]))( Vo, Mi, Vi );
}



//--------------------------------------------------------------
//! @brief	��Z
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
//! @brief	��Z
//! @brief	pO = pMI *f;
//--------------------------------------------------------------
inline Mtx &MtxMul( Mtx &Out, const Mtx &In,  float f  )
{
	return MtxMul( Out, f, In );
}


//--------------------------------------------------------------
//! @brief	���Z
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
//! @brief	�w����W�ʒu�ł̊e�����S��]�s����v�Z
//------------------------------------------------------------------//

// �����s��*��]�s��
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


// ��]�s��*�����s��
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
//! @brief	�s��ƃN�H�[�^�j�I����p������]�Ƃ̉��Z���s��
//------------------------------------------------------------------//

// �s�� *= �N�H�[�^�j�I��
inline Mtx &MtxRotationQuat( Mtx &mtx, const CQuaternion &Quat )
{
	Mtx m( Quat );
	mtx *= m;
	return mtx;
}


// �s��=�N�H�[�^�j�I��*�s��
inline Mtx &MtxRotationQuat( const CQuaternion &Quat, Mtx &mtx )
{
	Mtx m( Quat );
	m *= mtx;
	mtx = m;
	return mtx;
}


//------------------------------------------------------------------//
//! @brief	�s��Ǝw����W���S�̃N�H�[�^�j�I����p������]�Ƃ̉��Z���s��
//------------------------------------------------------------------//

// �s�� *= �N�H�[�^�j�I��
inline Mtx &MtxRotationQuatPivot( Mtx &mtx, const CQuaternion &Quat, const Vec3 &pos )
{
	Mtx m( false );
	m.RotationAxisPivot( Quat, pos );
	mtx *= m;
	return mtx;
}


// �s��=�N�H�[�^�j�I��*�s��
inline Mtx &MtxRotationQuatPivot( const CQuaternion &Quat, const Vec3 &pos, Mtx &mtx )
{
	Mtx m( false );
	m.RotationAxisPivot( Quat, pos );
	m *= mtx;
	mtx = m;
	return mtx;
}



//------------------------------------------------------------------//
//! @brief	���s�ړ��s��Ƃ̉��Z���s��
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�����s��*���s�ړ��s��
//! @brief	pMo *= �ړ���(x, y, z)�̍s�� 
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
//! @brief	���s�ړ��s��*�����s��
//! @brief	Mo = �ړ���(x, y, z)�̍s�� *Mo
//--------------------------------------------------------------
inline Mtx &MtxMulTranslate( const Vec3 &v, Mtx &Mo )
{
	return MtxMulTranslate( v.x, v.y, v.z, Mo );
}



//------------------------------------------------------------------//
//! @brief	�X�P�[�����O�s��Ƃ̉��Z���s��
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�����s��*�X�P�[�����O�s��
//! @brief	Mo *= �g�嗦(x, y, z)�̍s��
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
//! @brief	�X�P�[�����O�s��*�����s��
//! @brief	Mo = �g�嗦(x, y, z)�̍s�� *Mo
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
//! @brief	�w����W���S�X�P�[�����O�s��Ƃ̉��Z���s��
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�����s��*�X�P�[�����O�s��
//! @brief	Mo *= pos���S�Ŋg�嗦scl�̍s��
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
//! @brief	�ϊ��s��̍쐬
//! @param	pTrs	���s�ړ�
//! @param	pRot	��]
//! @param	pScl	�X�P�[�����O
//! @rtnval		�ϊ���s��	
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
//! @brief	���̑�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�������]
//--------------------------------------------------------------
inline Mtx &MtxSignReverse  ( Mtx &Mo, const Mtx &M )
{
	return Mo.Set(	-M[e11], -M[e12], -M[e13], -M[e14],
					-M[e21], -M[e22], -M[e23], -M[e24],
					-M[e31], -M[e32], -M[e33], -M[e34],
					-M[e41], -M[e42], -M[e43], -M[e44] );
}


//--------------------------------------------------------------
//! @brief	�]�u�s��̍쐬
//--------------------------------------------------------------
inline Mtx &MtxTranspose( Mtx &Out,   const Mtx &Src )
{
	return Out.Set( Src[e11], Src[e21], Src[e31], Src[e41],
					Src[e12], Src[e22], Src[e32], Src[e42],
					Src[e13], Src[e23], Src[e33], Src[e43],
					Src[e14], Src[e24], Src[e34], Src[e44] );
}


//----------------------------------------------------------
//! @brief	�����s���LU��������
//! @brief	�s�{�b�e�B���O���s��ꂽ�ꍇ�A
//! @brief	�����ɒu�����ꂽ�s�ԍ����i�[�����
//! @brief	���ʂ́A
//! @brief			U11 U12 U13 U14
//! @brief			L21 U22 U23 U24
//! @brief			L31 U32 U33 U34
//! @brief			L41 U42 U43 U44
//! @brief	�̌`�Ŋi�[�����
//
//! @param	pMlu	LU�s��
//! @param	pMsrc	���s��
//! @param	pivot	�s�{�b�e�B���O�̌��ʁA�s�����ǂ��ς���������i�[
//! @rtnval		�s�{�b�e�B���O�������ǂ���
//---------------------------------------------------------
inline bool MtxLUDecomp( Mtx &Mlu, const Mtx &Msrc, BYTE *pivot )
{
	return MtxLUDecomp( Mlu, Mlu, Msrc, pivot );
}


//----------------------------------------------------------
//! @brief	����LU�s��̋t�s������߂�
//! @param	pMli	L�t�s��
//! @param	pMui	U�t�s��
//! @param	pMlui	LU�t�s��
//! @param	pMl		L�s��
//! @param	pMu		U�s��
//! @param	pMlu	LU�s��
//! @rtnval		�t�s��Z�o���ł������ǂ���	
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


