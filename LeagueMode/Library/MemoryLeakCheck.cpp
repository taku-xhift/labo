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
 * @date 2010.04.19 17:37:14
 *
 * @version 0.01, Shishido Takuya, 2010.04.19 17:37:14
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/MemoryLeakCheck.hpp"


#ifdef _MSC_VER
#ifdef MEMORYLEAKCHECK


/**----------------------------------------------------
 * @brief リークチェックのスタートの関数。
 * @note        Visual Stadio の機能を利用しているので、
 *                  マクロを使って診断して置き換え。
 *---------------------------------------------------*/
void leakCheckStart() {
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}


/**----------------------------------------------------
 * @brief メモリ取得時にブレーク
 * @note        breakNumber_ 回目のメモリ確保時に
 *                   break point が発生する。
 * @note        複数個仕掛けてもどうやら最後の１個しか反応しないっぽい。
 *                  １個消費後ならどうなのか？
 * @note        Visual Stadio の機能を使用しているので
 *                  マクロを使って診断して置き換え。
 * @param[in]   breakNumber_    何回目のメモリ確保か？
 *---------------------------------------------------*/
void setBreakAlloc(int breakNumber_) {
#ifdef _MSC_VER
	_CrtSetBreakAlloc(breakNumber_);    // num は取得された番号
#endif
}


/**----------------------------------------------------
 * @brief リークチェックの終了用の関数。
 * @note        Visual Stdio の機能を利用しているので、
 *                  マクロを使って判断して置き換え。
 * @note        この関数を通過する時点でリークしているものがあれば
 *                  アドレスとリーク容量が出力用画面に出力される。
 *                  ただし、グローバル変数などもリークとみなされるので
 *                  そこら辺の注意は必要。
 *---------------------------------------------------*/
void leakCheckEnd() {
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
}



#endif  // #ifdef MEMORYLEAKCHECK
#endif  // #ifdef _MSC_VER

