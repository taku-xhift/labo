
//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include "StreamObject.hpp"

// ���������[�N�̃`�F�b�N���s�����C�u���������Ă���΁B
#ifdef MEMORYLEAKCHECK
#include "MemoryLeakCheck.hpp"
#endif

//---------------------------------------------------------
//  define
//---------------------------------------------------------
namespace {
	const char* logFileName = "log.txt";
}


/**----------------------------------------------------
 * @brief  constructor
 *---------------------------------------------------*/
so::StreamObject::StreamObject()
	: fileName(logFileName)
{
	// �t�@�C�����e�̏�����
	std::ofstream fileout(this->fileName.c_str());

	if (!fileout) {
		//�G���[�������L�q
		std::cout << this->fileName.c_str() << "cannot open." << std::endl;
	}

	// �t�@�C������
	fileout.close();
}


/**--------------------------------------------------------
 * @brief      �}�j�s�����[�^ : endl �̎����B
 * @note        std::endl ���Ăяo���� flush ���g��Ȃ��Ă��悩�����̂ɁB
 *                  �G���[���N���邽�߁A���̂܂ܑΏ��B���g�� std::endl �ƈꏏ�B
 * @param[in]   streamObject    �傫�ȈӖ��͂Ȃ��B  operator << �Ƃ̌��ˍ���������
 * @return      ���ɈӖ��͂Ȃ��B
 *-------------------------------------------------------*/
so::StreamObject& so::endl(so::StreamObject& streamObject_)
{
	//-----------------------------------------------------
	//  �t�@�C���Ɋւ��鏈��
	//-----------------------------------------------------
	std::ofstream fout( streamObject_.getFileName().c_str(), std::ios::app );

	// �J���Ȃ������ꍇ�͏I��
	if(fout.fail()) {
		std::cout << streamObject_.getFileName().c_str() << "cannot open." << std::endl;
		return streamObject_;
	}

	// �o��
	fout << "\n" << std::flush;

	// �t�@�C�������
	fout.close();


	//-----------------------------------------------------
	//  �R���\�[���Ɋւ��鏈��
	//-----------------------------------------------------
	std::cout << "\n" << std::flush;

	return streamObject_;
}


