
#ifndef MATH_MATH_HPP_INCLUDED
#define MATH_MATH_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

namespace Math {


/**
 * @brief �ȈՓI�ȂR�������܂Ŏ�舵���N���X
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
	 * @param[in]   x_  x ���W�p�����[�^
	 * @param[in]   y_  y ���W�p�����[�^
	 * @param[in]   z_  z ���W�p�����[�^
	*/
	Vector3(float x_, float y_, float z_);

	/*
	 * @brief operator +
	 * @param[in]   rhs     �E�Ӓl
	 * @return      �e�p�����[�^�������Z�����V��������
	 */
	inline Vector3 operator+ (const Vector3& rhs) const;

	/*
	 * @brief operator +=
	 * @param[in]   rhs     �E�Ӓl
	 * @return      �e�p�����[�^�������Z�����V��������
	 */
	inline Vector3& operator+= (const Vector3& rhs);

	/*
	 * @brief operator -
	 * @param[in]   rhs     �E�Ӓl
	 * @return      �e�p�����[�^�������Z�����V��������
	 */
	inline Vector3 operator- (const Vector3& rhs) const;

	/*
	 * @brief operator -
	 * @param[in]   rhs     �E�Ӓl
	 * @return      �e�p�����[�^�������Z�����V��������
	 */
	inline Vector3 operator-= (const Vector3& rhs);

	/*
	 * @brief �p�����[�^�Ɉ������{������
	 * @param[in]   scaling_    �{��
	*/
	void multiplication(float scaling_);

	/*
	 * @brief �O�ς��쐬����
	 * @param[in]   vector_     ��������̃x�N�g��
	 * @return      �쐬���ꂽ�O��
	*/
	Vector3 crossProduct(Vector3 vector_) const;


private:

	float x;    // x ���W�p�����[�^
	float y;    // y ���W�p�����[�^
	float z;    // z ���W�p�����[�^
};


}    // namespace Math

#endif

