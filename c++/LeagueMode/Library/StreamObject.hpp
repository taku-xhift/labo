
#ifndef SO_STREAMOBJECT_HPP_INCLUDED
#define SO_STREAMOBJECT_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------



#include <iostream>
#include <string>
#include <fstream>

namespace so {


/**
 * @brief ファイル出力とコンソール出力を同時に行う
 * @note    使い方は完全に iostream の std::cout と一緒。
 *              operator << のオーバーロードに関しては
 *              std::ostream に関して行うこと推奨。
 *              ファイルの方は (ﾟΔﾟ)ｼﾗﾈ
 *              ostream 系 << で処理できるならそれで可なはず。
 * @author  Takuya Shishido
 * @date    2009.10.29 02:40:00
 * @version 0.01, Shishido Takuya, 2009.10.29 02:40:00
 */
class StreamObject
{
public:

	/**----------------------------------------------------
	 * @brief  constructor
	 *---------------------------------------------------*/
	StreamObject();


	/**----------------------------------------------------
	 * @brief  マニピュレータを受け付けるためのメソッド
	 * @note   引数として受け取っているのは関数ポインタ。
	 * @param[in]   StreamObject&
	 *                  関数ポインタ。実行してほしい
	 *                  マニピュレータは operator << を使って
	 *                  後で作成する必要がある。
	 * @return  戻り値に特に意味はない。しかし operator << をつなげるために必要。
	 *---------------------------------------------------*/
	StreamObject& operator <<(StreamObject& (*pmanipulatorfunction)(StreamObject&))
	{
		return (*pmanipulatorfunction)(*this);
	}


public:

	/**----------------------------------------------------
	 * @brief     getter of fileName
	 * @return    Reference of std::string type.
	 *---------------------------------------------------*/
	std::string getFileName() const {
		return this->fileName;
	}


	/**----------------------------------------------------
	 * @brief        setter of fileName
	 * @param[in]    fileName_    A parameter to set.
	 *---------------------------------------------------*/
	void setFileName(std::string fileName_) {
		this->fileName = fileName_;
	}

private:

	std::string fileName;       //!< 出力先
};



/**----------------------------------------------------
 * @brief      実際に出力している部分
 * @note        実装自体は std::cout と std::ofstream を使っている。
 * @param[in]    streamObject   出力に使っているクラスデータ
 * @param[in]    data           出力する予定のデータ
 *---------------------------------------------------*/
template<class Type>
StreamObject& operator<<(StreamObject& streamObject_, const Type& data_)
{
	//-----------------------------------------------------
	//  ファイルに関する処理
	//-----------------------------------------------------
	std::ofstream fout( streamObject_.getFileName().c_str(), std::ios::app ); // test.txt を追記モードで開く

	// 開けなかった場合は終了
	if( fout.fail() )
	{
		std::cout << "file is nothing." << std::endl;
		return streamObject_;
	}

	// 出力
	fout << data_ << std::flush;

	// ファイルを閉じる
	fout.close();


	//-----------------------------------------------------
	//  コンソールに関する処理
	//-----------------------------------------------------
	std::cout << data_ << std::flush;

	return streamObject_;
}



static StreamObject out;    //!< グローバルオブジェクトとして存在。
                            //      名前空間には所属していますが。




/**----------------------------------------------------
 * @brief      マニピュレータ : endl の実装。
 * @note        std::endl を呼び出せば flush を使わなくてもよかったのに。
 *                  エラーが起きるため、このまま対処。中身は std::endl と一緒。
 * @param[in]   streamObject    大きな意味はない。  operator << との兼ね合いがこれ
 * @return      特に意味はない。
 *---------------------------------------------------*/
StreamObject& endl(StreamObject& streamObject);




}   // namespace so


#endif  // SO_STREAMOBJECT_HPP_INCLUDED

