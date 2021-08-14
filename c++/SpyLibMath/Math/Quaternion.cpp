//------------------------------------------------
//! @file	CQuaternion.cpp
//! @brief	クォータオン
//! @author	伊藤貴徳
//! @date	07/07/15：再編
//! @date	08/02/11：全体を整理
//-----------------------------------------------


#include "Quaternion.h"


//----------------------------------------------------------
// メソッド
//----------------------------------------------------------


//--------------------------------------
// セット
//--------------------------------------
Quat &Quat::Set( const Mtx &M )
{
	return M.GetRotation( *this );
/*
	float trace = M[e11] + M[e22] + M[e33] + M[e44];

	if( trace >= 1.0f )
	{
		trace = sqrtf( trace );
		float divTr = 1.0f / (2 * trace);

		v.x = ( M[e23] - M[e32] ) * divTr; 
		v.y = ( M[e31] - M[e13] ) * divTr; 
		v.z = ( M[e12] - M[e21] ) * divTr; 
		w   = trace * 0.5f;

		return *this;
	}
	else
	{
		if( (M[e11] >= M[e22]) && (M[e11] >= M[e33]) )
		{
			v.x = sqrtf( M[e11] - M[e22] - M[e33] +1 ) * 0.5f;
			
			float vi = 1.0f / (v.x * 4);
			v.y = ( M[e12] + M[e21] ) * vi;
			v.z = ( M[e13] + M[e31] ) * vi;
			w   = ( M[e23] + M[e32] ) * vi;
		}
		else if( (M[e22] >= M[e11]) && (M[e22] >= M[e33]) )
		{
			v.y = sqrtf( M[e22] - M[e11] - M[e33] +1 ) * 0.5f;
			
			float vi = 1.0f / (v.y * 4);
			v.x = ( M[e23] + M[e32] ) * vi;
			v.z = ( M[e21] + M[e12] ) * vi;
			w   = ( M[e31] + M[e13] ) * vi;
		}
		else
		{
			v.z = sqrtf( M[e33] - M[e11] - M[e22] +1 ) * 0.5f;
			
			float vi = 1.0f / (v.z * 4);
			v.x = ( M[e31] + M[e13] ) * vi;
			v.y = ( M[e32] + M[e23] ) * vi;
			w   = ( M[e12] + M[e21] ) * vi;
		}

		return *this;
	}
*/
}



//--------------------------------
// D3DX型との互換用
//--------------------------------
#ifdef ___USE_D3DX___

Quat &Quat::Set( const D3DXMATRIX &M )
{
	return Mtx( M ).GetRotation( *this );
/*
	float trace = M._11 + M._22 + M._33 + M._44;

	if( trace >= 1.0f )
	{
		trace = sqrtf( trace );
		float divTr = 1.0f / (2 * trace);

		v.x = ( M._23 - M._32 ) * divTr; 
		v.y = ( M._31 - M._13 ) * divTr; 
		v.z = ( M._12 - M._21 ) * divTr; 
		w   = trace * 0.5f;

		return *this;
	}
	else
	{
		if( (M._11 >= M._22) && (M._11 >= M._33) )
		{
			v.x = sqrtf( M._11 - M._22 - M._33 +1 ) * 0.5f;
			
			float vi = 1.0f / (v.x * 4);
			v.y = ( M._12 + M._21 ) * vi;
			v.z = ( M._13 + M._31 ) * vi;
			w   = ( M._23 + M._32 ) * vi;
		}
		else if( (M._22 >= M._11) && (M._22 >= M._33) )
		{
			v.y = sqrtf( M._22 - M._11 - M._33 +1 ) * 0.5f;
			
			float vi = 1.0f / (v.y * 4);
			v.x = ( M._23 + M._32 ) * vi;
			v.z = ( M._21 + M._12 ) * vi;
			w   = ( M._31 + M._13 ) * vi;
		}
		else
		{
			v.z = sqrtf( M._33 - M._11 - M._22 +1 ) * 0.5f;
			
			float vi = 1.0f / (v.z * 4);
			v.x = ( M._31 + M._13 ) * vi;
			v.y = ( M._32 + M._23 ) * vi;
			w   = ( M._12 + M._21 ) * vi;
		}

		return *this;
	}
*/
}

#endif


//-----------------------------------------------------------
// クラス外関数
//-----------------------------------------------------------

//----------------------------------------------------------
// クォータニオンの球面線形補間
// Q1をQ2方向に補間する
//----------------------------------------------------------
Quat &QuatSlerp( Quat &Qo, const Quat &Q1, const Quat &Q2, float t )
{
	Quat q1( Q1 );
	Quat q2( Q2 );
	float  theta;

	theta = QuatDot( Q1, Q2 );

	if( theta < 0 )
	{
		theta = -theta;
		q2 *= -1;
	}

	if( theta > 1.0f )
	{
		theta = 1.0f;
	}

	if( theta < SLERP_MAX )
	{
		theta = acosf( theta );

		q1 *= sinf( theta * (1.0f - t) );
		q2 *= sinf( theta * t );
		q1 += q2;

		Qo = q1 / sinf( theta );
	}
	else
	{
		q1 += q2 * t;
		QuatNormalize( Qo, q1 );
	}

	return Qo;
}