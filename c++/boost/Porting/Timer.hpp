/**
 * @file
 * @brief 時間測定クラス
 *
 * @author Takuya Shishido
 * @date   2011.02.17 18:14:56
 *
 * @version 0.01, Shishido Takuya, 2011.02.17 18:14:56
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED


//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include <string>
#include <map>
#include <ctime>
#include "NonCopyable.hpp"



//! \brief 時間測定クラス
//! \note   オブジェクトが生成されてから破棄されるまでの時間を測定
//! \note   static 関数 とメンバ関数を使い分けるようにする
class Timer
	: private NonCopyable
{
public:

	typedef std::map<std::string, float> TimerList;     //!< 別名保存


	//! \brief constructor
	//! \param[in]  tag     測定する時間のタグ。過去に作ったことがないタグでもいい。
	explicit Timer(const std::string& tag) throw()
		: tag_(tag)
	{
		this->start_ = std::clock();
	}


	//! \brief destructor
	//! \note   破棄される時に測定終了し、保存
	~Timer() {
		std::map<std::string, float>::iterator ite = timerList_.find(this->tag_);
		// tag が存在していなければ初期化しておく
		if (ite == timerList_.end()) {
			timerList_[this->tag_] = .0f;
		}
		timerList_[this->tag_] += static_cast<float>(std::clock() - this->start_)/CLOCKS_PER_SEC;
	}


	//! \brief オブジェクトが生成されてからの時間取得
	float elapsed() const throw()           { return static_cast<float>(std::clock() - this->start_); }


	//! \brief 過去に測定したものの合計を取得する
	//! \param[in]  tag     測定に利用したタグ
	//! \except     UnFoundError    tag が見つからなかった場合
	static float elapsed(const std::string& tag) throw(UnFoundError) {
		TimerList::iterator ite = timerList_.find(tag);
		if (ite != timerList_.end()) {
			return ite->second;
		} else {
			throw UnFoundError();
		}
	}


	//! \brief オブジェクトのタイマーをリセットする
	void restart() throw() { this->start_ = std::clock(); }


	//! \brief 過去に測定したタイマーをリセットする
	//! \param[in]  tag     リセットするタグ
	//! \except     UnFoundError    tag が見つからなかった
	static void restart(std::string tag) throw(UnFoundError) {
		TimerList::iterator ite = timerList_.find(tag);
		if (ite != timerList_.end()) {
			ite->second = .0f;
		} else {
			throw UnFoundError();
		}
	}


private:

	std::clock_t    start_;         //!< オブジェクトが生成された時間
	std::string     tag_;           //!< 自分が所属するタグ

	static TimerList timerList_;    //!< tag で管理された時間のリスト。
};

Timer::TimerList Timer::timerList_;



//-------------------------------------------------------------------------------------------------
//          使用例
//-------------------------------------------------------------------------------------------------
//
//
//#include <iostream>
//#include <vector>
//
//int main()
//{
//	std::vector<int> container;
//
//	{
//		Timer timer("insert");
//		for (int i = 0; i < 100000; ++i) {
//			container.push_back(i);
//		}
//	}
//	{
//		Timer timer("print");
//		for (std::vector<int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
//			std::cout << *ite << "\n";
//		}
//		std::cout << std::endl;
//	}
//
//	std::cout << "insert = " << Timer::elapsed("insert") << std::endl;
//	std::cout << "print = " << Timer::elapsed("print") << std::endl;
//}
//
//-------------------------------------------------------------------------------------------------


#endif

