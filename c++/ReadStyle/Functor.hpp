/**
 * @file
 * @brief ファンクタだけを並べるファイル
 *
 * @author Takuya Shishido
 * @date   2010.03.31 14:31:16
 *
 * @version 0.01, Shishido Takuya, 2010.03.31 14:31:16
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

/**
 * @brief list で std::pair の要素を second の大きい順に並び替える
 * @note    まとめるデータはメンバにあるもので全て。
 * @author  Takuya Shishido
 * @date    2010.03.30 15:26:25
 * @version 0.01, Shishido Takuya, 2010.03.30 15:26:25
 */
class FunctorSecondGreaterSort
{
public:

	FunctorSecondGreaterSort() { }

	template<typename Type>
	bool operator() (Type lhs_, Type rhs_) {
		return lhs_.second > rhs_.second;
	}
};

/**
 * @brief list で Data の要素を num の大きい順に並び替える
 * @note    まとめるデータはメンバにあるもので全て。
 * @author  Takuya Shishido
 * @date    2010.03.31 15:35:25
 * @version 0.01, Shishido Takuya, 2010.03.31 15:35:25
 */
class FunctorNumGreaterSort
{
public:

	FunctorNumGreaterSort() { }

	template<typename Type>
	bool operator() (Type lhs_, Type rhs_) {
		// 人種最優先で並び替え
		// 人種は小さい順
		if (lhs_.race < rhs_.race) {
			return true;
		} else if (lhs_.race > rhs_.race) {
			return false;
		}

		// 人種が一緒であればその ID の数で並び替え
		// num は 多い順
		return lhs_.num > rhs_.num;
	}
};



/**
 * @brief list で std::pair の要素の first から探し出す
 *
 * @author  Takuya Shishido
 * @date    2010.03.30 16:02:25
 * @version 0.01, Shishido Takuya, 2010.03.30 2010.03.30 15:26:25
 */
class FunctorFind
{
public:

	FunctorFind(int target_) : target(target_) { }

	template<typename Type>
	bool operator() (Type data_) {
		return data_.first == this->target;
	}

	int target;
};




/**
 * @brief list で std::pair の要素の first から探し出す
 *
 * @author  Takuya Shishido
 * @date    2010.03.30 16:02:25
 * @version 0.01, Shishido Takuya, 2010.03.30 2010.03.30 15:26:25
 */
class FunctorSortDataSet
{
public:

	FunctorSortDataSet() { }

	template<typename Type>
	void operator() (Type& data_) {
		data_.sortDataCount();
	}
};




#endif

