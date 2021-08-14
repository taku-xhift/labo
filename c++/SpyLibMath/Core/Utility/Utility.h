//------------------------------------------------------------------
//! @file	Utility.h
//! @brief	�e��ėp�}�N������
//! @author	�ɓ��M��
//! @date	07/07/14
//------------------------------------------------------------------


#ifndef ___UTILITY_H___
#define ___UTILITY_H___


#define ___OPTIMIZE___		// �œK���d��


// �}�N���Ɋ�Â��ݒ�
#ifdef ___OPTIMIZE___
#define inline	__forceinline

#else
#define inline	inline

#endif


//---------------------------------------------------//
// �ėp�r�b�g�t���O�`�F�b�N
//---------------------------------------------------//
#ifndef BIT_FLAG_CHECK
#define BIT_FLAG_CHECK( target, flag )			( ( (target) & (flag) ) == (flag) )
#endif


//---------------------------------------------------//
// �ėp�G���[�`�F�b�N
//---------------------------------------------------//

// �}�N���ɂ��G���[�`�F�b�N
#ifndef VALUE_CHECK
#define VALUE_CHECK( target, val, rtnCode )		if( (target) == (val) ) return (rtnCode);
#endif

// �}�N���ɂ��NULL�`�F�b�N 
#ifndef NULL_CHECK
#define NULL_CHECK( obj, rtnCode )				if( !(obj) ) { \
													SPY_ASSERT( obj, (_T("NULL��������܂���")) ); \
													return (rtnCode); \
												}
#endif


//---------------------------------------------------//
// �폜
//---------------------------------------------------//

// �`�F�b�N���폜
#ifndef SAFE_DELETE
#define SAFE_DELETE( pObj )						if( pObj ) { delete pObj;    pObj = NULL;}
#endif

// �`�F�b�N���z��폜
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( pObj )				if( pObj ) { delete [] pObj; pObj = NULL;}
#endif

// �`�F�b�N�����
#ifndef SAFE_FREE
#define SAFE_FREE( pObj )						if( pObj ) { free( pObj );	 pObj = NULL;}
#endif

// �n���h���N���[�Y
#ifndef SAFE_CLOSE
#define	SAFE_CLOSE( handle )					if( handle ) { ::CloseHandle( handle ); handle = NULL;}
#endif



//---------------------------------------------------//
// D3D�p���
//---------------------------------------------------//
#ifndef SAFE_RELEASE
#define SAFE_RELEASE( pObj )					if( pObj ) { pObj->Release(); pObj = NULL;}
#endif


//---------------------------------------------------//
// ������ϊ�
//---------------------------------------------------//
#ifndef TO_STRING
#define TO_STRING( str )	#str
#endif


#endif // #ifndef ___UTILITY_H___