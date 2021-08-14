//-----------------------------------------------------------
//! @fiule	CQuaternion.h
//! @brief	�N�H�[�^�I��
//! @author �ɓ��M��
//! @date	07/07/15�F�ĕ�
//! @date	08/02/11�F�S�̂𐮗�
//-----------------------------------------------------------


#ifndef ___QUATERNION_H___
#define ___QUATERNION_H___


//#include "Core/Utility/LibHeader.h"
#include "VecMtx.h"


//------------------------------------------------------------------
// �N�H�[�^�j�I���N���X
//------------------------------------------------------------------
class CQuaternion
{
public:
	// �A�N�Z�X�p�񋓌^
	enum { eX, eY, eZ, eW };

private:
	//--------------------------------------------------//
	// �����o�ϐ�
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
	// �R���X�g���N�^
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
	// �Z�b�g�p
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
	// D3DX�^�Ƃ̑��݌݊�
	//--------------------------------------------------//
	D3DXQUATERNION &toD3DQuat( D3DXQUATERNION &Q )		const;
	D3DXMATRIX     &toD3DMtx ( D3DXMATRIX     &M )		const;

	operator D3DXQUATERNION ()							const;
	operator D3DXMATRIX		()							const;

	// D3DX�^����̑���ɑΏ�
	CQuaternion &operator = ( const D3DXQUATERNION & );
	CQuaternion &operator = ( const D3DXMATRIX & );



	//--------------------------------------------------//
	// ������Z�q
	//--------------------------------------------------//
	CQuaternion &operator = ( const CQuaternion &Q  );
	CQuaternion &operator = ( const Mtx & M  );


	//--------------------------------------------------//
	// �傫���A�����Ȃ�
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
	// �e�퉉�Z�q
	/***********************************************************/

	//--------------------------------------------------//
	// �Q�����Z�q
	//--------------------------------------------------//
	
	// �W�����Z
	CQuaternion operator + ( const CQuaternion &Q  )	const;
	CQuaternion operator - ( const CQuaternion &Q  )	const;
	CQuaternion operator * ( float f )					const;
	CQuaternion operator / ( float f )					const;

	CQuaternion operator * ( const CQuaternion &Q  )	const;


	// ������Z
	CQuaternion &operator += ( const CQuaternion &Q  );
	CQuaternion &operator -= ( const CQuaternion &Q  );
	CQuaternion &operator *= ( float f );
	CQuaternion &operator /= ( float f );

	CQuaternion &operator *= ( const CQuaternion &Q  );

	// �t�����h
	friend CQuaternion  operator * ( float f, const CQuaternion & );


	//--------------------------------------------------//
	// �_�����Z
	//--------------------------------------------------//
	bool operator == ( const CQuaternion &Q  )			const;
	bool operator != ( const CQuaternion &Q  )			const;

	
	//--------------------------------------------------//
	// ���̑�
	//--------------------------------------------------//
	CQuaternion &Normalize();
	bool IsNormal()										const;
	bool Zero()											const;

};

typedef CQuaternion	Quat;



//----------------------------------------------------------//
// �N���X�O�֐�
//----------------------------------------------------------//

//-----------------------------------------------------
// ���Z�֐�
//-----------------------------------------------------
Quat &QuatAdd( Quat &Qo, const Quat &Qi1, const Quat &Qi2 );	// ���Z
Quat &QuatSub( Quat &Qo, const Quat &Qi1, const Quat &Qi2 );	// ���Z
Quat &QuatMul( Quat &Qo, const Quat &Qi1, const Quat &Qi2 );	// ��Z
Quat &QuatMul( Quat &Qo, const Quat &Qi,  float f );
Quat &QuatDiv( Quat &Qo, const Quat &Qi,  float fa );			// ���Z
float QuatDot( const Quat &pQ1, const Quat &pQ2 );				// ����



//-----------------------------------------------------
// �e�폈��
//-----------------------------------------------------
Quat &QuatNormalize  ( Quat &Qo, const Quat &Qi );				// �P�ʉ�
Quat &QuatReverse    ( Quat &Qo, const Quat &Qi );				// ���]
Quat &QuatConjugugate( Quat &Qo, const Quat &Qi );				// ����
Quat &QuatInverse    ( Quat &Qo, const Quat &Qi );				// �t��
Quat &QuatRotation   ( Quat &Qo, const Vec3 &Vaxis, float rot );// ��]  ���͓����Ő��K�������
Mtx  &QuatRotation   ( Mtx  &Mo, const Vec3 &Vaxis, float rot );
Quat &QuatRotationYPR( Quat &Qo, const Vec3 &Rot );				// ���[�s�b�`���[����]
Mtx  &QuatRotationYPR( Mtx  &Mo, const Vec3 &Rot );
Quat &QuatSlerp      ( Quat &Qo, const Quat &Qorig, const Quat &Qtgt, float t );	// ���ʐ��`�⊮


#include "Quaternion.inl"


#endif
