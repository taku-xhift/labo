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

#ifdef MEMORYLEAKCHECK
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif
#endif

#endif

