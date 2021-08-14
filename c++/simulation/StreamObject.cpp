
//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include "StreamObject.hpp"



/**--------------------------------------------------------
 * @brief      �}�j�s�����[�^ : endl �̎����B
 * @note        std::endl ���Ăяo���� flush ���g��Ȃ��Ă��悩�����̂ɁB
 *                  �G���[���N���邽�߁A���̂܂ܑΏ��B���g�� std::endl �ƈꏏ�B
 * @param[in]   streamObject    �傫�ȈӖ��͂Ȃ��B  operator << �Ƃ̌��ˍ���������
 * @return      ���ɈӖ��͂Ȃ��B
 *-------------------------------------------------------*/
so::StreamObject& so::endl(so::StreamObject& streamObject)
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
	fout << "\n" << std::flush;

	// �t�@�C�������
	fout.close();


	//-----------------------------------------------------
	//  �R���\�[���Ɋւ��鏈��
	//-----------------------------------------------------
	std::cout << "\n" << std::flush;

	return out;
}


