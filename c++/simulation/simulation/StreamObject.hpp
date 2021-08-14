
#ifndef SO_STREAMOBJECT_HPP_INCLUDED
#define SO_STREAMOBJECT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------



#include <iostream>
#include <string>
#include <fstream>

namespace so {


/**
 * @brief �t�@�C���o�͂ƃR���\�[���o�͂𓯎��ɍs��
 * @note    �g�����͊��S�� iostream �� std::cout �ƈꏏ�B
 *              operator << �̃I�[�o�[���[�h�Ɋւ��Ă�
 *              std::ostream �Ɋւ��čs�����Ɛ����B
 *              �t�@�C���̕��� (߃��)���
 *              ostream �n << �ŏ����ł���Ȃ炻��ŉȂ͂��B
 * @author  Takuya Shishido
 * @date    2009.10.29 02:40:00
 * @version 0.01, Shishido Takuya, 2009.10.29 02:40:00
 */
class StreamObject
{
public:

	/**----------------------------------------------------
	 * @brief  constructor
	 *---------------------------------------------------*/
	StreamObject()
		: fileName("report.txt")
	{
		// �t�@�C�����e�̏�����
		std::ofstream fileout(this->fileName.c_str());

		if (!fileout) {
			//�G���[�������L�q
			std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		}

		// �t�@�C������
		fileout.close();
	}


	/**----------------------------------------------------
	 * @brief  �}�j�s�����[�^���󂯕t���邽�߂̃��\�b�h
	 * @note   �����Ƃ��Ď󂯎���Ă���̂͊֐��|�C���^�B
	 * @param[in]   StreamObject&
	 *                  �֐��|�C���^�B���s���Ăق���
	 *                  �}�j�s�����[�^�� operator << ���g����
	 *                  ��ō쐬����K�v������B
	 * @return  �߂�l�ɓ��ɈӖ��͂Ȃ��B������ operator << ���Ȃ���K�v������B
	 *---------------------------------------------------*/
	StreamObject& operator <<(StreamObject& (*pmanipulatorfunction)(StreamObject&))
	{
		return (*pmanipulatorfunction)(*this);
	}


public:

	/**----------------------------------------------------
	 * @brief     getter of fileName
	 * @return    Reference of std::string type.
	 *---------------------------------------------------*/
	std::string getFilename() const {
		return this->fileName;
	}


	/**----------------------------------------------------
	 * @brief        setter of fileName
	 * @param[in]    fileName_    A parameter to set.
	 *---------------------------------------------------*/
	void setFilename(std::string fileName_) {
		this->fileName = fileName_;
	}

private:

	std::string fileName;       //!< �o�͐�
};



/**----------------------------------------------------
 * @brief      ���ۂɏo�͂��Ă��镔��
 * @note        �������̂� std::cout �� std::ofstream ���g���Ă���B
 * @param[in]    streamObject   �o�͂Ɏg���Ă���N���X�f�[�^
 * @param[in]    data           �o�͂���\��̃f�[�^
 *---------------------------------------------------*/
template<class Type>
StreamObject& operator<<(StreamObject& streamObject, const Type& data)
{
	//-----------------------------------------------------
	//  �t�@�C���Ɋւ��鏈��
	//-----------------------------------------------------
	std::ofstream fout( streamObject.getFilename().c_str(), std::ios::app ); // test.txt ��ǋL���[�h�ŊJ��

	// �J���Ȃ������ꍇ�͏I��
	if( fout.fail() )
	{
		std::cout << "file is nothing." << std::endl;
		return streamObject;
	}

	// �o��
	fout << data << std::flush;

	// �t�@�C�������
	fout.close();


	//-----------------------------------------------------
	//  �R���\�[���Ɋւ��鏈��
	//-----------------------------------------------------
	std::cout << data << std::flush;

	return streamObject;
}



static StreamObject out;    //!< �O���[�o���I�u�W�F�N�g�Ƃ��đ��݁B
                            //      ���O��Ԃɂ͏������Ă��܂����B




/**----------------------------------------------------
 * @brief      �}�j�s�����[�^ : endl �̎����B
 * @note        std::endl ���Ăяo���� flush ���g��Ȃ��Ă��悩�����̂ɁB
 *                  �G���[���N���邽�߁A���̂܂ܑΏ��B���g�� std::endl �ƈꏏ�B
 * @param[in]   streamObject    �傫�ȈӖ��͂Ȃ��B  operator << �Ƃ̌��ˍ���������
 * @return      ���ɈӖ��͂Ȃ��B
 *---------------------------------------------------*/
StreamObject& endl(StreamObject& streamObject);




}   // namespace so


#endif  // SO_STREAMOBJECT_HPP_INCLUDED

