/**
 * @file
 * @brief 選手容姿を読み込む
 *
 * @author Takuya Shishido
 * @date 2010.03.30 11:09:08
 *
 * @version 0.01, Shishido Takuya, 2010.03.30 11:09:08
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "StreamObject.hpp"
#include "DataSet.hpp"
#include "Functor.hpp"


//---------------------------------------------------------
//  define
//---------------------------------------------------------
namespace {
	const std::string readFileName = "style.csv";       //!< 読み込むファイルの名前
	const std::string resultFileName = "result.txt";    //!< 書き込む結果データのファイル名
	const int invalidNum = 11;      //!< データの中でも解析の必要無いデータの先頭からの数
}


//---------------------------------------------------------
//  declaration
//---------------------------------------------------------
class DataSet;


//---------------------------------------------------------
//  prototype
//---------------------------------------------------------
void readFiles(std::string fileName_, std::vector<DataSet> dataContainer_) throw();
void writeFiles(std::string fileName_) throw();
template<typename Type> std::vector<Type> eraceVector(const std::vector<Type>& container_, int num_) throw();





//---------------------------------------------------------
//  entry point
//---------------------------------------------------------
int main()
{
	std::vector<DataSet> dataContainer;

	readFiles(readFileName, dataContainer);

	return 0;
}



/**-------------------------------------------------------------
 * @breif ファイル読込み関数。
 *          csv ファイル読込みをし、分析結果をファイルに出力までする。
 * @param[in]   fileName_   読み込みファイル
 *-------------------------------------------------------------*/
void readFiles(std::string fineName_, std::vector<DataSet> dataContainer_) throw()
{
	std::ifstream ifs(fineName_.c_str());
	std::string fileData;

	// ファイルが読み込めたかチェックを行う
	assert(ifs.good());

	// １行目読込み
	std::getline(ifs, fileData);

	std::vector<std::string> dataName;
	boost::algorithm::split(dataName, fileData, boost::is_any_of(","));


	// サイズ確保、名前セット
	dataContainer_.resize(dataName.size());
	for (unsigned int i = 0; i < dataName.size(); ++i) {
		dataContainer_.at(i).setDataName(dataName.at(i));
	}


	//-----------------------------------------------------
	//  ファイルの本格的な読込み
	//      ただし、人種(スキンカラー)情報が最先頭に来ていないといけない。
	//      それ以外の場所にあるのであれば addData の第一引数に
	//      適切な番号のデータを渡すようにしてください。
	//      もしくは excel の段階で並び替えるとか。
	//      いちいち対応するの面倒なんで。
	//-----------------------------------------------------
	int counter = 0;    // 心の安定用。フリーズ時間が長いとドキドキするので
	while (std::getline(ifs, fileData)) {
		boost::algorithm::split(dataName, fileData, boost::is_any_of(","));
		// 例えば 鼻 を読み取っている場合は dataName の 鼻 にあたる部分を解析させる
		for (unsigned int i = 0; i < dataContainer_.size(); ++i) {
			dataContainer_.at(i).addData(dataName.at(0), dataName.at(i));
		}
		++counter;
		std::cout << "counter = " << counter << std::endl;
	}

	// ソート
	std::for_each(dataContainer_.begin(), dataContainer_.end(), FunctorSortDataSet());

	// 結果を出力する
	for (std::vector<DataSet>::iterator ite = dataContainer_.begin(); ite != dataContainer_.end(); ++ite) {
		so::out << (*ite) << so::endl;
	}
}



/**-------------------------------------------------------------
 * @breif ファイル書き込み関数。
 *          csv ファイル読込みをし、分析結果をファイルに出力までする。
 * @param[in]   fileName_   読み込みファイル
 *-------------------------------------------------------------*/
void writeFiles(std::string fineName_) throw()
{

}




/**-------------------------------------------------------------
 * @breif vector 型のデータの先頭から num_ 分だけ消去する
 * @param[in]   num_    消去する数
 *-------------------------------------------------------------*/
template<typename Type>
std::vector<Type> eraceVector(const std::vector<Type>& container_, int num_) throw()
{
	// オリジナルデータからコピー
	std::vector<Type> data = container_;

	// イテレータを指定された分進めて消去
	std::vector<Type>::iterator ite = data.begin();
	std::advance(ite, num_);
	data.erase(data.begin(), ite);

	return data;
}

