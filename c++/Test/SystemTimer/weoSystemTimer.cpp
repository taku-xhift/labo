/**
 * @file  SystemTimer.cpp
 * @brief タイマー管理クラス
 * @note    スレッドセーフ
 *
 * @author Takuya Shishido
 * @date   2011.06.15 10:08:37
 *
 * @version 0.01, Shishido Takuya, 2011.06.15 10:08:37
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include <iostream>
#include <bitset>
#include <limits>
#include <windows.h>
#include <vector>
#include <stdexcept>
#include <cassert>
//#include "weDebug.h"
#include "weoSystemTimer.h"
#include "weoFlowMutex.h"
//#include "weoFlowDefine.h"



namespace {

	typedef pm_mode::WindowsMutex TimerMutex;


	/****************************************************************
	 * @brief タイマーの状態管理用
	 ***************************************************************/
	enum TimerKind {
		TIMERKIND_REMAIN_TIME,          //!< 制限時間式
		TIMERKIND_DEADLINE_TIME,        //!< 締切り式
		TIMERKIND_MAX,
	};


	/****************************************************************
	 * @brief タイマーのデータを扱うクラス
	 ***************************************************************/
	struct RemainTimeData {
		clock_t remainTime_;            //!< 残り時間
		clock_t registryRemainTIme_;    //!< 前回登録されたリセット時間
	};

	struct SystemTimerData
	{
		SystemTimerData() throw()
			: state_(SYSTEMTIMERSTATE_UNINITIALIZE)
			, kind_(TIMERKIND_MAX)
			, callback_(NULL)
			//, deadline_(systemTimerInfinitTime)      warning C4608 : remainTime_ によって初期化済み、対策でコメントアウト
		{
			// union なのでコンストラクタが定義できない
			this->remainTime_.remainTime_         = systemTimerInfinitTime;
			this->remainTime_.registryRemainTIme_ = systemTimerInfinitTime;
		}


		SystemTimerState            state_;         //!< 状態管理データ
		TimerKind                   kind_;          //!< タイマーの種類
		union {
			RemainTimeData          remainTime_;    //!< 残り時間
			ServerTime              deadline_;      //!< 締切時間
		};
		void (*callback_)(void);                    //!< 登録されたコールバック関数
	};


	struct SystemTimer
	{
		bool                isFirstTimeOfSetServerTime_;    //!< サーバ時間のセットが初めてかどうか
		clock_t             nowTime_;                       //!< 今フレームの時間
		clock_t             preTime_;                       //!< 前フレームの時間
		clock_t             totalTimeFromPreSetServerTime_; //!< サーバ時間からの経過時間。マイフレーム加算される。
		ServerTime          serverTime_;                    //!< サーバ時刻。deadline 用。
		std::vector<SystemTimerData> timerList_;            //!< データ管理用データ。TIMERCATEGORY_MAX サイズの配列。


		SystemTimer() throw()
			: isFirstTimeOfSetServerTime_(false)
			, nowTime_(0)
			, preTime_(0)
			, totalTimeFromPreSetServerTime_(0)
			, serverTime_(time(NULL))
		{
		}

		~SystemTimer() throw() {}

		ServerTime getSynchronizedNowTime() const throw() {
			return this->serverTime_ + this->totalTimeFromPreSetServerTime_/CLOCKS_PER_SEC;
		}

	};

	SystemTimer*    systemTimer = NULL;
	TimerMutex      mutex_;
}


/****************************************************************
 * @brief サーバの時間の setter
 * @param[in]   serverTime  サーバの時間。型をどうするのか不明
 ***************************************************************/
SystemTimerCreationError weoResetServerTime(ServerTime serverTime) throw() {
	if (systemTimer == NULL) { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	if (systemTimer->isFirstTimeOfSetServerTime_ == false) {
		// ２回目以降の更新では前回のサーバ時間から今回のサーバ時間分
		// 経過時間を減らす必要がある
		const ServerTime nowTime = systemTimer->getSynchronizedNowTime();

		const weInt diff = static_cast<weInt>(difftime(nowTime, serverTime));
		systemTimer->nowTime_ -= diff;
		systemTimer->totalTimeFromPreSetServerTime_ = 0;
	}
	systemTimer->isFirstTimeOfSetServerTime_ = false;
	systemTimer->serverTime_ = serverTime;

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief タイマーの初期化
 ***************************************************************/
SystemTimerCreationError weoCreateTimerDataSystemTimer() throw() {
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	try {
		// タイマーのインスタンス化とメモリ確保エラーの処理
		if (systemTimer == NULL) { systemTimer = NEW SystemTimer(); } 
		if (systemTimer == NULL) { throw std::bad_alloc(ExceptionMessage("")); }
	} catch (std::bad_alloc& e) {
		weString const log = e.what();
		WE_PRINTF("%s\n", log);
		WE_ASSERT(false, log);
		log;
		return SYSTEMTIMERCREATIONERROR_ALLOCATE;
	}

	try {
		// タイマーリストの作成とメモリ確保エラーの処理
		systemTimer->timerList_.resize(TIMERCATEGORY_MAX);
		if (systemTimer->timerList_.size() != TIMERCATEGORY_MAX) {
			throw std::bad_alloc(ExceptionMessage(""));
		}
	} catch (std::bad_alloc& e) {
		weString const log = e.what();
		WE_PRINTF("%s\n", log);
		WE_ASSERT(false, log);
		log;
		return SYSTEMTIMERCREATIONERROR_ALLOCATE;
	}

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief タイマーの破棄
 ***************************************************************/
void weoDestroyTimerDataSystemTimer() throw() {
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	SAFE_DELETE(systemTimer);
}


/****************************************************************
 * @brief タイマーのアップデータ
 ***************************************************************/
SystemTimerCreationError weoUpdaterSystemTimer() throw() {
	if (systemTimer == NULL) { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }

	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	// 現在の時刻の割り出し。
	// 割り出し方法は、サーバからセットされた時間に、経過時間を足す
	systemTimer->preTime_ = systemTimer->nowTime_;
	systemTimer->nowTime_ = clock();
	const clock_t elapsedTime = systemTimer->nowTime_ - systemTimer->preTime_;
	systemTimer->totalTimeFromPreSetServerTime_ += elapsedTime;
	const ServerTime nowTime = systemTimer->serverTime_ + systemTimer->totalTimeFromPreSetServerTime_/CLOCKS_PER_SEC;

	// 締切りが来ているものがあるかチェック
	// 残り時間も減らす
	for (weInt i = 0; i < TIMERCATEGORY_MAX; ++i) {
		// カウントダウンする気がないものは次にまわす
		if (systemTimer->timerList_.at(i).state_ != SYSTEMTIMERSTATE_COUNTDOWN) { continue; }

		// 残り時間でカウントダウンしている時
		if (systemTimer->timerList_.at(i).kind_ == TIMERKIND_REMAIN_TIME) {
			// 無限時間の設定だった場合には時間を減らさない
			if (systemTimer->timerList_.at(i).remainTime_.remainTime_ == systemTimerInfinitTime) { continue; }

			systemTimer->timerList_.at(i).remainTime_.remainTime_ -= elapsedTime;

			// typedef long int time_t なので 0 以下になりうる
			if (systemTimer->timerList_.at(i).remainTime_.remainTime_  <= 0) {
				// セットしなおすより残しておいた方がカウントダウンやり直しのときに都合がいい
				//systemTimer->timerList_.at(i).flag_.set(SYSTEMTIMERFLAG_IS_SETTED_REMAIN_TIME, false);
				systemTimer->timerList_.at(i).remainTime_.remainTime_  = systemTimerInfinitTime;
				systemTimer->timerList_.at(i).state_ = SYSTEMTIMERSTATE_END_COUNTDOWN;
				if (systemTimer->timerList_.at(i).callback_ != NULL) {
					systemTimer->timerList_.at(i).callback_();
				}
			}

		// 締め切り時間でカウントダウンしている時
		} else if (systemTimer->timerList_.at(i).kind_ == TIMERKIND_DEADLINE_TIME) {
			if (difftime(systemTimer->timerList_.at(i).deadline_, nowTime) <= .0) {
				// カウントダウンが終了した
				systemTimer->timerList_.at(i).state_ = SYSTEMTIMERSTATE_END_COUNTDOWN;
				if (systemTimer->timerList_.at(i).callback_ != NULL) {
					systemTimer->timerList_.at(i).callback_();
				}
			}
		} else {
			// Do Nothing
		}
	}

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 制限時間を設定する
 * @note        startCountDownSystemTimer をしないとカウントダウンしない
 * @note        setDeadlineForSystemTimer とは併用不可
 * @param[in]   category    セットしたいカテゴリ
 * @param[in]   remainTime  制限時間。単位は秒。
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoSetRemainTimeForSystemTimer(TimerCategory category, weInt remainSecTime) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	// 状態の更新
	systemTimer->timerList_.at(category).state_ = SYSTEMTIMERSTATE_STOP;
	systemTimer->timerList_.at(category).kind_ = TIMERKIND_REMAIN_TIME;

	// 初期化の場合と具体的な時間がセットされた場合で区別が必要
	if (remainSecTime == systemTimerInfinitTime) {
		systemTimer->timerList_.at(category).remainTime_.remainTime_          = systemTimerInfinitTime;
		systemTimer->timerList_.at(category).remainTime_.registryRemainTIme_  = systemTimerInfinitTime;
	} else {
		systemTimer->timerList_.at(category).remainTime_.remainTime_          = remainSecTime * CLOCKS_PER_SEC;
		systemTimer->timerList_.at(category).remainTime_.registryRemainTIme_  = remainSecTime * CLOCKS_PER_SEC;
	}

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 時間のカウントダウンスタート
 * @note    setRemainTimeForSystemTimer のみに対応。制限時間の方は自動でチェックされる。
 * @param[in]   category    スタートしたいカテゴリ
 * @param[in]   value   true  : 開始
 * @param[in]   value   false : 中止(カウントはリセットされない)
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 * @except      コールバックを登録していない場合アサート
 ***************************************************************/
SystemTimerCreationError weoStartCountDownSystemTimer(TimerCategory category, weBool value) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	if (systemTimer->timerList_.at(category).remainTime_.remainTime_ == systemTimerInfinitTime) { return SYSTEMTIMERCREATIONERROR_NOERROR; }

	if (systemTimer->timerList_.at(category).callback_ != NULL) {
		if (value == TRUE) {
			systemTimer->timerList_.at(category).state_ = SYSTEMTIMERSTATE_COUNTDOWN;
		} else {
			systemTimer->timerList_.at(category).state_ = SYSTEMTIMERSTATE_STOP;
		}
	} else {
		WE_ASSERT(false, "CallBack is not setted!!!\n");
		return SYSTEMTIMERCREATIONERROR_LOGIC_ERROR;
	}

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 時間のリセット
 * @note    weoSetRemainTimeForSystemTimer でセットされた時間に戻す。
 *              過去にそれでセットされていない場合は systemTimerInfinitTime になる。
 * @param[in]   category    リセットしたいカテゴリ
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoResetCountDownTimer(TimerCategory category) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	// カウントダウンフラグを戻しつつ時間も過去のものにリセット
	systemTimer->timerList_.at(category).state_ = SYSTEMTIMERSTATE_STOP;
	systemTimer->timerList_.at(category).remainTime_.remainTime_ = systemTimer->timerList_.at(category).remainTime_.registryRemainTIme_;

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 締め切り時間を設定する
 * @note        setRemainTimeForSystemTimer とは併用不可
 * @param[in]   category    セットしたいカテゴリ
 * @param[in]   deadline    締め切り。tm が使いづらかったのでラッパーを作るかも
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoSetDeadlineForSystemTimer(TimerCategory category, tm* deadline) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	systemTimer->timerList_.at(category).state_    = SYSTEMTIMERSTATE_COUNTDOWN;
	systemTimer->timerList_.at(category).kind_     = TIMERKIND_DEADLINE_TIME;
	systemTimer->timerList_.at(category).deadline_ = mktime(deadline);

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 締切りが来たら呼ばれるコールバックを設定する
 * @param[in]   category    セットしたいカテゴリ
 * @param[in]   コールバック。引数のないもののみ。
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoSetCallBackForSystemTimer(TimerCategory category, void (*callback)(void)) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	pm_mode::ScopedLocker<TimerMutex> locker(mutex_);

	systemTimer->timerList_.at(category).callback_ = callback;
	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 残り時間の取得
 * @param[in]   category    取得したいカテゴリ
 * @param[out]  time        残り時間
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 * @except      time が NULL だとアサート
 * @except      残り時間を設定する前に呼び出すとアサート
 ***************************************************************/
SystemTimerCreationError weoGetRemainTimeSystemTimer(TimerCategory category, weInt* remainSecTime) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	if (time == NULL)                   { WE_ASSERT(false, "Argument(time) is Invalid(NULL)!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	if (systemTimer->timerList_.at(category).state_ == SYSTEMTIMERSTATE_UNINITIALIZE) { WE_ASSERT(false, "Logic Error!!! state => SYSTEMTIMERSTATE_UNINITIALIZE\n"); return SYSTEMTIMERCREATIONERROR_LOGIC_ERROR; }

	if (systemTimer->timerList_.at(category).kind_ == TIMERKIND_REMAIN_TIME) {
		*remainSecTime = systemTimer->timerList_.at(category).remainTime_.remainTime_/CLOCKS_PER_SEC;
	} else if (systemTimer->timerList_.at(category).kind_ == TIMERKIND_DEADLINE_TIME) {
		*remainSecTime = static_cast<weInt>(difftime(systemTimer->timerList_.at(category).deadline_, systemTimer->getSynchronizedNowTime()));
	} else {
		WE_ASSERT(false, "Logic Error!!!\n [ 残り時間の取得よりも前に残り時間の設定をしてください!!! ]\n");
		return SYSTEMTIMERCREATIONERROR_LOGIC_ERROR;
	}

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief 残り時間の取得
 * @param[in]   category        取得したいカテゴリ
 * @param[out]  remainSecTime   残り時間。単位は秒。float は整数部が秒。
 * @return      実行結果
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 * @except      time が NULL だとアサート
 * @except      残り時間を設定する前に呼び出すとアサート
 ***************************************************************/
SystemTimerCreationError weoGetRemainTimeByFloatSystemTimer(TimerCategory category, weFloat* remainSecTime) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }
	if (category >= TIMERCATEGORY_MAX)  { WE_ASSERT(false, "Argument(category) is Invalid!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	if (time == NULL)                   { WE_ASSERT(false, "Argument(time) is Invalid(NULL)!!!\n"); return SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT; }
	if (systemTimer->timerList_.at(category).state_ == SYSTEMTIMERSTATE_UNINITIALIZE) { WE_ASSERT(false, "Logic Error!!! state => SYSTEMTIMERSTATE_UNINITIALIZE\n"); return SYSTEMTIMERCREATIONERROR_LOGIC_ERROR; }

	if (systemTimer->timerList_.at(category).kind_ == TIMERKIND_REMAIN_TIME) {
		*remainSecTime = static_cast<weFloat>(systemTimer->timerList_.at(category).remainTime_.remainTime_/CLOCKS_PER_SEC);
		*remainSecTime += static_cast<weFloat>(systemTimer->timerList_.at(category).remainTime_.remainTime_%CLOCKS_PER_SEC)/CLOCKS_PER_SEC;
	} else if (systemTimer->timerList_.at(category).kind_ == TIMERKIND_DEADLINE_TIME) {
		*remainSecTime = static_cast<weFloat>(difftime(systemTimer->timerList_.at(category).deadline_, systemTimer->getSynchronizedNowTime()));
	} else {
		WE_ASSERT(false, "Logical Error!!!\n [ 残り時間の取得よりも前に残り時間の設定をしてください!!! ]\n");
		return SYSTEMTIMERCREATIONERROR_LOGIC_ERROR;
	}

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}


/****************************************************************
 * @brief タイマーの状態を取得する
 * @param[in]   category        取得したいカテゴリ
 * @param[in]   state           状態
 * @return      実行結果
 * @except      未初期化時に呼ぶとアサート
 ***************************************************************/
SystemTimerCreationError weoGetTimerStateSystemTimer(TimerCategory category, SystemTimerState* state) throw() {
	if (systemTimer == NULL)            { WE_ASSERT(false, "SystemTimer is not initialized!!!\n"); return SYSTEMTIMERCREATIONERROR_UNINIT; }

	*state = systemTimer->timerList_.at(category).state_;

	return SYSTEMTIMERCREATIONERROR_NOERROR;
}

