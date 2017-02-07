/**
 * @file
 * @brief 計算に関するクラス、モジュール
 *
 * @author Takuya Shishido
 * @date   2010.01.29 17:36:35
 *
 * @version 0.01, Shishido Takuya, 2010.01.29 17:36:35
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Math.hpp"


namespace Math {

/*-----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
Vector3::Vector3() : x(.0f), y(.0f), z(.0f)
{
}

/*-----------------------------------------------------
 * @brief constructor
 * @param[in]   x_  x 座標パラメータ
 * @param[in]   y_  y 座標パラメータ
 * @param[in]   z_  z 座標パラメータ
 *---------------------------------------------------*/
Vector3::Vector3(float x_, float y_, float z_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
}


/*-----------------------------------------------------
 * @brief operator +
 * @param[in]   rhs     右辺値
 * @return      各パラメータを引き算した新しいもの
 *---------------------------------------------------*/
Vector3 Vector3::operator+ (const Vector3& rhs) const
{
	return Vector3(this->x + rhs.x,
				   this->y + rhs.y,
				   this->z + rhs.z);
}

/*-----------------------------------------------------
 * @brief operator +=
 * @param[in]   rhs     右辺値
 * @return      各パラメータを引き算した新しいもの
 *---------------------------------------------------*/
Vector3& Vector3::operator+= (const Vector3& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

	return *this;
}

/*-----------------------------------------------------
 * @brief operator -
 * @param[in]   rhs     右辺値
 * @return      各パラメータを引き算した新しいもの
 *---------------------------------------------------*/
Vector3 Vector3::operator- (const Vector3& rhs) const
{
	return Vector3(this->x - rhs.x,
				   this->y - rhs.y,
				   this->z - rhs.z);
}

/*-----------------------------------------------------
 * @brief operator -
 * @param[in]   rhs     右辺値
 * @return      各パラメータを引き算した新しいもの
 *---------------------------------------------------*/
Vector3 Vector3::operator-= (const Vector3& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;

	return *this;
}

/*-----------------------------------------------------
 * @brief パラメータに引数分倍かける
 * @param[in]   scaling_    倍率
 *---------------------------------------------------*/
void Vector3::multiplication(float scaling_)
{
	this->x *= scaling_;
	this->y *= scaling_,
	this->z *= scaling_;
}

/*-----------------------------------------------------
 * @brief 外積を作成する
 * @param[in]   vector_     もう一方のベクトル
 * @return      作成された外積
 *---------------------------------------------------*/
Vector3 Vector3::crossProduct(Vector3 vector_) const
{
	// TODO めんどくさかった
	// 理想は新しい Vector3 に外積の結果を代入し、返す
	return Vector3();
}



}    // namespace Math

