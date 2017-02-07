/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date 2010.03.31 14:27:26
 *
 * @version 0.01, Shishido Takuya, 2010.03.31 14:27:26
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <limits>
#include <sstream>
#include <cassert>
#include "DataSet.hpp"
#include "Functor.hpp"


/**----------------------------------------------------
 * @brief     getter of DataCount
 * @return    Reference of std::pair<int, int> type.
 *---------------------------------------------------*/
void DataSet::sortDataCount() throw() {
	this->dataCount.sort(FunctorNumGreaterSort());
}



/**----------------------------------------------------
 * @brief 読み取ったデータを解析して dataCount に格納していく
 *---------------------------------------------------*/
void DataSet::addData(std::string race_, std::string data_) throw()
{
	// 人種に関しての調査
	int raceCheck = std::numeric_limits<int>::max();
	std::istringstream is(race_);
	is >> raceCheck;
	if (raceCheck == std::numeric_limits<int>::max()) {
		so::out << "人種読み取りにしっぱいしました。" << so::endl;
		assert(0);
		return;
	}

	// 取得したデータを int に変換
	int integer = std::numeric_limits<int>::max();
	is.str("");
	is.clear();
	is.str(data_);
	is >> integer;

	// 読み取れたかの確認
	if (integer == std::numeric_limits<int>::max()) {
		if (data_ == "") {
			// 何も入っていない可能性はおおいにあるので
		} else {
			// 問題大有り。なにか読み取りに失敗する構造になっているに違いない
			so::out << data_ << so::endl;
			assert(false);
		}
	}

	// フル検索
	bool checker = false;
	for (std::list<Data>::iterator ite = this->dataCount.begin(); ite != this->dataCount.end(); ++ite) {
		if (ite->race == raceCheck && ite->ID == integer) {
			++(ite->num);
			checker = true;
			break;
		}
	}

	// 見つからなかった場合
	if (checker == false) {
		this->dataCount.push_back(Data(raceCheck, integer, 1));
	}
}



