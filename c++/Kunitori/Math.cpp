
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
 * @param[in]   x_  x ���W�p�����[�^
 * @param[in]   y_  y ���W�p�����[�^
 * @param[in]   z_  z ���W�p�����[�^
 *---------------------------------------------------*/
Vector3::Vector3(float x_, float y_, float z_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
}


/*-----------------------------------------------------
 * @brief operator +
 * @param[in]   rhs     �E�Ӓl
 * @return      �e�p�����[�^�������Z�����V��������
 *---------------------------------------------------*/
Vector3 Vector3::operator+ (const Vector3& rhs) const
{
	return Vector3(this->x + rhs.x,
				   this->y + rhs.y,
				   this->z + rhs.z);
}

/*-----------------------------------------------------
 * @brief operator +=
 * @param[in]   rhs     �E�Ӓl
 * @return      �e�p�����[�^�������Z�����V��������
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
 * @param[in]   rhs     �E�Ӓl
 * @return      �e�p�����[�^�������Z�����V��������
 *---------------------------------------------------*/
Vector3 Vector3::operator- (const Vector3& rhs) const
{
	return Vector3(this->x - rhs.x,
				   this->y - rhs.y,
				   this->z - rhs.z);
}

/*-----------------------------------------------------
 * @brief operator -
 * @param[in]   rhs     �E�Ӓl
 * @return      �e�p�����[�^�������Z�����V��������
 *---------------------------------------------------*/
Vector3 Vector3::operator-= (const Vector3& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;

	return *this;
}

/*-----------------------------------------------------
 * @brief �p�����[�^�Ɉ������{������
 * @param[in]   scaling_    �{��
 *---------------------------------------------------*/
void Vector3::multiplication(float scaling_)
{
	this->x *= scaling_;
	this->y *= scaling_,
	this->z *= scaling_;
}

/*-----------------------------------------------------
 * @brief �O�ς��쐬����
 * @param[in]   vector_     ��������̃x�N�g��
 * @return      �쐬���ꂽ�O��
 *---------------------------------------------------*/
Vector3 Vector3::crossProduct(Vector3 vector_) const
{
	// TODO �߂�ǂ���������
	// ���z�͐V���� Vector3 �ɊO�ς̌��ʂ������A�Ԃ�
	return Vector3();
}



}    // namespace Math

