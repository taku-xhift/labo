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

#ifndef MEMORYLEAKCHECK_HPP_INCLUDED
#define MEMORYLEAKCHECK_HPP_INCLUDED

//-----------------------------------------------------
//  define
//-----------------------------------------------------


#ifdef _MSC_VER
#ifdef MEMORYLEAKCHECK
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#if defined (_DEBUG)
#define New new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define Malloc(p1)  _malloc_dbg(p1,_NORMAL_BLOCK,__FILE__,__LINE__)
#define Calloc(p1)  _malloc_dbg(p1,_NORMAL_BLOCK,__FILE__,__LINE__)
#else
#define New new
#define Malloc(p1)  malloc(p1)
#define Calloc(p1)  calloc(p1)
#endif  // #if defined (_DEBUG)


#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief ���[�N�`�F�b�N�̃X�^�[�g�̊֐��B
 * @note        Visual Stadio �̋@�\�𗘗p���Ă���̂ŁA
 *                  �}�N�����g���Đf�f���Ēu�������B
 *---------------------------------------------------*/
void leakCheckStart();



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
void setBreakAlloc(int breakNumber_);


/**----------------------------------------------------
 * @brief ���[�N�`�F�b�N�̏I���p�̊֐��B
 * @note        Visual Stdio �̋@�\�𗘗p���Ă���̂ŁA
 *                  �}�N�����g���Ĕ��f���Ēu�������B
 * @note        ���̊֐���ʉ߂��鎞�_�Ń��[�N���Ă�����̂������
 *                  �A�h���X�ƃ��[�N�e�ʂ��o�͗p��ʂɏo�͂����B
 *                  �������A�O���[�o���ϐ��Ȃǂ����[�N�Ƃ݂Ȃ����̂�
 *                  ������ӂ̒��ӂ͕K�v�B
 *---------------------------------------------------*/
void leakCheckEnd();


#ifdef __cplusplus
}
#endif


#endif  // #ifdef MEMORYLEAKCHECK
#endif  // #ifdef _MSC_VER
#endif  // #ifndef MEMORYLEAKCHECK_HPP_INCLUDED
