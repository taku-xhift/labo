/**
 * @file
 * @brief メモリリークのチェックをしたいファイルでインクルードするもの。
 *          チェックするためには MEMORYLEAKCHECK を define してプログラムを動かすこと。
 * @note    entry Point にて    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 *                              _CrtDumpMemoryLeaks();
 *              を使用することでメモリのリークがないかチェックする。
 *              また、c のチェック方法が見つからなかったが、リークの情報が出力されている画面で
 *              何番目に取得されたかがわかるので
 *                  _CrtSetBreakAlloc( num );    // num は取得された番号
 *              を使うことでブレークポイントを作り出すことが出来る。
 *              entryPoint で _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 *              のすぐ下あたりで使うといい。
 *              マルチスレッド化されてたらどうするんでしょうね？
 *
 * @author Takuya Shishido
 * @date   2010.04.07 11:23:19
 *
 * @version 0.01, Shishido Takuya, 2010.04.07 11:23:19
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
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

