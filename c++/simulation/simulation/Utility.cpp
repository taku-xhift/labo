/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2009.11.08 21:13:39
 *
 * @version 0.01, Shishido Takuya, 2009.11.08 21:13:39
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include "Utility.hpp"
#include "GameManager.hpp"
#include "City.hpp"
#include "StreamObject.hpp"


using namespace so;

namespace Utility {


/**--------------------------------------------------------
 * @brief 初期化データ読み込み
 * @author  Takuya Shishido
 * @date    2009.11.08 21:13:39
 * @version 0.01, Shishido Takuya, 2009.11.08 21:13:39
 --------------------------------------------------------*/
// TODO
// 下記関数無いの文字列群をすべて実装。
// これを CityParameter と TeamParameter, UserData まで
// すべてに対応する予定。
// template を使うなどしてうまく回るようにしたいところですが。
	void readInitFile(NewMode::GameManager& manager)
{
	std::string fileName = manager.getCityConfigFileName();

	std::ifstream ifs(fileName.c_str());
	std::string data;
	NewMode::CityParameter cityParameter;    // これにデータをつっこむ

/*	while (getline(ifs, data)) {
		unsigned int equalPos = std::string part = data.find("=", 0);
		std::string dataName = data.substr(0, equalPos);
		if (dataName.empty() == true) {
			out << "要素の名前の無いデータがみつかりました。" << endl;
			out << "読み込みを中止します。" << endl;
			return;
		}

		std::string valueStr = data.stbstr(equalPos);
		int value = atoi(valueStr.c_str());
		if (value == 0) {
			out << "0 が読み込まれました。" << endl;
			out << "不正なデータがあった可能性があります。" << endl;
		}

		//assortmentData(cityParameter, dataName, value);

		// find_first_not_of(" ", 0) でスペース以外のデータの先頭を探し出し
		// その部分文字列を切り出し、それを atoi で数値化。
		// atoi == 0 なら文字列が渡されているので失敗
		// 数値になっていれば それを dataName で指定されたパラメータに対して初期化
		// end などの特定文字列をデータセットの末端の指定しにすれば
		// その段階で設定されたパラメータを gameManager のデータコンテナに
		// コピーして終了。

		// 上記の作業が eof まで続けて行われ、すべて読み込み終えたら終了

		out << data << endl;
	}
	*/
}


}


