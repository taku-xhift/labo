/**
 * @file
 * @brief stream 管理モジュール
 *
 * @author Takuya Shishido
 * @date   2009.10.29 02:40:00
 *
 * @version 0.01, Shishido Takuya, 2009.10.29 02:40:00
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include "StreamObject.hpp"



/**--------------------------------------------------------
 * @brief      マニピュレータ : endl の実装。
 * @note        std::endl を呼び出せば flush を使わなくてもよかったのに。
 *                  エラーが起きるため、このまま対処。中身は std::endl と一緒。
 * @param[in]   streamObject    大きな意味はない。  operator << との兼ね合いがこれ
 * @return      特に意味はない。
 *-------------------------------------------------------*/
so::StreamObject& so::endl(so::StreamObject& streamObject)
{
	//-----------------------------------------------------
	//  ファイルに関する処理
	//-----------------------------------------------------
	std::ofstream fout( streamObject.getFilename().c_str(), std::ios::app ); // test.txt を追記モードで開く

	// 開けなかった場合は終了
	if( fout.fail() )
	{
		std::cout << "file is nothing." << std::endl;
		return streamObject;
	}

	// 出力
	fout << "\n" << std::flush;

	// ファイルを閉じる
	fout.close();


	//-----------------------------------------------------
	//  コンソールに関する処理
	//-----------------------------------------------------
	std::cout << "\n" << std::flush;

	return out;
}


