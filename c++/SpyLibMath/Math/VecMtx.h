//-----------------------------------------------------------------------------------
//! @file	VecMtx.h
//! @brief	2-4�����x�N�g����4x4�̍s��
//! @author	�ɓ��M��
//! @date	07/07/15�F�ĕ�
//! @date	07/08/05�F�s�񃁃\�b�h�Ɋe��ϊ��s��쐬��ǉ�
//! @date	07/08/11�F�Q�������S�����x�N�g����ǉ�
//! @date			  �x�N�g���̒ǉ��ɔ����I�[�o�[���[�h����
//! @date	07/08/26�F�s��̃A�N�Z�b�T������
//! @date			  �s��̂k�t������ǉ�
//! @date	07/09/01�F�t�s��v�Z���k�t������p�������̂ɕύX
//! @date			  �x�N�g���̔C�ӎ���]��ǉ�
//! @date	07/09/08�F�s���()���Z�q�ǉ�
//! @date	08/02/11�F�S�̂𐮗�
//-----------------------------------------------------------------------------------

// 2-4�����x�N�g��&4*4�s��

#ifndef ___VEC_AND_MTX_H___
#define ___VEC_AND_MTX_H___

#include "../Core/Utility/LibHeader.h"


#include <cmath>

#include <cstdlib>
#define _USE_LH_			// �r���[�s��ƃv���W�F�N�V�����s��̍쐬���ɍ���n�ō쐬����
#include <d3dx9math.h>


typedef _W64 int		differ_type;


class CVector3;
class CMatrix44;
class CQuaternion;
// �s�񁨃x�N�g���ϊ����̑I��
enum eMtxToVec { kTNoW,		// ���s�ړ����Aw���Z�����i�f�t�H���g�j
				 kNoTNoW,	// ���s�ړ������Aw���Z�����i�@���v�Z�j
				 kTW,		// ���s�ړ����Aw���Z����
				 kNoTW		// ���s�ړ������Aw���Z����
			   };





//===============================================================================//
//  �R�����x�N�g���N���X
//===============================================================================//
class CVector3
{
public:
	// �A�N�Z�X�p��
	enum { eX, eY, eZ };

private:
	//--------------------------------------------------//
	// �����o�ϐ�
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
	// �e��R���X�g���N�^
	//--------------------------------------------------//
	CVector3();
	CVector3( float x, float y, float z=0 );
	CVector3( const float *);
	CVector3( const CVector3 &v );
	CVector3( const CVector3 &Vto, const CVector3 &Vfor );	///< pVto->pVfor�x�N�g�����쐬
	CVector3( const CMatrix44&M, eMtxToVec = kTNoW );

	CVector3( const D3DXVECTOR2 &D3dVec, float z=0 );
	CVector3( const D3DXVECTOR3 &D3dVec );
	CVector3( const D3DXVECTOR4 &D3dVec, bool w = false );		///< w=true�ł����Z���s��
	CVector3( const D3DXVECTOR2 &D3dVto, const D3DXVECTOR2 &D3dVfor, float z=0 );
	CVector3( const D3DXVECTOR3 &D3dVto, const D3DXVECTOR3 &D3dVfor );
	CVector3( const D3DXMATRIX  &DxMtx, eMtxToVec = kTNoW );

	~CVector3();


	//--------------------------------------------------//
	// �Z�b�g
	//--------------------------------------------------//
	CVector3 &Set( float x, float y, float z=0.0f );
	CVector3 &Set( const float *p );
	CVector3 &Set( const CVector3 &Vto, const CVector3 &Vfor );
	CVector3 &Set( const CMatrix44&, eMtxToVec = kTNoW );

	CVector3 &Set( const D3DXVECTOR2 &D3dVec, float z=0 );
	CVector3 &Set( const D3DXVECTOR3 &D3dVec );
	CVector3 &Set( const D3DXVECTOR4 &D3dVec, bool w = false );///< w=true�ł����Z���s��
	CVector3 &Set( const D3DXVECTOR2 &D3dVto, const D3DXVECTOR2 &D3dVfor, float z=0 );
	CVector3 &Set( const D3DXVECTOR3 &D3dVto, const D3DXVECTOR3 &D3dVfor );
	CVector3 &Set( const D3DXMATRIX  &DxMtx, eMtxToVec = kTNoW );


	//--------------------------------------------------//
	// D3DX�^�Ƃ̌݊�
	//--------------------------------------------------//


	// D3DX�^�ւ̕ϊ��p
	D3DXVECTOR3 &toD3DVEC3( D3DXVECTOR3 &Dv3 )					const;
	D3DXVECTOR4 &toD3DVEC4( D3DXVECTOR4 &Dv3, float w = 1.0f )	const;
	D3DXMATRIX  &toD3DMTX ( D3DXMATRIX  &D3m )					const;

	operator D3DXVECTOR3 ()	const;
	operator D3DXMATRIX	 ()	const;


	// D3DX�^����̑���ɑΏ�
	CVector3 &operator = ( const D3DXVECTOR2 &v  );
	CVector3 &operator = ( const D3DXVECTOR3 &v  );
	CVector3 &operator = ( const D3DXVECTOR4 &v  );				///< w���Z�Ȃ�
	CVector3 &operator = ( const D3DXMATRIX  &m  );


	//--------------------------------------------------//
	// ���
	//--------------------------------------------------//
	CVector3 &operator = ( const CVector3  &v  );
	CVector3 &operator = ( const CMatrix44 &m  );


	//--------------------------------------------------//
	// �e��Q�����Z
	//--------------------------------------------------//

	// �W�����Z
	CVector3 operator + ( const CVector3 &v2 )	const;
	CVector3 operator - ( const CVector3 &v2 )	const;
	CVector3 operator * ( float f )				const;
	CVector3 operator / ( float f )				const;

	friend CVector3 operator * ( float f, const CVector3& );
	friend CVector3 operator / ( float f, const CVector3& );


	// ������Z
	CVector3 &operator += ( const CVector3 &v2 );
	CVector3 &operator -= ( const CVector3 &v2 );
	CVector3 &operator *= ( float f );
	CVector3 &operator /= ( float f );


	// �s��Ƃ̉��Z
	CMatrix44 operator *( const CMatrix44 &rM )  const;


	//--------------------------------------------------//
	// �P�����Z�ق�
	//--------------------------------------------------//
	//float  &operator [] ( differ_type i );
	//float   operator [] ( differ_type i )		const;
	CVector3 operator - ()						const;		// �����𔽓]
	float Norm2()								const;		// �傫���̂Q���Ԃ�
	float Norm()								const;		// �x�N�g���̑傫����Ԃ�
	const float *Ptr()							const;
	operator const float *()					const;
	operator       float *();


	//--------------------------------------------------//
	// �_�����Z
	//--------------------------------------------------//
	bool operator == ( const CVector3 &v2 )		const;
	bool operator != ( const CVector3 &v2 )		const;


	//--------------------------------------------------//
	// �ɍ��W�Ƃ̌݊�
	//--------------------------------------------------//

	// �ɍ��W���쐬
	// (0,0,1)���(��]�p�ƁA�p�ӂ�����0)�Ƃ���
	CVector3 &PolarCoordinate( float r, float theta, float phi );

	// ���S�܂ł̋�����ύX����
	CVector3 &ChangePolarCoordinateR( float r );


	//--------------------------------------------------//
	// ���̑�
	//--------------------------------------------------//
	CVector3 &Normalize();								// �P�ʉ�
	bool IsNormal()								const;	// �P�ʃx�N�g���ł��邩����
	bool IsZeroVec()							const;	// �[���x�N�g���ł��邩����
	float Dist ( const CVector3 & )				const;	// ���������߂�
	float Dist2( const CVector3 & )				const;	// ������2������߂�

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

	// ����@
	CVector3 Normal() const;
	CVector3 Vertical() const;

};

typedef CVector3	Vec3;



//-----------------------------------------------------------------------//
// �e��Q�����Z
//-----------------------------------------------------------------------//
Vec3 &Vec3Add( Vec3 &pVo, const Vec3 &pVi, const Vec3 &pVi2);		// ���Z
Vec3 &Vec3Sub( Vec3 &pVo, const Vec3 &pVi, const Vec3 &pVi2);		// ���Z
Vec3 &Vec3Mul( Vec3 &pVo, const Vec3 &pVi, float  f );		// ��Z
Vec3 &Vec3Div( Vec3 &pVo, const Vec3 &pVi, float  f );		// ���Z



//-----------------------------------------------------------------------//
// �x�N�g�����Z
//-----------------------------------------------------------------------//
Vec3 &Vec3Reverse    ( Vec3 & pVo,  const Vec3 &pVi );				// �t�������쐬
Vec3 &Vec3Normalize  ( Vec3 & pVo,  const Vec3 &pVi );				// �P�ʉ�
float Vec3Dot        ( const Vec3 &pV1,  const Vec3 &pV2 );				// ����
Vec3 &Vec3Cross      ( Vec3 & pVo,  const Vec3 &pVi,  const Vec3 &pVi2);	// �O��
float Vec3CrossAngle ( const Vec3 &pV1,  const Vec3 &pV2 );				// ���p�i�p�x�̓��W�A�����͓x���j
Vec3 &Vec3RotationAxisX( Vec3 &pVout, const Vec3 &pVin, float  rot );	// �x�N�g������]
Vec3 &Vec3RotationAxisY( Vec3 &pVout, const Vec3 &pVin, float  rot );
Vec3 &Vec3RotationAxisZ( Vec3 &pVout, const Vec3 &pVin, float  rot );
Vec3 &Vec3RotationAxis ( Vec3 &pVout, const Vec3 &pVin, const Vec3 &pVaxis, float rot );
Vec3 &Vec3Lerp       ( Vec3 &pVout, const Vec3 &pVin1, const Vec3 &pVin2, float t );	// ���`���
Vec3 &Vec3Hermite    ( Vec3 &pVout, const Vec3 &pVin1, const Vec3 &pVtan1, 
					  const Vec3 &pVin2, const Vec3 &pVtan2, float t );	// �G���~�[�g���







//===============================================================================//
// 4*4�s��N���X
//===============================================================================//

// �s��v�f�A�N�Z�X�p�񋓌^

enum{ e11, e21, e31, e41, e12, e22, e32, e42, e13, e23, e33, e43, e14, e24, e34, e44 };


class CMatrix44
{
private :
	//--------------------------------------------------//
	// �����o�ϐ�
	// �ꎟ�z��ŗp��
	// �f�[�^�̎󂯓n�����l���A
	// ��P�ʁA�s�P�ʂ�define�ŕύX�\�ɂ��Ă���
	//--------------------------------------------------//
	float m_m[16];


public :
	/*-----------------------------------------------------*/
	// �e��R���X�g���N�^
	/*-----------------------------------------------------*/
	CMatrix44( bool identity = true);							// �K�v�Ȃ�ΒP�ʍs��ŏ���������
	CMatrix44(	float _11, float _12, float _13, float _14,		// �S�Ă̗v�f�𖾎��I�Ɏw��
				float _21, float _22, float _23, float _24,
				float _31, float _32, float _33, float _34,
				float _41, float _42, float _43, float _44 );
	CMatrix44( const float *m );								//���� �z��œn��
	CMatrix44( float x, float y, float z );						//�x�N�g���Ƃ��ēn��
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
	// D3DX�݊�
	/*-----------------------------------------------------*/

	// D3DX�^�ւ̕ϊ��y��D3DX�^����̑��
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


	// �Q�ƌ^
	CMatrix44 &operator = ( const D3DXVECTOR2	&v );
	CMatrix44 &operator = ( const D3DXVECTOR3	&v );
	CMatrix44 &operator = ( const D3DXVECTOR4	&v );
	CMatrix44 &operator = ( const D3DXMATRIX	&m );
	CMatrix44 &operator = ( const D3DXQUATERNION &q );



	/*-----------------------------------------------------*/
	// �Z�b�g
	/*-----------------------------------------------------*/
	
	// �v�f���w�肵�Ēl���Z�b�g
	void SetVal( differ_type num, float val );
	void SetVal( differ_type row, differ_type col, float val );

	// �s�Z�b�g
	void SetRow( differ_type colNo, float x, float y, float z, float trs );
	void SetRow( differ_type rowNo, const Vec3 &, float trs );

	// ��Z�b�g
	void SetCol( differ_type colNo, float x, float y, float z, float w );
	void SetCol( differ_type colNo, const Vec3 &, float w );

	// �ꊇ�Z�b�g
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
	// �Q�b�g
	/*-----------------------------------------------------*/
	
	// �ꊇ
	const float *GetMatrix()					const;
	float		*GetMatrix();
	float		*GetMatrix( float *pM )			const;
	operator const float*()						const;
	operator       float*();

	// �v�f���w�肵�Ēl���擾
	float &GetVal( differ_type i );
	float  GetVal( differ_type i )						const;
	float &GetVal( differ_type row, differ_type col );
	float  GetVal( differ_type row, differ_type col )	const;
	//float &operator [] ( differ_type i );
	//float  operator [] ( differ_type i )				const;
	float &operator () ( differ_type row, differ_type col );
	float  operator () ( differ_type row, differ_type col )		const;

	// ��擾
	Vec3  &GetCol( Vec3 &, differ_type colNo )			const;
	float *GetCol( float*, differ_type colNo )			const;

	// �s�擾
	Vec3  &GetRow( Vec3 &, differ_type rowNo )			const;
	float *GetRow( float*, differ_type rowNo )			const;

	// �x�N�g���v�f�Ƃ��Ď擾
	// ���s�ړ������܂�
	float XT()									const;
	float XT2D()								const;	// z�����𖳎�����
	float YT()									const;
	float YT2D()								const;	// z�����𖳎�����
	float ZT()									const;
	float WT()									const;

	// ���s�ړ������Ȃ�
	float XNoT()								const;
	float XNoT2D()								const;	// z�����𖳎�����
	float YNoT()								const;
	float YNoT2D()								const;	// z�����𖳎�����
	float ZNoT()								const;
	float WNoT()								const;

	// �����x�N�g���Ə�Z���ăx�N�g���v�f���擾
	// ���s�ړ������܂�
	float VecXT( const Vec3 & )						const;
	float VecYT( const Vec3 & )						const;
	float VecZT( const Vec3 & )						const;
	float VecWT( const Vec3 & )						const;

	// ���s�ړ������Ȃ�
	float VecXNoT( const Vec3 & )					const;
	float VecYNoT( const Vec3 & )					const;
	float VecZNoT( const Vec3 & )					const;
	float VecWNoT( const Vec3 & )					const;


	/*-----------------------------------------------------*/
	// ���
	/*-----------------------------------------------------*/
	CMatrix44 &operator = ( const CVector3	&rV );
 	CMatrix44 &operator = ( const CQuaternion	&rQ );
	CMatrix44 &operator = ( const CMatrix44	&m  );


	/*-----------------------------------------------------*/
	// �e�퉉�Z�q
	/*-----------------------------------------------------*/
	CMatrix44  operator + ( const CMatrix44 &rM )	const;
	CMatrix44  operator - ( const CMatrix44 &rM )	const;
	CMatrix44  operator * ( float f ) const;
	CMatrix44  operator / ( float f ) const;

	CMatrix44 &operator += ( const CMatrix44 &M  );
	CMatrix44 &operator -= ( const CMatrix44 &M  );
	CMatrix44 &operator *= ( float f );
	CMatrix44 &operator /= ( float fa );

	//�s�񓯎m�̏�Z
	CMatrix44  operator *  ( const CMatrix44 &M  )	const;
	CMatrix44 &operator *= ( const CMatrix44 &M  );

	friend CMatrix44 operator  *( float, const CMatrix44 & );

	// �x�N�g���Ƃ̉��Z
	// �� �l�ł̏��Z�͍s��Ȃ�
	CVector3  operator *(  const CVector3& )		const;


	/*-----------------------------------------------------*/
	// �_�����Z
	/*-----------------------------------------------------*/
	bool operator == ( const CMatrix44 & )			const;
	bool operator != ( const CMatrix44 & )			const;


	/*-----------------------------------------------------*/
	// ���̑�
	/*-----------------------------------------------------*/
	CMatrix44 operator - ()							const;			// �������]
	CMatrix44 &Identity();											// �P�ʍs��ɂ���
	bool IsIdentity()								const;			// �P�ʍs��ł��邩����
	float Det()										const;			// �s��
	

	/*-----------------------------------------------------*/
	// ��{�ϊ��̃T�|�[�g
	/*-----------------------------------------------------*/
	CMatrix44 &SwapRow( differ_type row1, differ_type row2 );		// �s����ւ�
	CMatrix44 &SwapCol( differ_type col1, differ_type col2 );		// �����ւ�
	CMatrix44 &MulRow ( differ_type row, float f );					// �w��s�ɌW�����|����
	CMatrix44 &MulCol ( differ_type col, float f );					// �w���ɌW�����|����


	/*-----------------------------------------------------*/
	// �e��ϊ��s��쐬
	/*-----------------------------------------------------*/
	CMatrix44 &RotationX( float rad );									// ��]�s��쐬
	CMatrix44 &RotationY( float rad );
	CMatrix44 &RotationZ( float rad );

	CMatrix44 &RotationXPivot( const Vec3 &pos, float rad );			// �w����W���S��]�s��쐬
	CMatrix44 &RotationYPivot( const Vec3 &pos, float rad );
	CMatrix44 &RotationZPivot( const Vec3 &pos, float rad );
	CMatrix44 &RotationXPivot( float x, float y, float z, float rad );
	CMatrix44 &RotationYPivot( float x, float y, float z, float rad );
	CMatrix44 &RotationZPivot( float x, float y, float z, float rad );
	
	CMatrix44 &Scaling( const Vec3 &scl );								// �X�P�[�����O�s��̍쐬
	CMatrix44 &Scaling( float x, float y, float z );

	CMatrix44 &ScalingPivot( const Vec3 &pos, const Vec3 &scl );		// �w��ʒu���S�X�P�[�����O�s��̍쐬

	CMatrix44 &Translate( const Vec3 &trs );							// ���s�ړ��s��̍쐬
	CMatrix44 &Translate( float x, float y, float z );

	CMatrix44 &SetTranslate( const Vec3 &trs );							// �i���̗v�f�͕ς����Ɂj���s�ړ��p�����[�^��K�p����
	CMatrix44 &SetTranslate( float x, float y, float z );

	CMatrix44 &AddTranslate( const Vec3 &trs );							// �i���̗v�f�͕ς����Ɂj���s�ړ��p�����[�^�ɉ��Z����
	CMatrix44 &AddTranslate( float x, float y, float z );

	CMatrix44 &RotationAxis( const Vec3 &axis, float rad );				// �C�ӎ�����ɉ�]
	CMatrix44 &RotationAxis( const CQuaternion & );
	CMatrix44 &RotationAxis( float x, float y, float z, float rad );

	CMatrix44 &RotationAxisPivot( const Vec3 &axis, float rad, const Vec3 &pos );	// �w����W���S�C�ӎ�����ɉ�]
	CMatrix44 &RotationAxisPivot( const CQuaternion &, const Vec3 &pos );
	CMatrix44 &RotationAxisPivot( float x, float y, float z, float rad, const Vec3 &pos );

	CMatrix44 &RotationYPR( const Vec3 &YPR );							// ���[�s�b�`���[����]
	CMatrix44 &RotationYPR( float pitch, float yaw, float roll );

	CMatrix44 &RotationYPRPivot( const Vec3 &YPR, const Vec3 &pos );	// �w��ʒu���S���[�s�b�`���[����]
	CMatrix44 &RotationYPRPivot( float pitch, float yaw, float roll, const Vec3 &pos );


	/*-----------------------------------------------------*/
	// �g�����X�t�H�[���쐬
	/*-----------------------------------------------------*/
	CMatrix44 &Compose( const Vec3 &Trs, const Vec3 &Rot, const Vec3 &Scl );
	CMatrix44 &Compose( const Vec3 &Trs, const CQuaternion &, const Vec3 &Scl );


	/*-----------------------------------------------------*/
	// �g�����X�t�H�[�����̎擾
	/*-----------------------------------------------------*/
	Vec3 &GetTranslate( Vec3 & )					const;	// ���s�ړ������݂̂��擾
	Vec3 &GetScale( Vec3 & )						const;	// �X�P�[���擾
	CQuaternion &GetRotation( CQuaternion & )		const;	// ��]�����擾
	void Decompose( Vec3 &Scl, CQuaternion &, Vec3 &trs )	const;	// �g�����X�t�H�[������ 


	/*-----------------------------------------------------*/
	// �l�̑���̊֌W��t�����h�ɂ����֐�
	/*-----------------------------------------------------*/
	friend CMatrix44 &MtxMulTranslate( CMatrix44 &, float, float, float );
	friend CMatrix44 &MtxMulTranslate( float, float, float, CMatrix44& );
	friend CMatrix44 &MtxMulScaling  ( CMatrix44 &, float, float, float );
	friend CMatrix44 &MtxMulScaling  ( float, float, float, CMatrix44& );

};

typedef CMatrix44	Mtx;



//--------------------------------------------------------------
// �N���X�O�֐�
//--------------------------------------------------------------

/*-----------------------------------------------------*/
// �l�����Z�֐�
/*-----------------------------------------------------*/
Mtx  &MtxAdd( Mtx &O,  const Mtx &In1, const Mtx  &pIn2 );		// ���Z
Mtx  &MtxSub( Mtx &O,  const Mtx &In1, const Mtx  &pIn2 );		// ���Z
Mtx  &MtxMul( Mtx &O,  const Mtx &In1, const Mtx  &pIn2 );		// ��Z
Vec3 &MtxMul( Vec3 &O, const Mtx &Min, const Vec3 &pVin, eMtxToVec = kTNoW );
Mtx  &MtxMul( Mtx &O,  float f,  const Mtx  &In );
Mtx  &MtxMul( Mtx &O,  const Mtx &In,  float f  );
Mtx  &MtxDiv( Mtx &O,  float f,  const Mtx  &In );		// ���Z


/*-----------------------------------------------------*/
// �e��ϊ�����
/*-----------------------------------------------------*/

//--------------------------------------------------
// �����S�̉�]�s��Ɗ|����
//--------------------------------------------------
Mtx &MtxMulRotationX( Mtx &, float );
Mtx &MtxMulRotationY( Mtx &, float );
Mtx &MtxMulRotationZ( Mtx &, float );
Mtx &MtxMulRotationX( float, Mtx &);
Mtx &MtxMulRotationY( float, Mtx &);
Mtx &MtxMulRotationZ( float, Mtx &);


//--------------------------------------------------
// �w����W���S�̉�]�s��Ɗ|����
//--------------------------------------------------

// pM*��]�s���pM�Ɋi�[
Mtx &MtxMulRotationX( Mtx &pM, float r, float y, float z );	// x�����S
Mtx &MtxMulRotationY( Mtx &pM, float r, float x, float z );	// y�����S
Mtx &MtxMulRotationZ( Mtx &pM, float r, float x, float y );	// z�����S

// ��]�s��*M��M�Ɋi�[
Mtx &MtxMulRotationX( float r, float y, float z, Mtx &M );	// x�����S
Mtx &MtxMulRotationY( float r, float x, float z, Mtx &M );	// y�����S
Mtx &MtxMulRotationZ( float r, float x, float y, Mtx &M );	// z�����S

// ���ꂼ��̃I�[�o�[���[�h�`��
Mtx &MtxMulRotationX( Mtx &M, float  r, const Vec3 &V );
Mtx &MtxMulRotationY( Mtx &M, float  r, const Vec3 &V );
Mtx &MtxMulRotationZ( Mtx &M, float  r, const Vec3 &V );
Mtx &MtxMulRotationX( float  r, const Vec3 &V, Mtx &M );
Mtx &MtxMulRotationY( float  r, const Vec3 &V, Mtx &M );
Mtx &MtxMulRotationZ( float  r, const Vec3 &V, Mtx &M );


//--------------------------------------------------
// �N�H�[�^�j�I�����g������]���|����
//--------------------------------------------------
Mtx &MtxRotationQuat( Mtx &, const CQuaternion & );
Mtx &MtxRotationQuat( const CQuaternion &, Mtx & );


//--------------------------------------------------
// �w����W���S�ŃN�H�[�^�j�I�����g������]���|����
//--------------------------------------------------
Mtx &MtxRotationQuatPivot( Mtx &, const CQuaternion &, const Vec3 & );
Mtx &MtxRotationQuatPivot( const CQuaternion &, const Vec3 &, Mtx & );


//--------------------------------------------------
// �s����g����x,y,z ����]���v�Z
//--------------------------------------------------

enum eMtxRotType { kXYZ, kXZY, kYXZ, kYZX, kZXY, kZYX };

Mtx &MtxRotationXYZ( Mtx &,   const Vec3 &, eMtxRotType = kXYZ );	// �s��*��]
Mtx &MtxRotationXYZ( const Vec3 &, Mtx &,   eMtxRotType = kXYZ );	// ��]*�s��


//--------------------------------------------------
// ���s�ړ��s��Ɗ|����
//--------------------------------------------------
Mtx &MtxMulTranslate( Mtx &,  float, float, float );			// �s��*���s�ړ��s��
Mtx &MtxMulTranslate( Mtx &  M, const Vec3 &V );
Mtx &MtxMulTranslate( float, float, float , Mtx &);				// ���s�ړ��s��*�s��
Mtx &MtxMulTranslate( const Vec3 &V, Mtx &  M );


//--------------------------------------------------
// �X�P�[�����O�s��Ɗ|����
//--------------------------------------------------
Mtx &MtxMulScaling( Mtx &, float, float, float );				// �s��*�X�P�[�����O�s��
Mtx &MtxMulScaling( Mtx &, const Vec3 &V );
Mtx &MtxMulScaling( float, float, float, Mtx & );				// �X�P�[�����O�s��*�s��
Mtx &MtxMulScaling( const Vec3 &V, Mtx &M );


//--------------------------------------------------
// �w����W���S�̃X�P�[�����O�s��Ɗ|����
//--------------------------------------------------
Mtx &MtxMulScalingPivot( Mtx &, const Vec3 &scl, const Vec3 &pos );	// �s��*�X�P�[�����O
Mtx &MtxMulScalingPivot( const Vec3 &scl, const Vec3 &pos, Mtx & );	// �X�P�[�����O*�s��


//--------------------------------------------------
// �ϊ��s��̍쐬
//--------------------------------------------------
Mtx &MtxCompose( const Vec3 &Trs, const Vec3 &Rot, const Vec3 &Scl, Mtx &);
Mtx &MtxCompose( const Vec3 &Trs, const CQuaternion &Rot, const Vec3 &Scl, Mtx &);


//--------------------------------------------------
// ���̑�
//--------------------------------------------------

// �������]
Mtx &MtxSignReverse( Mtx &pMo, const Mtx &M );

// �]�u�s��쐬
Mtx &MtxTranspose( Mtx &pMo, const Mtx &M );

// �t�s��쐬
Mtx &MtxInverse( Mtx &pMo, const Mtx &M, float *pDet=NULL );

// �k�t�������s��
bool MtxLUDecomp( Mtx &pMl, Mtx &pMu, const Mtx &pMsrc, BYTE *pivot=NULL );
bool MtxLUDecomp( Mtx &pMlu, const Mtx &pMsrc, BYTE *pivot=NULL );	// ����  �P��̍s��Ɍ��ʂ��i�[

// LU�s��̋t�s������߂�
bool MtxLUInverse( Mtx &pMli, Mtx &PMui, const Mtx &pMl, const Mtx &pMu );
bool MtxLUInverse( Mtx &pMli, Mtx &PMui, const Mtx &pMlu );
bool MtxLUInverse( Mtx &pMlui, const Mtx &pMl, const Mtx &pMu );
bool MtxLUInverse( Mtx &pMlui, const Mtx &pMlu );

// �r���[�s��쐬
Mtx &MtxView( Mtx &pMo, const Vec3 &vEye, const Vec3 &vAt, const Vec3 &vUp );

// �v���W�F�N�V�����s��쐬
Mtx &MtxProjection( Mtx &pMo, float fovY, float aspect, float near, float far );

// �s�{�b�g�T��
BYTE MtxGetPivotRow( const Mtx &M, BYTE row, BYTE st=0 );
BYTE MtxGetPivotCol( const Mtx &M, BYTE col, BYTE st=0 );

// �s�{�b�e�B���O
bool MtxPivottingRow( Mtx &pMo, const Mtx &pMi, BYTE *pivot );
bool MtxPivottingCol( Mtx &pMo, const Mtx &pMi, BYTE *pivot );


#include "Vec3.inl"
#include "Mtx.inl"


#endif

