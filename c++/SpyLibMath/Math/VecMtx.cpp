//-----------------------------------------------------------------------------
//! @file	VecMat.cpp
//! @brief	2-4�����x�N�g����4x4�̍s��
//! @author �ɓ��M��
//! @date	07/07/15�F�ĕ�
//! @date	07/08/05�F�s�񃁃\�b�h�Ɋe��ϊ��s��쐬��ǉ�
//! @date	07/08/11�F�Q�������S�����x�N�g����ǉ�
//! @date			  �x�N�g���̒ǉ��ɔ����I�[�o�[���[�h����
//! @date	07/08/26�F�s��̃A�N�Z�b�T������
//! @date			  �s��̂k�t������ǉ�
//! @date	07/09/01�F�t�s��v�Z���k�t������p�������̂ɕύX
//! @date			  �x�N�g���̔C�ӎ���]��ǉ�
//! @date	08/02/11�F�S�̂𐮗�
//-----------------------------------------------------------------------------

#include "VecMtx.h"
#include "Quaternion.h"
#include "Geometry.h"


//===============================================================================//
// �Q�����x�N�g��
//===============================================================================//


//--------------------------------------------------------------
//! @brief �G���~�[�g���
//! @param	vin1	�x�N�g���P
//! @param	vtan1	vin1�̐ڐ��x�N�g��
//! @param	vin2	�x�N�g���Q
//! @param	vtan2	vin2�̐ڐ��x�N�g��
//! @param	t		�����l
//--------------------------------------------------------------
Vec2 &Vec2Hermite( Vec2 &vout, const Vec2 &vin1, const Vec2 &vtan1,
					const Vec2 &vin2, const Vec2 &vtan2, float t )
{
	Vec2 vA, vB;
	float t2 = t*t;

	vA = 2.0f *( vin1 - vin2 ) + vtan1 + vtan2;
	vB = 3.0f *( vin2 - vin1 ) - vtan1*2.0f - vtan2;
	vout = vA*(t2*t) + vB*t2 + vtan1*t + vin1;

	return vout;
}



//===============================================================================//
// �R�����x�N�g��
//===============================================================================//

//--------------------------------------------------------------
//! @brief �x�N�g����C�ӂ̒P�ʃx�N�g������ɉ�]
//! @param	vout	�o��
//! @param	vin	���̓x�N�g��
//! @param	vaxis	��]���x�N�g���i�����ŒP�ʉ��j
//! @param	rot		��]�p
//--------------------------------------------------------------
Vec3 &Vec3RotationAxis ( Vec3 &Vout, const Vec3 &Vin, const Vec3 &Vaxis, float rot )
{
/*
	�x�N�g���̔C�ӎ����S�ŉ�]�����鎮�́A���h���O�̌����ƈ�ʂɌĂ΂��ȉ��̎��ŗ^������

	v' = �o��
	v = ���x�N�g��
	n = �P�ʉ����ꂽ���x�N�g��
	�� = ��]�p
	�Ƃ��āA

	v' = v*cos�� + n*Dot(n, v)*(1.0f-cos��) - Cross(v, n)*sin��

	�A���ADot �͓��� Cross �͊O�ςƂ���
 */

	float s = sinf( RAD(rot) );
	float c = cosf( RAD(rot) );

	Vec3		axis, v;

	Vec3Normalize( axis, Vaxis );
	Vec3Cross( v, axis, Vin );
	Vout = Vin*c + axis*Vec3Dot( axis, Vin )*(1.0f - c) - v*s; 

	return Vout;
}


//--------------------------------------------------------------
//! @brief �G���~�[�g���
//! @param	Vout	�o��
//! @param	Vin1	�x�N�g���P
//! @param	Vtan1	pVin1�̐ڐ��x�N�g��
//! @param	Vin2	�x�N�g���Q
//! @param	Vtan2	pVin2�̐ڐ��x�N�g��
//! @param	t		�����l
//--------------------------------------------------------------
Vec3 &Vec3Hermite( Vec3 &Vout, const Vec3 &Vin1, const Vec3 &Vtan1,
						const Vec3 &Vin2, const Vec3 &Vtan2, float t )
{
	Vec3 vA, vB;
	float t2 = t*t;

	vA = 2.0f *( Vin1 - Vin2 ) + Vtan1 + Vtan2;
	vB = 3.0f *( Vin2 - Vin1 ) - Vtan1*2.0f - Vtan2;
	Vout = vA*(t2*t) + vB*t2 + Vtan1*t + Vin1;

	return Vout;
}





//===============================================================================//
// 4*4�s��
//===============================================================================//

/********************************************************************/
// ���\�b�h
/********************************************************************/


//--------------------------------------------------------------
//! @brief �Z�b�g
//--------------------------------------------------------------
Mtx &Mtx::Set( const Quat &Q )
{
	float x = Q.v.x *Q.v.x;
	float y = Q.v.y *Q.v.y;
	float z = Q.v.z *Q.v.z; 

	m_m[e11] = 1.0f - 2.0f *(y + z);
	m_m[e22] = 1.0f - 2.0f *(x + z);
	m_m[e33] = 1.0f - 2.0f *(x + y);

	x = Q.v.x *Q.v.y;
	z = Q.v.z *Q.w;

	m_m[e21] = 2.0f *(x - z);
	m_m[e12] = 2.0f *(x + z);

	x = Q.v.x *Q.v.z;
	y = Q.v.y *Q.w;

	m_m[e31] = 2.0f *(x + y);
	m_m[e13] = 2.0f *(x - y);

	x = Q.v.x *Q.w;
	y = Q.v.y *Q.v.z;

	m_m[e32] = 2.0f *(y - x);
	m_m[e23] = 2.0f *(y + x);

	m_m[e14] = m_m[e24] = m_m[e34] =
	m_m[e41] = m_m[e42] = m_m[e43] = 0;
	m_m[e44] = 1.0f;
	
	return *this;
}


//------------------------------------------------------------------//
//! @brief D3DX�݊�����
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�֐��ϊ� 
//--------------------------------------------------------------
D3DXQUATERNION &Mtx::toD3DQUAT( D3DXQUATERNION &Q ) const 
{
	Q = Quat( *this );
	return Q;
}


Mtx::operator D3DXQUATERNION () const
{
	return Quat( *this );
}



// D3DX�^�Ƃ̌݊�
Mtx &Mtx::operator = ( const D3DXQUATERNION &q )
{
	return Set( Quat( q ) );
}




//------------------------------------------------------------------//
// �e�퉉�Z�q
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�s�񓯎m�̏�Z 
//--------------------------------------------------------------

// �W�����Z
Mtx Mtx::operator *( const Mtx &M ) const
{
	float temp[16];
	int   i1, i2;

	for( char i=0; i<16; i++ )
	{
		i1 = i & 3;
		i2 = (i >> 2) << 2;
		temp[i] = this->m_m[i1]   *M.m_m[i2]   + this->m_m[i1+4]  *M.m_m[i2+1] +
			      this->m_m[i1+8] *M.m_m[i2+2] + this->m_m[i1+12] *M.m_m[i2+3];
	}
	return Mtx( temp );
}


// ����^
Mtx &Mtx::operator *= ( const Mtx &M )
{
	float m[16];
	int   i1, i2;

	for( char i=0; i<16; i++ )
	{
		i1 = i & 3;
		i2 = (i>>2) << 2;
		m[i] = m_m[i1]   *M.m_m[i2]   + m_m[i1+4]  *M.m_m[i2+1] +
			   m_m[i1+8] *M.m_m[i2+2] + m_m[i1+12] *M.m_m[i2+3];
	}

	return Set( m );
}



//------------------------------------------------------------------//
// ���̑�
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�s�񎮂����߂�
//--------------------------------------------------------------
float Mtx::Det()		const
{
/*
	����͗]�C�q�W�J�ŋ��߂�
	���R�͈ȉ��ɂ��

	���t���R�X�g�v�Z��
		��Z�񐔂�72��B�������Ɏg�����ɂȂ�Ȃ�

	det = 11*22*33*44 + 11*23*34*42 + 11*24*32*43
		+ 12*21*34*43 + 12*23*31*44 + 12*24*33*41
		+ 13*21*32*44 + 13*22*34*41 + 13*24*31*42
		+ 14*21*33*42 + 14*22*31*43 + 14*23*32*41
		- 11*22*34*43 - 11*23*32*44 - 11*24*33*42
		- 12*21*33*44 - 12*23*34*41 - 12*24*31*43
		- 13*21*34*42 - 13*22*31*44 - 13*24*32*41
		- 14*21*32*43 - 14*22*33*41 - 14*23*31*42

	�����������ɂ��A��Z�񐔂�28��ɗ}������
	
	= 11*( 22*(33*44-34*43) - 23*(32*44-34*42) + 24*(32*43-33*42) )
	+ 12*(-21*(33*44-34*43) + 23*(31*44-34*41) - 24*(31*43-33*41) )
	+ 13*( 21*(32*44-34*42) - 22*(31*44-34*41) + 24*(31*42-32*41) )
	+ 14*(-21*(32*43-33*42) + 22*(31*43-33*41) - 23*(31*42-32*41) )

	LU�������ċ��߂�ꍇ�ALU��������20��̏揜�Z���K�v�ɂȂ�
	���Z���v�Z�R�X�g�̒Ⴂ��Z�ɒu���������23��ɂȂ�A
	���̌�A�s�񎮂����߂�ߒ���26��ɂȂ�
	�s�{�b�g���삪���邱�Ƃ��l�������ꍇ�A���x�I�D�ʐ��͂��Ȃ�����ł���
*/
	float _33x44_34x43	= m_m[e33]*m_m[e44] - m_m[e34]*m_m[e43];
	float _23x44_24x43	= m_m[e23]*m_m[e44] - m_m[e24]*m_m[e43];
	float _23x34_24x33	= m_m[e23]*m_m[e34] - m_m[e24]*m_m[e33];
	float _13x44_14x43	= m_m[e13]*m_m[e44] - m_m[e14]*m_m[e43];
	float _13x34_14x33	= m_m[e13]*m_m[e34] - m_m[e14]*m_m[e33];
	float _13x24_14x23	= m_m[e13]*m_m[e24] - m_m[e14]*m_m[e23];

	return   m_m[e11] *( m_m[e22]*_33x44_34x43 - m_m[e32]*_23x44_24x43 + m_m[e42]*_23x34_24x33 )
		   - m_m[e21] *( m_m[e12]*_33x44_34x43 - m_m[e32]*_13x44_14x43 + m_m[e42]*_13x34_14x33 )
		   + m_m[e31] *( m_m[e12]*_23x44_24x43 - m_m[e22]*_13x44_14x43 + m_m[e42]*_13x24_14x23 )
		   - m_m[e41] *( m_m[e12]*_23x34_24x33 - m_m[e22]*_13x34_14x33 + m_m[e32]*_13x24_14x23 );
}


//------------------------------------------------------------------//
// �e��ϊ��֐��쐬
//------------------------------------------------------------------//

//------------------------------------------------------------------//
//! @brief	�w����W���SX����]�s��쐬
//------------------------------------------------------------------//
Mtx &Mtx::RotationXPivot( float x, float y, float z, float rad )
{
	float cosr = cosf( RAD(rad) );
	float sinr = sinf( RAD(rad) );

	Identity();
	m_m[e22] = m_m[e33] = cosr;
	m_m[e32] = sinr;
	m_m[e23] = -m_m[e32];
	m_m[e24] = -y*cosr + x*sinr + y;
	m_m[e34] = -y*sinr - z*cosr + z;

	return *this;
}

//------------------------------------------------------------------//
//! @brief	�w����W���SY����]�s��쐬
//------------------------------------------------------------------//
Mtx &Mtx::RotationYPivot( float x, float y, float z, float rad )
{
	float cosr = cosf( RAD(rad) );
	float sinr = sinf( RAD(rad) );

	Identity();
	m_m[e11] = m_m[e33] = cosf( RAD(rad) );
	m_m[e13] = sinf( RAD(rad) );
	m_m[e31] = -m_m[e13];
	m_m[e14] = -x*cosr - z*sinr + x;
	m_m[e34] =  x*sinr - z*cosr + z;

	return *this;
}

//------------------------------------------------------------------//
//! @brief	�w����W���SZ����]�s��쐬
//------------------------------------------------------------------//
Mtx &Mtx::RotationZPivot( float x, float y, float z, float rad )
{
	float cosr = cosf( RAD(rad) );
	float sinr = sinf( RAD(rad) );

	Identity();
	m_m[e11] = m_m[e22] = cosf( RAD(rad) );
	m_m[e21] = sinf( RAD(rad) );
	m_m[e12] = -m_m[e21];
	m_m[e14] = -x*cosr + y*sinr + x;
	m_m[e24] = -x*sinr - y*cosr + y;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	�C�ӎ����S�ŉ�]����s����쐬
//------------------------------------------------------------------//
Mtx &Mtx::RotationAxis( const Vec3 &arg_axis, float rad )
{
/*
	x*x*(1-cos)+cos		x*y*(1-cos)-z*sin	z*x*(1-cos)+y*sin	0
	x*y*(1-cos)+z*sin	y*y*(1-cos)+cos		z*y*(1-cos)-x*sin	0
	z*x*(1-cos)-y*sin	y*z*(1-cos)+x*sin	z*z*(1-cos)+cos		0
			0					0					0			1
 */
	Vec3 axis = arg_axis;
	float sinr = sinf( RAD(rad) );
	float cosr = cosf( RAD(rad) );
	float cInv = 1.0f - cosr;
	float temp;
	axis.Normalize();

	m_m[e11] = axis.x*axis.x*cInv + cosr;
	m_m[e22] = axis.y*axis.y*cInv + cosr;
	m_m[e33] = axis.z*axis.z*cInv + cosr;
	m_m[e12] = m_m[e21] = axis.x*axis.y*cInv;
	temp = axis.z*sinr;	m_m[e12] -= temp;	m_m[e21] += temp;
	m_m[e13] = m_m[e31] = axis.z*axis.x*cInv;
	temp = axis.y*sinr;	m_m[e13] += temp;	m_m[e31] -= temp;
	m_m[e23] = m_m[e32] = axis.y*axis.z*cInv;
	temp = axis.x*sinr;	m_m[e23] -= temp;	m_m[e32] += temp;

	m_m[e14] = m_m[e24] = m_m[e34] =
	m_m[e41] = m_m[e42] = m_m[e43] = 0;
	m_m[e44] = 1.0f;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	���[�s�b�`���[����]����s����쐬
//! @brief	���A���ۂ̌v�Z�����͍ł��悭�g���� Roll Pitch Yaw 
//! @brief	�̏��ōs����(D3DXMatrixRotationYawPitchRoll�֐��Ɠ���)
//------------------------------------------------------------------//
Mtx &Mtx::RotationYPR( float pitch, float yaw, float roll )
{
/*
	pitch = ��, yaw = ��, roll = ��
	cos��cos��	cos��sin��sin��-sin��cos��	cos��sin��cos��+sin��sin��	0
	sin��cos��	sin��sin��sin��+cos��cos��	sin��sin��cos��-cos��sin��	0
	  -sin��			cos��sin��					cos��cos��			0
		0					0							0				1
 */
	float	sPhai	= sinf( RAD(roll) );
	float	cPhai	= cosf( RAD(roll) );
	float	sTheta	= sinf( RAD(pitch) );
	float	cTheta	= cosf( RAD(pitch) );
	float	sPsi	= sinf( RAD(yaw) );
	float	cPsi	= cosf( RAD(yaw) );
	float	temp1	= cPhai*sTheta;
	float	temp2	= sPhai*sTheta;

	m_m[e11] = cPhai*cTheta;	m_m[e12] = temp1*sPsi - sPhai*cPsi;		m_m[e13] = temp1*cPsi + sPhai*sPsi;
	m_m[e21] = sPhai*cTheta;	m_m[e22] = temp2*sPsi + cPhai*cPsi;		m_m[e23] = temp2*cPsi - cPhai*sPsi;
	m_m[e31] = -sTheta;			m_m[e32] = cTheta*sPsi;					m_m[e33] = cTheta*cPsi;
	m_m[e14] = m_m[e24] = m_m[e34] = m_m[41] = m_m[e42] = m_m[e43] = 0;	m_m[e44] = 1;

	return *this;
}


//------------------------------------------------------------------//
//! @brief	��]�����̎擾
//! @brief	0�ȉ��̃X�P�[�����|�����Ă���v�f������Ə�肭�����Ȃ��̂Œ���
//------------------------------------------------------------------//
CQuaternion &Mtx::GetRotation( CQuaternion &rot ) const
{
	Vec3 scl;

	GetScale( scl );

	// �X�P�[���t���̎Z�o
	for( char i=0; i < 3; i++ )
	{
		if( !IsZero(scl[i]) )	scl[i] = 1.0f / scl[i];
	}

	float _11 = m_m[e11]*scl.x;
	float _22 = m_m[e22]*scl.y;
	float _33 = m_m[e33]*scl.z;
	float trace = _11 + _22 + _33 + m_m[e44];

	if( trace >= 1.0f )
	{
		trace = sqrtf( trace );
		float divTr = 1.0f / (2 * trace);

		rot.v.x = ( m_m[e23]*scl.z - m_m[e32]*scl.y ) * divTr; 
		rot.v.y = ( m_m[e31]*scl.x - m_m[e13]*scl.z ) * divTr; 
		rot.v.z = ( m_m[e12]*scl.y - m_m[e21]*scl.x ) * divTr; 
		rot.w   = trace * 0.5f;
	}

	else
	{
		if( (_11 >= _22) && (_11 >= _33) )
		{
			rot.v.x = sqrtf( _11 - _22 - _33 +1 ) * 0.5f;
			
			float vi = 1.0f / (rot.v.x * 4);
			rot.v.y = ( m_m[e12]*scl.y + m_m[e21]*scl.x ) * vi;
			rot.v.z = ( m_m[e13]*scl.z + m_m[e31]*scl.x ) * vi;
			rot.w   = ( m_m[e23]*scl.z + m_m[e32]*scl.y ) * vi;
		}
		else if( (_22 >= _11) && (_22 >= _33) )
		{
			rot.v.y = sqrtf( _22 - _11 - _33 +1 ) * 0.5f;
			
			float vi = 1.0f / (rot.v.y * 4);
			rot.v.x = ( m_m[e23]*scl.z + m_m[e32]*scl.y ) * vi;
			rot.v.z = ( m_m[e21]*scl.x + m_m[e12]*scl.y ) * vi;
			rot.w   = ( m_m[e31]*scl.x + m_m[e13]*scl.z ) * vi;
		}
		else
		{
			rot.v.z = sqrtf( _33 - _11 - _22 +1 ) * 0.5f;
			
			float vi = 1.0f / (rot.v.z * 4);
			rot.v.x = ( m_m[e31]*scl.x + m_m[e13]*scl.z ) * vi;
			rot.v.y = ( m_m[e32]*scl.y + m_m[e23]*scl.z ) * vi;
			rot.w   = ( m_m[e12]*scl.y + m_m[e21]*scl.x ) * vi;
		}
	}
	return rot;
}


//--------------------------------------------------------------
//! @brief	�g�����X�t�H�[������
//--------------------------------------------------------------
void Mtx::Decompose( Vec3 &scl, CQuaternion &rot, Vec3 &trs )	const
{
	GetTranslate( trs );
	GetRotation( rot );
	GetScale( scl );
}


/********************************************************************/
// �N���X�O�֐�
/********************************************************************/

//------------------------------------------------------------------//
// ���Z�֐�
//------------------------------------------------------------------//

//--------------------------------------------------------------
// �s�񓯎m�̏�Z
// pO = pI*pI2
//--------------------------------------------------------------
Mtx &MtxMul( Mtx &Out, const Mtx &In, const Mtx &In2)
{
	float m[16];
	int i1, i2;

	for( char i=0; i<16; i++ )
	{
		i1 = i & 3;
		i2 = (i>>2) << 2;
		m[i] = In[i1]   *In2[i2]   + In[i1+4]  *In2[i2+1] +
			   In[i1+8] *In2[i2+2] + In[i1+12] *In2[i2+3];
	}
		
	return Out.Set( m );
}



//------------------------------------------------------------------//
// ��]�s��v�Z
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�e���𒆐S�Ɂu����*��]�s��v�ŉ�]
//!	@brief	pM = pM *�e���𒆐S�Ƃ����p�xr�̉�]�s��
//--------------------------------------------------------------

// X�����S
Mtx &MtxMulRotationX( Mtx &M, float r )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _12 =  cosr*M[ e12 ] + sinr*M[ e13 ];
	float _22 =  cosr*M[ e22 ] + sinr*M[ e23 ];
	float _32 =  cosr*M[ e32 ] + sinr*M[ e33 ];
	float _13 = -sinr*M[ e12 ] + cosr*M[ e13 ];
	float _23 = -sinr*M[ e22 ] + cosr*M[ e23 ];
	float _33 = -sinr*M[ e32 ] + cosr*M[ e33 ];

	M.SetVal( e12, _12 );		M.SetVal( e13, _13 );
	M.SetVal( e22, _22 );		M.SetVal( e23, _23 );
	M.SetVal( e32, _32 );		M.SetVal( e33, _33 );

	return M;
}


// Y�����S
Mtx &MtxMulRotationY( Mtx &M, float r )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11 =  cosr*M[ e11 ] - sinr*M[ e13 ];
	float _21 =  cosr*M[ e21 ] - sinr*M[ e23 ];
	float _31 =  cosr*M[ e31 ] - sinr*M[ e33 ];
	float _13 =  sinr*M[ e11 ] + cosr*M[ e13 ];
	float _23 =  sinr*M[ e21 ] + cosr*M[ e23 ];
	float _33 =  sinr*M[ e31 ] + cosr*M[ e33 ];

	M.SetVal( e11, _11 );	M.SetVal( e13, _13 );
	M.SetVal( e21, _21 );	M.SetVal( e23, _23 );
	M.SetVal( e31, _31 );	M.SetVal( e33, _33 );

	return M;
}


// Z�����S
Mtx &MtxMulRotationZ( Mtx &M, float r )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11 =  cosr*M[ e11 ] + sinr*M[ e12 ];
	float _21 =  cosr*M[ e21 ] + sinr*M[ e22 ];
	float _31 =  cosr*M[ e31 ] + sinr*M[ e32 ];
	float _12 = -sinr*M[ e11 ] + cosr*M[ e12 ];
	float _22 = -sinr*M[ e21 ] + cosr*M[ e22 ];
	float _32 = -sinr*M[ e31 ] + cosr*M[ e32 ];

	M.SetVal( e11, _11 );	M.SetVal( e12, _12 );
	M.SetVal( e21, _21 );	M.SetVal( e22, _22 );
	M.SetVal( e31, _31 );	M.SetVal( e32, _32 );

	return M;
}


//--------------------------------------------------------------
//! @brief	�e���𒆐S�Ɂu��]�s��*�����v�ŉ�]
//!	@brief	pM = �e���𒆐S�Ƃ����p�xr�̉�]�s�� *pM
//--------------------------------------------------------------

// X�����S
Mtx &MtxMulRotationX( float r, Mtx &M )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _21 =  cosr*M[ e21 ] - sinr*M[ e31 ];
	float _22 =  cosr*M[ e22 ] - sinr*M[ e32 ];
	float _23 =  cosr*M[ e23 ] - sinr*M[ e33 ];
	float _24 =  cosr*M[ e24 ] - sinr*M[ e34 ];
	float _31 =  sinr*M[ e21 ] + cosr*M[ e31 ];
	float _32 =  sinr*M[ e22 ] + cosr*M[ e32 ];
	float _33 =  sinr*M[ e23 ] + cosr*M[ e33 ];
	float _34 =  sinr*M[ e24 ] + cosr*M[ e34 ];

	M.SetVal( e21, _21 );		M.SetVal( e22, _22 );
	M.SetVal( e23, _23 );		M.SetVal( e24, _24 );
	M.SetVal( e31, _31 );		M.SetVal( e32, _32 );
	M.SetVal( e33, _33 );		M.SetVal( e34, _34 );

	return M;
}


// Y�����S
Mtx &MtxMulRotationY( float r, Mtx &M )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11 =  cosr*M[ e11 ] + sinr*M[ e31 ];
	float _12 =  cosr*M[ e12 ] + sinr*M[ e32 ];
	float _13 =  cosr*M[ e13 ] + sinr*M[ e33 ];
	float _14 =  cosr*M[ e14 ] + sinr*M[ e34 ];
	float _31 = -sinr*M[ e11 ] + cosr*M[ e31 ];
	float _32 = -sinr*M[ e12 ] + cosr*M[ e32 ];
	float _33 = -sinr*M[ e13 ] + cosr*M[ e33 ];
	float _34 = -sinr*M[ e14 ] + cosr*M[ e34 ];

	M.SetVal( e11, _11 );	M.SetVal( e12, _12 );
	M.SetVal( e13, _13 );	M.SetVal( e14, _14 );
	M.SetVal( e31, _31 );	M.SetVal( e32, _32 );
	M.SetVal( e33, _33 );	M.SetVal( e34, _34 );

	return M;
}


// Z�����S
Mtx &MtxMulRotationZ( float r, Mtx &M )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11 =  cosr*M[ e11 ] - sinr*M[ e21 ];
	float _12 =  cosr*M[ e12 ] - sinr*M[ e22 ];
	float _13 =  cosr*M[ e13 ] - sinr*M[ e23 ];
	float _14 =  cosr*M[ e14 ] - sinr*M[ e24 ];
	float _21 =  sinr*M[ e11 ] + cosr*M[ e21 ];
	float _22 =  sinr*M[ e12 ] + cosr*M[ e22 ];
	float _23 =  sinr*M[ e13 ] + cosr*M[ e23 ];
	float _24 =  sinr*M[ e14 ] + cosr*M[ e24 ];

	M.SetVal( e11, _11 );	M.SetVal( e12, _12 );
	M.SetVal( e13, _13 );	M.SetVal( e14, _14 );
	M.SetVal( e21, _21 );	M.SetVal( e22, _22 );
	M.SetVal( e23, _23 );	M.SetVal( e24, _24 );

	return M;
}



//------------------------------------------------------------------//
// �w����W�𒆐S�Ƃ�����]�s��Ɗ|����
//------------------------------------------------------------------//

//--------------------------------------------------------------
//! @brief	�w����W�ʒu�ł̊e�����S��]*�����s����v�Z
//!	@brief	M = M *(x, y, z)�𒆐S�Ƃ����p�xr�̉�]�s��
//--------------------------------------------------------------

// X����]
Mtx &MtxMulRotationX( Mtx &M, float r, float y, float z )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _12, _13, _14, _22, _23, _24, _32, _33, _34;
	float _t24, _t34; 

	_t24 = -y*cosr + z*sinr + y;
	_t34 = -y*sinr - z*cosr + z;

	_12 =  cosr*M[ e12 ] + sinr*M[ e13 ];
	_22 =  cosr*M[ e22 ] + sinr*M[ e23 ];
	_32 =  cosr*M[ e32 ] + sinr*M[ e33 ];
	_13 = -sinr*M[ e12 ] + cosr*M[ e13 ];
	_23 = -sinr*M[ e22 ] + cosr*M[ e23 ];
	_33 = -sinr*M[ e32 ] + cosr*M[ e33 ];
	_14 =  _t24*M[ e12 ] + _t34*M[ e13 ] + M[ e14 ];
	_24 =  _t24*M[ e22 ] + _t34*M[ e23 ] + M[ e24 ];
	_34 =  _t24*M[ e32 ] + _t34*M[ e33 ] + M[ e34 ];
	
	M.SetVal( e12, _12 );		M.SetVal( e13, _13 );
	M.SetVal( e14, _14 );		M.SetVal( e22, _22 );
	M.SetVal( e23, _23 );		M.SetVal( e24, _24 );
	M.SetVal( e32, _32 );		M.SetVal( e33, _33 );
	M.SetVal( e34, _34 );

	return M;
}


// Y����]
Mtx &MtxMulRotationY( Mtx &M, float r, float x, float z )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11, _13, _14, _21, _23, _24, _31, _33, _34;
	float _t14, _t34; 

	_t14 = -x*cosr - z*sinr + x;
	_t34 =  x*sinr - z*cosr + z;

	_11 =  cosr*M[ e11 ] - sinr*M[ e13 ];
	_21 =  cosr*M[ e21 ] - sinr*M[ e23 ];
	_31 =  cosr*M[ e31 ] - sinr*M[ e33 ];
	_13 =  sinr*M[ e11 ] + cosr*M[ e13 ];
	_23 =  sinr*M[ e21 ] + cosr*M[ e23 ];
	_33 =  sinr*M[ e31 ] + cosr*M[ e33 ];
	_14 =  _t14*M[ e11 ] + _t34*M[ e13 ] + M[ e14 ];
	_24 =  _t14*M[ e21 ] + _t34*M[ e23 ] + M[ e24 ];
	_34 =  _t14*M[ e31 ] + _t34*M[ e33 ] + M[ e34 ];
	
	M.SetVal( e11, _11 );		M.SetVal( e13, _13 );
	M.SetVal( e14, _14 );		M.SetVal( e21, _21 );
	M.SetVal( e23, _23 );		M.SetVal( e24, _24 );
	M.SetVal( e31, _31 );		M.SetVal( e33, _33 );
	M.SetVal( e34, _34 );

	return M;
}


// Z����]
Mtx &MtxMulRotationZ( Mtx &M, float r, float x, float y )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11, _12, _14, _21, _22, _24, _31, _32, _34;
	float _t14, _t24; 

	_t14 = -x*cosr + y*sinr + x;
	_t24 = -x*sinr - y*cosr + y;

	_11 =  cosr*M[ e11 ] + sinr*M[ e12 ];
	_21 =  cosr*M[ e21 ] + sinr*M[ e22 ];
	_31 =  cosr*M[ e31 ] + sinr*M[ e32 ];
	_12 = -sinr*M[ e11 ] + cosr*M[ e12 ];
	_22 = -sinr*M[ e21 ] + cosr*M[ e22 ];
	_32 = -sinr*M[ e31 ] + cosr*M[ e32 ];
	_14 =  _t14*M[ e11 ] + _t24*M[ e12 ] + M[ e14 ];
	_24 =  _t14*M[ e21 ] + _t24*M[ e22 ] + M[ e24 ];
	_34 =  _t14*M[ e31 ] + _t24*M[ e32 ] + M[ e34 ];
	
	M.SetVal( e11, _11 );		M.SetVal( e12, _12 );
	M.SetVal( e14, _14 );		M.SetVal( e21, _21 );
	M.SetVal( e22, _22 );		M.SetVal( e24, _24 );
	M.SetVal( e31, _31 );		M.SetVal( e32, _32 );
	M.SetVal( e34, _34 );

	return M;
}


//--------------------------------------------------------------
//! @brief	�����s��*�w����W�ʒu�ł̊e�����S��]���v�Z
//!	@brief	M = (x, y, z)�𒆐S�Ƃ����p�xr�̉�]�s�� *M 
//--------------------------------------------------------------

// X����]
Mtx &MtxMulRotationX( float r, float y, float z, Mtx &M )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _21, _22, _23, _24, _31, _32, _33, _34;
	float _t24, _t34;

	_t24 = -y*cosr + z*sinr + y;
	_t34 = -y*sinr - z*cosr + z;

	_21 =  cosr*M[ e21 ] - sinr*M[ e31 ] + _t24*M[ e41 ];
	_22 =  cosr*M[ e22 ] - sinr*M[ e32 ] + _t24*M[ e42 ];
	_23 =  cosr*M[ e23 ] - sinr*M[ e33 ] + _t24*M[ e43 ];
	_24 =  cosr*M[ e24 ] - sinr*M[ e34 ] + _t24*M[ e44 ];
	_31 =  sinr*M[ e21 ] + cosr*M[ e31 ] + _t34*M[ e41 ];
	_32 =  sinr*M[ e22 ] + cosr*M[ e32 ] + _t34*M[ e42 ];
	_33 =  sinr*M[ e23 ] + cosr*M[ e33 ] + _t34*M[ e43 ];
	_34 =  sinr*M[ e24 ] + cosr*M[ e34 ] + _t34*M[ e44 ];
	
	M.SetVal( e21, _21 );		M.SetVal( e22, _22 );
	M.SetVal( e23, _23 );		M.SetVal( e24, _24 );
	M.SetVal( e31, _31 );		M.SetVal( e32, _32 );
	M.SetVal( e33, _33 );		M.SetVal( e34, _34 );

	return M;	
}


// Y����]
Mtx &MtxMulRotationY( float r, float x, float z, Mtx &M )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11, _12, _13, _14, _31, _32, _33, _34;
	float _t14, _t34; 

	_t14 = -x*cosr - z*sinr + x;
	_t34 =  x*sinr - z*cosr + z;

	_11 =  cosr*M[ e11 ] + sinr*M[ e31 ] + _t14*M[ e41 ];
	_12 =  cosr*M[ e12 ] + sinr*M[ e32 ] + _t14*M[ e42 ];
	_13 =  cosr*M[ e13 ] + sinr*M[ e33 ] + _t14*M[ e43 ];
	_14 =  cosr*M[ e14 ] + sinr*M[ e34 ] + _t14*M[ e44 ];
	_31 = -sinr*M[ e11 ] + cosr*M[ e31 ] + _t34*M[ e41 ];
	_32 = -sinr*M[ e12 ] + cosr*M[ e32 ] + _t34*M[ e42 ];
	_33 = -sinr*M[ e13 ] + cosr*M[ e33 ] + _t34*M[ e43 ];
	_34 = -sinr*M[ e14 ] + cosr*M[ e34 ] + _t34*M[ e44 ];
	
	M.SetVal( e11, _11 );		M.SetVal( e12, _12 );
	M.SetVal( e13, _13 );		M.SetVal( e14, _14 );
	M.SetVal( e31, _31 );		M.SetVal( e32, _32 );
	M.SetVal( e33, _33 );		M.SetVal( e34, _34 );

	return M;
}


// Z����]
Mtx &MtxMulRotationZ( float r, float x, float y, Mtx &M )
{
	float sinr = sinf( RAD(r) );
	float cosr = cosf( RAD(r) );
	float _11, _12, _13, _14, _21, _22, _23, _24;
	float _t14, _t24; 

	_t14 = -x*cosr + y*sinr + x;
	_t24 = -x*sinr - y*cosr + y;

	_11 =  cosr*M[ e11 ] - sinr*M[ e21 ] + _t14*M[ e41 ];
	_12 =  cosr*M[ e12 ] - sinr*M[ e22 ] + _t14*M[ e42 ];
	_13 =  cosr*M[ e13 ] - sinr*M[ e23 ] + _t14*M[ e43 ];
	_14 =  cosr*M[ e14 ] - sinr*M[ e24 ] + _t14*M[ e44 ];
	_21 =  sinr*M[ e11 ] + cosr*M[ e21 ] + _t24*M[ e41 ];
	_22 =  sinr*M[ e12 ] + cosr*M[ e22 ] + _t24*M[ e42 ];
	_23 =  sinr*M[ e13 ] + cosr*M[ e23 ] + _t24*M[ e43 ];
	_24 =  sinr*M[ e14 ] + cosr*M[ e24 ] + _t24*M[ e44 ];
	
	M.SetVal( e11, _11 );		M.SetVal( e12, _12 );
	M.SetVal( e13, _13 );		M.SetVal( e14, _14 );
	M.SetVal( e21, _21 );		M.SetVal( e22, _22 );
	M.SetVal( e23, _23 );		M.SetVal( e24, _24 );

	return M;
}



//----------------------------------------------------------
// �s���p���Ăw�x�y���ŉ�]
//----------------------------------------------------------

// ����*��]�s��
Mtx &MtxRotationXYZ( Mtx &M, const Vec3 &V, eMtxRotType rType )
{
	// �E����|���Ă��������̂��߁A�w�菇�Ƌt�Ɋ|���Ă���
	switch( rType )
	{
	case kXYZ:
		{
			MtxMulRotationZ( M, V.z );
			MtxMulRotationY( M, V.y );
			MtxMulRotationX( M, V.x );
		}
		break;

	case kXZY:
		{
			MtxMulRotationY( M, V.z );
			MtxMulRotationZ( M, V.y );
			MtxMulRotationX( M, V.x );
		}
		break;

	case kYXZ:
		{
			MtxMulRotationZ( M, V.z );
			MtxMulRotationX( M, V.y );
			MtxMulRotationY( M, V.x );
		}
		break;

	case kYZX:
		{
			MtxMulRotationX( M, V.x );
			MtxMulRotationZ( M, V.y );
			MtxMulRotationY( M, V.z );
		}
		break;

	case kZXY:
		{
			MtxMulRotationY( M, V.z );
			MtxMulRotationX( M, V.x );
			MtxMulRotationZ( M, V.y );
		}
		break;

	case kZYX:
		{
			MtxMulRotationX( M, V.x );
			MtxMulRotationY( M, V.z );
			MtxMulRotationZ( M, V.y );
		}
		break;
	}

	return M;
}


// ��]�s��*����
Mtx &MtxRotationXYZ( const Vec3 &V, Mtx &M, eMtxRotType rType )
{
	switch( rType )
	{
	case kXYZ:
		{
			MtxMulRotationX( V.x, M );
			MtxMulRotationY( V.y, M );
			MtxMulRotationZ( V.z, M );
		}
		break;

	case kXZY:
		{
			MtxMulRotationX( V.x, M );
			MtxMulRotationZ( V.z, M );
			MtxMulRotationY( V.y, M );
		}
		break;

	case kYXZ:
		{
			MtxMulRotationY( V.y, M );
			MtxMulRotationX( V.x, M );
			MtxMulRotationZ( V.z, M );
		}
		break;

	case kYZX:
		{
			MtxMulRotationY( V.y, M );
			MtxMulRotationZ( V.z, M );
			MtxMulRotationX( V.x, M );
		}
		break;

	case kZXY:
		{
			MtxMulRotationZ( V.z, M );
			MtxMulRotationX( V.x, M );
			MtxMulRotationY( V.y, M );
		}
		break;
	
	case kZYX:
		{
			MtxMulRotationZ( V.z, M );
			MtxMulRotationY( V.y, M );
			MtxMulRotationX( V.x, M );
		}
		break;
	}
	return M;
}


//----------------------------------------------------------
// ���s�ړ�
//----------------------------------------------------------

//--------------------------------------------------------------
//! @brief	���s�ړ��s��*�����s��
//! @brief	M = �ړ���(x, y, z)�̍s�� *M
//--------------------------------------------------------------
Mtx &MtxMulTranslate( float x, float y, float z, Mtx &Mo )
{
	Mo.m_m[e11] += Mo.m_m[e41]*x;	Mo.m_m[e12] += Mo.m_m[e42]*x;	
	Mo.m_m[e13] += Mo.m_m[e43]*x;	Mo.m_m[e14] += Mo.m_m[e44]*x;
	Mo.m_m[e21] += Mo.m_m[e41]*y;	Mo.m_m[e22] += Mo.m_m[e42]*y;	
	Mo.m_m[e23] += Mo.m_m[e43]*y;	Mo.m_m[e24] += Mo.m_m[e44]*y;
	Mo.m_m[e31] += Mo.m_m[e41]*z;	Mo.m_m[e32] += Mo.m_m[e42]*z;	
	Mo.m_m[e33] += Mo.m_m[e43]*z;	Mo.m_m[e34] += Mo.m_m[e44]*z;
	return Mo;
}



//----------------------------------------------------------
// �X�P�[�����O
//----------------------------------------------------------

//--------------------------------------------------------------
//! @brief	�X�P�[�����O�s��*�����s��
//! @brief	M = pos���Sscl�{�̍s�� *M
//--------------------------------------------------------------
Mtx &MtxMulScalingPivot( const Vec3 &scl, const Vec3 &pos, Mtx &Mo )
{
	float xt = pos.x * (1 - scl.x);
	float yt = pos.y * (1 - scl.y);
	float zt = pos.z * (1 - scl.z);

	Mo.SetVal( e11, Mo[e11]*scl.x + xt*Mo[e41] );
	Mo.SetVal( e12, Mo[e12]*scl.x + xt*Mo[e42] );
	Mo.SetVal( e13, Mo[e13]*scl.x + xt*Mo[e43] );
	Mo.SetVal( e14, Mo[e14]*scl.x + xt*Mo[e44] );
	Mo.SetVal( e21, Mo[e21]*scl.y + yt*Mo[e41] );
	Mo.SetVal( e22, Mo[e22]*scl.y + yt*Mo[e42] );
	Mo.SetVal( e23, Mo[e23]*scl.y + yt*Mo[e43] );
	Mo.SetVal( e24, Mo[e24]*scl.y + yt*Mo[e44] );
	Mo.SetVal( e31, Mo[e31]*scl.z + zt*Mo[e41] );
	Mo.SetVal( e32, Mo[e32]*scl.z + zt*Mo[e42] );
	Mo.SetVal( e33, Mo[e33]*scl.z + zt*Mo[e43] );
	Mo.SetVal( e34, Mo[e34]*scl.z + zt*Mo[e44] );

	return Mo;
}


//----------------------------------------------------------
//! @brief	�t�s��
//! @param	Mo		�t�s��
//! @param	pMi		���s��
//! @param	pDet	�s�񎮁i�o�͗p�j
//----------------------------------------------------------
Mtx &MtxInverse( Mtx &Mo, const Mtx &Mi, float *pDet )
{
/*
	�s�� A �̋t�s�� AI �����߂�ɂ͐���ނ̕��@�����邪�A
	����� LU�������g�p����

	A  = L  *U 	�ƂȂ�悤�ɕ��������ꍇ�A
	AI = UI *LI	�ƂȂ�

	���̂Ƃ��A�s�� det �͈ȉ��̂悤�ɂȂ��Ă���

	detA = detL *detU

	L��U�͂Ƃ��ɎO�p�s��ł���A�O�p�s��̍s�񎮂͑Ίp�����̑���ɓ�����
	�܂��A����� L �̑Ίp�������S�ĂP�ɂȂ邽�߁AdetA �͈ȉ��̂悤�ɂȂ�

	detA = detU = detU11*detU22*detU33*detU44
 */

	Mtx		l(false), u(false);
	BYTE	piv[4];
	bool	isPivot;
	
	// LU ����
	isPivot = MtxLUDecomp( l, u, Mi, piv );
	
	// �s��
	if( pDet )
		*pDet = u[e11] *u[e22] *u[e33] *u[e44]; 

	// LU �t�s��
	MtxLUInverse( l, u, l, u );


	Mo = u *l;
	
	// �s�{�b�g�I���̔��f
	if( isPivot )
	{
		for( int i=0; i < 3; i++ )
		{
			if( i != piv[i] )
			{
				// ���Z�������t�ɂȂ��Ă��邽�߁A�s����ւ�.�����ւ��Ƒ��삵�Ė{���̌`�ɖ߂�
				Mo.SwapCol( i, piv[i] );
				Swap( piv[i], piv[ piv[i] ] );
			}
		}
	}

	return Mo;
}


//----------------------------------------------------------
//! @brief	�����s���LU��������
//! @brief	�s�{�b�e�B���O���s��ꂽ�ꍇ�A
//! @brief	�����ɒu�����ꂽ�s�ԍ����i�[�����
//! @param	pMl		L�s��
//!	@param	pMu		U�s��
//! @param	pMsrc	���s��
//! @param	pivot	�s�{�b�e�B���O�̌��ʁA�s�����ǂ��ς���������i�[
//! @rtnval		�s�{�b�e�B���O�������ǂ���
//---------------------------------------------------------
bool MtxLUDecomp( Mtx &Ml, Mtx &Mu, const Mtx &Msrc, BYTE *pivot )
{
/*
	�ȉ��AA = pMsrc, L = pMl, U = pMu �Ƃ���

	A = L *U  �̌`�ɂȂ�悤�ɕ�������
	����͂k�s��̑Ίp�������P�ƒu��

	�s��̉��Z�K�����AL, U �͂��ꂼ��ȉ��̂悤�ɂȂ�

		    1			0					0				  0
	L =  A21/A11		1					0				  0
		 A31/A11 (A32-L31*U12)/U22			1				  0
		 A41/A11 (A42-L41*U12)/U22 (A43-L41*U13-L42*U23)/U33  1

		  A11		A12				 A13					  A14
	U =    0	A22-L21*U12		 A23-L21*U13			  A24-L21*U14
		   0		 0		 A33-L31*U13-L32*U23	  A34-L31*U14-L32*U24
		   0		 0				  0			  A44-L41*U14-L42*U24-L43*U34


	���̌��ʂ���A�ȉ��̈�ʎ����������
				 t-1
	Lit = (Ait - �� (Lti *Ujt)) / Utt		(i > t)
				 j=1

				t-1
	Utj = Atj - �� (Lti *Uij)				(j >= t)
				i=1

	���F0���Z�h�~�̂��߁A�s�{�b�e�B���O�������ʓr�K�{�ƂȂ� 
*/

	Mtx		m( Msrc );
	BYTE	order[4];
	float	temp;
	float	div;
	bool	pivoted;

	Ml.Identity();
	Mu.Identity();

	// �s�{�b�g�I��
	pivoted = MtxPivottingRow( m, m, order );

	// L�P��ځAU�P�s�ڂ͂��ꂼ�꒼�ڑ�����Čv�Z�ʂ����炷
	temp = 1.0f / m[e11];
	Ml.SetCol( 0, 1, m[e21]*temp, m[e31]*temp, m[e41]*temp );
	Mu.SetRow( 0, m[e11], m[e12], m[e13], m[e14] );


	// �Q�s�ځA�Q��ڈȍ~
	for( BYTE col = 1; col < 4; col++ )
	{
		for( BYTE row = 1; row < 4; row++ )
		{
			temp = m.GetVal( row, col );
			for( BYTE t = 0; t < row; t++ )
			{
				temp -= Ml.GetVal( row, t ) * Mu.GetVal( t, col );
			}

			// �t�v�Z
			if( col >= row )
			{
				if( col == row )
				{				
					div = 1.0f / temp;
				}
				Mu.SetVal( row, col, temp );
			}

			// �k�v�Z
			else
			{
				Ml.SetVal( row, col, temp*div );
			}
		}	// for( col ... )
	}	//  for( row... )
	
	if( pivot )
		memcpy( pivot, order, sizeof(BYTE)*4 );
	return pivoted;
}


//----------------------------------------------------------
//! @brief	����LU�s��̋t�s������߂�
//! @param	pMli	L�t�s��
//! @param	pMui	U�t�s��
//! @param	pMl		L�s��
//! @param	pMu		U�s��
//! @rtnval		�t�s��Z�o���ł������ǂ���	
//----------------------------------------------------------
bool MtxLUInverse( Mtx &Mli, Mtx &Mui, const Mtx &Ml, const Mtx &Mu )
{
/*
	�ȉ��AL = pMl, U = pMu, LI = pMli, UI = pMui �Ƃ���

	�s��̉��Z�K�����ALI, UI �͂��ꂼ��ȉ��̂悤�ɂȂ�

		            1					  0			  0			0
	LI =          -L21					  1			  0			0
		     -(L31+L32*LI21)			-L32		  1			0
		 -(L41+L42*LI21+L43*LI31)  -(L42+L43*LI32)	-L43		1

		 1/U11	-(U12*UI22)/U11	-(U12*UI23+U13*UI33)/U11 -(U12*UI24+U13*UI34+U14*UI44)/U11
	UI =   0		1/U22			-(U23*UI33)/U22			  -(U23*UI34+U24*UI44)/U22
		   0		  0					 1/U33					   -(U34*UI44)/U33
		   0		  0						0							1/U44
 

	��̌��ʂ���A�ȉ��̈�ʎ����������

				   i-1
	LIit = -(Lit + �� (Lij *LIjt))			(i > t)
				   j=t+1

			 t
	UIit = -(�� (Uij *UIjt)) / Uii			(i < t)
			j=i+1

	UIit = 1.0 / Uii						(i = t)
	
 */
assert(
	if( IsZero( Mu.GetVal( 0, 0 ) ) ||
		IsZero( Mu.GetVal( 1, 1 ) ) ||
		IsZero( Mu.GetVal( 2, 2 ) ) ||
		IsZero( Mu.GetVal( 3, 3 ) ) )
		return false;
#endif

	Mtx		mL( Ml );
	Mtx		mU( Mu );

	Mli.Identity();
	Mui.Identity();

	// �t�s��Z�o

	// ���[�v�񐔂����炷���߁A�P���ȉӏ����ɌʂŐݒ肷��
	Mli.SetVal( 1, 0, -mL.GetVal( 1, 0 ) );
	Mli.SetVal( 2, 1, -mL.GetVal( 2, 1 ) );
	Mli.SetVal( 3, 2, -mL.GetVal( 3, 2 ) );
	Mui.SetVal( 0, 0, 1.0f/mU.GetVal( 0, 0 ) );
	Mui.SetVal( 1, 1, 1.0f/mU.GetVal( 1, 1 ) );
	Mui.SetVal( 2, 2, 1.0f/mU.GetVal( 2, 2 ) );
	Mui.SetVal( 3, 3, 1.0f/mU.GetVal( 3, 3 ) );

	/*
		��̌��ʂɂ��A�ȉ��̂悤��3x3�ƍl���Čv�Z����
		����ɔ����A��q��ʎ��Ƃ͑����̈ٓ����N�����Ă���
		UI12 UI13 UI14
		LI31 UI23 UI24
		LI41 LI42 UI34
	*/
	for( char col=3; col > 0; col-- )
	{
		for( char row=2; row >= 0; row-- )
		{
			float temp;

			// �tL�Z�o
			if( row >= col )
			{
				// if( col==2 ) row+=1; else if(col==1 && row==1) row+=2;	�̗�
				char	row2 = row + 1*((col>>1) & 1) + (col & 1)*(row & 1)*2;
				char	col2 = col-1;

				temp = mL.GetVal( row2, col2 ); 
				for( char t=col2+1; t < row2; t++ )
				{
					temp += mL.GetVal( row2, t ) *Mli.GetVal( t, col2 );
				}
				Mli.SetVal( row2, col2, -temp ); 
			}

			// �tU�Z�o
			else
			{
				temp = 0;
				for( BYTE t=row+1; t <= col; t++ )
				{
					temp += mU.GetVal( row, t ) *Mui.GetVal( t, col  );
				}
				Mui.SetVal( row, col, -temp*Mui.GetVal( row, row ) );
			}
		}
	}

	return true;
}


//----------------------------------------------------------
//! @brief	�ʑΏ̍s��쐬
//! @param	Mo		�o��
//! @param	pPlane	�ΏۂƂȂ��
//----------------------------------------------------------
Mtx &MtxPlaneReflect( Mtx &Mo, const CPlane &plane )
{
/*
	���� P �� ax + by + cz + d = 0 �̂Ƃ��A
	���̕��ʂɑΏۂɂȂ�悤�ȍs��͈ȉ��̂悤�ɂȂ�
	�A���A�@���͐��K���ς݂Ƃ���
	
	-2*a*a+1	 -2*a*b		 -2*a*c		-2*a*d
	 -2*b*a		-2*b*b+1	 -2*b*c		-2*b*d
	 -2*c*a		 -2*c*b		-2*c*c+1	-2*c*d
		0			0			0		   1
 */
	const Vec3 &pn = plane.m_normal;
	Vec3	v  = plane.m_normal*-2.0f;

	return Mo.Set( v.x*pn.x+1.0f,	v.x*pn.y,		v.x*pn.z,	   v.x*plane.m_d,
					 v.y*pn.x,		v.y*pn.y+1.0f,	v.y*pn.z,	   v.y*plane.m_d,
					 v.z*pn.x,		v.z*pn.y,		v.z*pn.z+1.0f, v.z*plane.m_d,
						0,				0,				0,				1.0f	 );
}




//----------------------------------------------------------
//! @brief	�r���[�s��쐬
//----------------------------------------------------------
Mtx &MtxView( Mtx &Mo, const Vec3 &vEye, const Vec3 &vAt, const Vec3 &vUp )
{
	Vec3 xAxis, yAxis;

	Vec3 zAxis( vEye, vAt );

	Vec3Normalize( zAxis, zAxis );
	Vec3Normalize( xAxis, Vec3Cross( xAxis, vUp, zAxis ) );
	Vec3Cross( yAxis, zAxis, xAxis );

	Mo.Set( xAxis.x, xAxis.y, xAxis.z, -Vec3Dot( xAxis, vEye ),
			yAxis.x, yAxis.y, yAxis.z, -Vec3Dot( yAxis, vEye ),
			zAxis.x, zAxis.y, zAxis.z, -Vec3Dot( zAxis, vEye ),
			.0f,	 .0f,	  .0f,						1.0f  );

	return Mo;
}


//----------------------------------------------------------
//! @brief	�v���W�F�N�V�����s��쐬
//----------------------------------------------------------
Mtx &MtxProjection( Mtx &Mo, float fovY, float aspect, float fNear, float fFar )
{
	float Z  = fFar / (fFar - fNear);
	float w3 = 1;
	float z4 = -Z *fNear;

	float Y = 1.0f / tanf( fovY *0.5f );
	float X = Y / aspect;

	Mo.Identity();
	Mo.SetVal( e11, X );	Mo.SetVal( e22, Y );
	Mo.SetVal( e33, Z );	Mo.SetVal( e44, .0f );
	Mo.SetVal( e34, z4 );	Mo.SetVal( e43, w3 );

	return Mo;
}

//----------------------------------------------------------
// �s�{�b�g�T����Ɗ֐�
//----------------------------------------------------------
BYTE GetAryMax( const float *ary, BYTE num )
{
	BYTE	maxIdx = 0;
	float	maxVal = 0;

	for( BYTE i= 0; i < num; i++ )
	{
		float temp = Abs( ary[i] );
		if( temp > maxVal )
		{
			maxVal = temp;
			maxIdx = i;
		}
	}
	return maxIdx; 
}


//----------------------------------------------------------
//! @brief	�s����s�{�b�g��T��
//! @param	row		�T���s
//! @param	st		�T���J�n�s�v�f
//----------------------------------------------------------
BYTE MtxGetPivotRow( const Mtx &M, BYTE row, BYTE st )
{
	if( st == 3 )
		return 3;

	float	ary[4];

	M.GetRow( ary, row );

	return GetAryMax( &ary[st], 4-st ) + st;
}


//----------------------------------------------------------
//! @brief	�񂩂�s�{�b�g��T��
//! @param	col		�T����
//! @param	st		�T���J�n��v�f
//----------------------------------------------------------
BYTE MtxGetPivotCol( const Mtx &M, BYTE col, BYTE st )
{
	if( st == 3 )
		return 3;

	float	ary[4];

	M.GetCol( ary, col );

	return GetAryMax( &ary[st], 4-st ) + st;
}


//----------------------------------------------------------
//! @brief	�s�s�{�b�e�B���O
//! @param	Mo		�o��
//! @param	pMi		����
//! @param	pivot	�s�{�b�e�B���O��̍s�ԍ�
//! @rtnval		�s�{�b�e�B���O�������ǂ���
//----------------------------------------------------------
bool MtxPivottingRow( Mtx &Mo, const Mtx &Mi, BYTE *pivot )
{
	Mtx		m( Mi );
	bool	pivoted;
	BYTE	order[4] = { 0, 1, 2, 3 };

	for( BYTE i = 0; i < 3; i++ )
	{
		BYTE idx = MtxGetPivotCol( m, i, i );

		if( idx != i )
		{
			pivoted = true;
			Swap( order[i], order[idx] );
			m.SwapRow( i, idx );
		}
	}
	Mo = m;
	if( pivot )
		memcpy( pivot, order, sizeof(BYTE)*4 );

	return pivoted;
}


//----------------------------------------------------------
//! @brief	��s�{�b�e�B���O
//! @param	Mo		�o��
//! @param	pMi		����
//! @param	pivot	�s�{�b�e�B���O��̗�ԍ�
//! @rtnval		�s�{�b�e�B���O�������ǂ���
//----------------------------------------------------------
bool MtxPivottingCol( Mtx &Mo, const Mtx &Mi, BYTE *pivot )
{
	Mtx		m( Mi );
	bool	pivoted;
	BYTE	order[4] = { 0, 1, 2, 3 };

	for( BYTE i = 0; i < 3; i++ )
	{
		BYTE idx = MtxGetPivotRow( m, i, i );

		if( idx != i )
		{
			pivoted = true;
			Swap( order[i], order[idx] );
			m.SwapCol( i, idx );
		}
	}
	Mo = m;
	if( pivot )
		memcpy( pivot, order, sizeof(BYTE)*4 );

	return pivoted;
}
