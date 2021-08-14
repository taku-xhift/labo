/**
 * @file
 * @brief ���������[�N�̃`�F�b�N���������t�@�C���ŃC���N���[�h������́B
 *          �`�F�b�N���邽�߂ɂ� MEMORYLEAKCHECK �� define ���ăv���O�����𓮂������ƁB
 * @note    entry Point �ɂ�    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 *                              _CrtDumpMemoryLeaks();
 *              ���g�p���邱�ƂŃ������̃��[�N���Ȃ����`�F�b�N����B
 *              �܂��Ac �̃`�F�b�N���@��������Ȃ��������A���[�N�̏�񂪏o�͂���Ă����ʂ�
 *              ���ԖڂɎ擾���ꂽ�����킩��̂�
 *                  _CrtSetBreakAlloc( num );    // num �͎擾���ꂽ�ԍ�
 *              ���g�����ƂŃu���[�N�|�C���g�����o�����Ƃ��o����B
 *              entryPoint �� _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 *              �̂�����������Ŏg���Ƃ����B
 *              �}���`�X���b�h������Ă���ǂ������ł��傤�ˁH
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"


#ifdef _MSC_VER
#ifdef MEMORYLEAKCHECK


/**----------------------------------------------------
 * @brief ���[�N�`�F�b�N�̃X�^�[�g�̊֐��B
 * @note        Visual Stadio �̋@�\�𗘗p���Ă���̂ŁA
 *                  �}�N�����g���Đf�f���Ēu�������B
 *---------------------------------------------------*/
void leakCheckStart() {
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}


/**----------------------------------------------------
 * @brief �������擾���Ƀu���[�N
 * @note        breakNumber_ ��ڂ̃������m�ێ���
 *                   break point ����������B
 * @note        �����d�|���Ă��ǂ����Ō�̂P�����������Ȃ����ۂ��B
 *                  �P�����Ȃ�ǂ��Ȃ̂��H
 * @note        Visual Stadio �̋@�\���g�p���Ă���̂�
 *                  �}�N�����g���Đf�f���Ēu�������B
 * @param[in]   breakNumber_    ����ڂ̃������m�ۂ��H
 *---------------------------------------------------*/
void setBreakAlloc(int breakNumber_) {
#ifdef _MSC_VER
	_CrtSetBreakAlloc(breakNumber_);    // num �͎擾���ꂽ�ԍ�
#endif
}


/**----------------------------------------------------
 * @brief ���[�N�`�F�b�N�̏I���p�̊֐��B
 * @note        Visual Stdio �̋@�\�𗘗p���Ă���̂ŁA
 *                  �}�N�����g���Ĕ��f���Ēu�������B
 * @note        ���̊֐���ʉ߂��鎞�_�Ń��[�N���Ă�����̂������
 *                  �A�h���X�ƃ��[�N�e�ʂ��o�͗p��ʂɏo�͂����B
 *                  �������A�O���[�o���ϐ��Ȃǂ����[�N�Ƃ݂Ȃ����̂�
 *                  ������ӂ̒��ӂ͕K�v�B
 *---------------------------------------------------*/
void leakCheckEnd() {
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
}



#endif  // #ifdef MEMORYLEAKCHECK
#endif  // #ifdef _MSC_VER

