/**
 * @file
 * @brief stream 管理モジュール
 *
 * @author Takuya Shishido
 * @date   2009.10.29 02:40:00
 *
 * @version 0.01, Shishido Takuya, 2009.10.29 02:40:00
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include "StreamObject.hpp"

// メモリリークのチェックを行うライブラリを入れていれば。
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
	// ファイル内容の初期化
	std::ofstream fileout(this->fileName.c_str());

	if (!fileout) {
		//エラー処理を記述
		std::cout << this->fileName.c_str() << "cannot open." << std::endl;
	}

	// ファイル処理
	fileout.close();
}


/**--------------------------------------------------------
 * @brief      マニピュレータ : endl の実装。
 * @note        std::endl を呼び出せば flush を使わなくてもよかったのに。
 *                  エラーが起きるため、このまま対処。中身は std::endl と一緒。
 * @param[in]   streamObject    大きな意味はない。  operator << との兼ね合いがこれ
 * @return      特に意味はない。
 *-------------------------------------------------------*/
so::StreamObject& so::endl(so::StreamObject& streamObject_)
{
	//-----------------------------------------------------
	//  ファイルに関する処理
	//-----------------------------------------------------
	std::ofstream fout( streamObject_.getFileName().c_str(), std::ios::app );

	// 開けなかった場合は終了
	if(fout.fail()) {
		std::cout << streamObject_.getFileName().c_str() << "cannot open." << std::endl;
		return streamObject_;
	}

	// 出力
	fout << "\n" << std::flush;

	// ファイルを閉じる
	fout.close();


	//-----------------------------------------------------
	//  コンソールに関する処理
	//-----------------------------------------------------
	std::cout << "\n" << std::flush;

	return streamObject_;
}


