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

#ifndef MATH_MATH_HPP_INCLUDED
#define MATH_MATH_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

namespace Math {


/**
 * @brief 簡易的な３次元情報まで取り扱うクラス
 *          
 * @author  Takuya Shishido
 * @date    2010.01.29 16:06:42
 * @version 0.01, Shishido Takuya, 2010.01.29 16:06:42
 */
class Vector3
{
public:

	/*
	 * @brief constructor
	*/
	Vector3();

	/*
	 * @brief constructor
	 * @param[in]   x_  x 座標パラメータ
	 * @param[in]   y_  y 座標パラメータ
	 * @param[in]   z_  z 座標パラメータ
	*/
	Vector3(float x_, float y_, float z_);

	/*
	 * @brief operator +
	 * @param[in]   rhs     右辺値
	 * @return      各パラメータを引き算した新しいもの
	 */
	inline Vector3 operator+ (const Vector3& rhs) const;

	/*
	 * @brief operator +=
	 * @param[in]   rhs     右辺値
	 * @return      各パラメータを引き算した新しいもの
	 */
	inline Vector3& operator+= (const Vector3& rhs);

	/*
	 * @brief operator -
	 * @param[in]   rhs     右辺値
	 * @return      各パラメータを引き算した新しいもの
	 */
	inline Vector3 operator- (const Vector3& rhs) const;

	/*
	 * @brief operator -
	 * @param[in]   rhs     右辺値
	 * @return      各パラメータを引き算した新しいもの
	 */
	inline Vector3 operator-= (const Vector3& rhs);

	/*
	 * @brief パラメータに引数分倍かける
	 * @param[in]   scaling_    倍率
	*/
	void multiplication(float scaling_);

	/*
	 * @brief 外積を作成する
	 * @param[in]   vector_     もう一方のベクトル
	 * @return      作成された外積
	*/
	Vector3 crossProduct(Vector3 vector_) const;


private:

	float x;    // x 座標パラメータ
	float y;    // y 座標パラメータ
	float z;    // z 座標パラメータ
};


}    // namespace Math

#endif

