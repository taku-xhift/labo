/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.03.31 14:27:26
 *
 * @version 0.01, Shishido Takuya, 2010.03.31 14:27:26
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef DATASET_HPP_INCLUDED
#define DATASET_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <list>
#include "StreamObject.hpp"



struct Data
{
	Data(int race_, int ID_, int num_) : race(race_), ID(ID_), num(num_) {}

	int race;       //!< 人種
	int ID;         //!< 番号
	int num;        //!< 数
};


/**
 * @brief データを一まとめにしたもの。
 * @note    まとめるデータはメンバにあるもので全て。
 * @author  Takuya Shishido
 * @date    2010.03.30 11:11:25
 * @version 0.01, Shishido Takuya, 2010.03.30 11:11:25
 */
class DataSet
{
public:


	/**----------------------------------------------------
	 * @brief     getter and setter
	 * @return    Reference of std::string type.
	 *---------------------------------------------------*/
	const std::string& getDataName() const throw() { return this->dataName; }
	void setDataName(const std::string& dataName_) throw() { this->dataName = dataName_; }
	const std::list<Data>::const_iterator getDataCountIterator() const { return this->dataCount.begin(); }
	const std::list<Data>::const_iterator getDataCountIteratorEnd() const { return this->dataCount.end(); }


	/**----------------------------------------------------
	 * @brief     getter of DataCount
	 * @return    Reference of std::pair<int, int> type.
	 *---------------------------------------------------*/
	void sortDataCount() throw();


	/**----------------------------------------------------
	 * @brief 読み取ったデータを解析して dataCount に格納していく
	 *---------------------------------------------------*/
	void addData(std::string race_, std::string data_) throw();


	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os               ストリームオブジェクト
	 * @param[in]  cityParameter    出力オブジェクト
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const DataSet& dataSet_)
	{
		os << "dataName: " << dataSet_.dataName << std::endl;
		os << "具体的なデータ" << std::endl;
		for (std::list<Data>::const_iterator ite = dataSet_.dataCount.begin(); ite != dataSet_.dataCount.end(); ++ite) {
			os << "race = " << ite->race << ", ID = " << ite->ID << ", number = " << ite->num << std::endl;
		}
		return os;
	}


private:

	std::string         dataName;         //!< データの名前
	std::list<Data>     dataCount;        //!< データのカウント。１つめが種類, ２つめがその数
};






#endif

