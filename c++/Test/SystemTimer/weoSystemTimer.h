/**
 * @file  SystemTimer.hpp
 * @brief タイマー管理クラス。
 * @note    スレッドセーフ
 * @note    使用例は一番下
 *
 * @author Takuya Shishido
 * @date   2011.06.15 10:08:37
 *
 * @version 1.01, Shishido Takuya, 2011.06.15 10:08:37
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef WEO_SYSTEMTIMER_HPP_INCLUDED
#define WEO_SYSTEMTIMER_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include <limits.h>
#include <time.h>


#ifdef __cplusplus
extern "C" {
#endif



// ----- mini test の都合 -----------------------------------------------

typedef int         weBool;
typedef int         weInt;
typedef float       weFloat;
typedef long int    weLong;
typedef const char* weString;

#define ExceptionMessage(message_)      ("")
#define WE_ASSERT(condition, message_) assert(condition)
#define WE_PRINTF(...)
#define NEW new
#define SAFE_DELETE(obj) do { if (obj != NULL) { delete obj; obj = NULL; } } while(0)

// ------ ここまで mini test --------------------------------------------


const weLong systemTimerInfinitTime = LONG_MAX;       //!< 無制限を示す値


/****************************************************************
 * @brief タイマーのカテゴリ一覧。種類が増えればこれを追加していく
 ***************************************************************/
typedef enum {
	//試合中のリスタート関連
	TIMERCATEGORY_KICKOFF,
	TIMERCATEGORY_THROWIN,
	TIMERCATEGORY_GOALKICK, 
	TIMERCATEGORY_CORNERKICK, 
	TIMERCATEGORY_FREEKICK, 
	TIMERCATEGORY_BRIEF_FREEKICK, 
	TIMERCATEGORY_PKMATCH, 

	TIMERCATEGORY_FORMATION,    //!< フォーメーション用
	TIMERCATEGORY_MAX,
} TimerCategory;


/****************************************************************
 * @brief タイマーの状態
 ***************************************************************/
typedef enum {
	SYSTEMTIMERSTATE_UNINITIALIZE,      //!< １度もセットされたことがない
	SYSTEMTIMERSTATE_STOP,              //!< 値はセットされているがストップ中
	SYSTEMTIMERSTATE_COUNTDOWN,         //!< カウントダウン中
	SYSTEMTIMERSTATE_END_COUNTDOWN,     //!< カウントダウンが終了した(get で返す値は前回設定した値)
	SYSTEMTIMERSTATE_MAX,
} SystemTimerState;


/****************************************************************
 * @brief タイマーの実行結果
 ***************************************************************/
typedef enum {
	SYSTEMTIMERCREATIONERROR_NOERROR,           //!< エラーなし
	SYSTEMTIMERCREATIONERROR_ALLOCATE,          //!< メモリ確保失敗
	SYSTEMTIMERCREATIONERROR_UNINIT,            //!< 初期化されていない状態で実行した
	SYSTEMTIMERCREATIONERROR_LOGIC_ERROR,       //!< 論理エラーが発生している
	SYSTEMTIMERCREATIONERROR_INVALID_ARGUMENT,  //!< 無効な引数が渡された
	SYSTEMTIMERCREATIONERROR_MAX,
} SystemTimerCreationError;



typedef time_t ServerTime;      //!< サーバ時間の型


/****************************************************************
 * @brief サーバの時間の setter
 * @param[in]   serverTime  サーバの時間。型をどうするのか不明
 * @return      実行結果
 ***************************************************************/
SystemTimerCreationError weoResetServerTime(ServerTime serverTime);


/****************************************************************
 * @brief タイマーの初期化
 ***************************************************************/
SystemTimerCreationError weoCreateTimerDataSystemTimer();


/****************************************************************
 * @brief タイマーの破棄
 ***************************************************************/
void weoDestroyTimerDataSystemTimer();


/****************************************************************
 * @brief タイマーのアップデータ
 * @return      実行結果
 ***************************************************************/
SystemTimerCreationError weoUpdaterSystemTimer();


/****************************************************************
 * @brief 制限時間を設定する
 * @note    startCountDownSystemTimer をしないとカウントダウンしない
 * @note    setDeadlineForSystemTimer とは併用不可
 * @note    クリアした時のデフォルト値にもなる
 * @param[in]   category        セットしたいカテゴリ
 * @param[in]   remainSecTime   制限時間。単位は秒。
 * @return      実行結果
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoSetRemainTimeForSystemTimer(TimerCategory category, weInt remainSecTime);


/****************************************************************
 * @brief 時間のカウントダウンスタート
 * @note    setRemainTimeForSystemTimer のみに対応。制限時間の方は自動でチェックされる。
 * @param[in]   category    スタートしたいカテゴリ
 * @param[in]   value   true  : 開始
 * @param[in]   value   false : 中止(カウントはリセットされない)
 * @return      実行結果
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 * @except      コールバックを登録していない場合アサート
 ***************************************************************/
SystemTimerCreationError weoStartCountDownSystemTimer(TimerCategory category, weBool value);


/****************************************************************
 * @brief 時間のリセット
 * @note    weoSetRemainTimeForSystemTimer でセットされた時間に戻す。
 *              過去にそれでセットされていない場合は systemTimerInfinitTime になる。
 * @param[in]   category    リセットしたいカテゴリ
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoResetCountDownTimer(TimerCategory category);


/****************************************************************
 * @brief 締め切り時間を設定する
 * @note        setRemainTimeForSystemTimer とは併用不可
 * @param[in]   category    セットしたいカテゴリ
 * @param[in]   deadline    締め切り。tm が使いづらかったのでラッパーを作るかも
 * @return      実行結果
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoSetDeadlineForSystemTimer(TimerCategory category, struct tm* deadline);


/****************************************************************
 * @brief 締切りが来たら呼ばれるコールバックを設定する
 * @param[in]   category    セットしたいカテゴリ
 * @param[in]   コールバック。引数のないもののみ。
 * @return      実行結果
 * @except      category が想定範囲以上で渡されるとアサート
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoSetCallBackForSystemTimer(TimerCategory category, void (*callback)(void));


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
SystemTimerCreationError weoGetRemainTimeSystemTimer(TimerCategory category, weInt* remainSecTime);
SystemTimerCreationError weoGetRemainTimeByFloatSystemTimer(TimerCategory category, weFloat* remainSecTime);


/****************************************************************
 * @brief タイマーの状態を取得する
 * @param[in]   category        取得したいカテゴリ
 * @param[out]  state           状態
 * @return      タイマーの現在の状態
 * @except      weoCreateTimerDataSystemTimer が呼ばれないまま使用するとアサート
 ***************************************************************/
SystemTimerCreationError weoGetTimerStateSystemTimer(TimerCategory category, SystemTimerState* state);



#ifdef __cplusplus
}
#endif

#endif  // SYSTEMTIMER_HPP_INCLUDED



/*

//---------------------------------------------------------------
//  使用例
//---------------------------------------------------------------


#include <iostream>
#include <ctime>
#include <windows.h>
#include "weoSystemTimer.h"


bool flag = false;

void flagSetter() {
	flag = true;
}

void printState(SystemTimerState state) {
	if (state == SYSTEMTIMERSTATE_COUNTDOWN) {
		std::cout << "CountDown." << std::endl;
	} else if (state == SYSTEMTIMERSTATE_END_COUNTDOWN) {
		std::cout << "End CountDown..." << std::endl;
	} else if (state == SYSTEMTIMERSTATE_STOP) {
		std::cout << "Stop CountDown..." << std::endl;
	} else if (state == SYSTEMTIMERSTATE_UNINITIALIZE) {
		std::cout << "Uninitialize!!!" << std::endl;
	}
}



int main() {
	// 初期化
	weoCreateTimerDataSystemTimer();
	weoResetServerTime(time(NULL));

	// １．残り時間でのタイマーの設定
	{
		// ４秒後に FORMATION のコールバックを呼んでもらうための手順
		weoSetRemainTimeForSystemTimer(TIMERCATEGORY_FORMATION, 4);
		weoSetCallBackForSystemTimer(TIMERCATEGORY_FORMATION, flagSetter);
		weoStartCountDownSystemTimer(TIMERCATEGORY_FORMATION, true);
	}

	// ２．締め切り時間でのタイマーの設定
	{
		// 特定の時間にコールバックの呼び出しをしてもらう手順
		// struct tm が非常に使いづらいのでラップする可能性あります
		tm time = {0};
		time.tm_sec = 0;            // 秒(0～61)
		time.tm_min = 3;           // 分(0～59)
		time.tm_hour = 17;           // 時(0～23)
		time.tm_mday = 21;          // 日(1～31)
		time.tm_mon = 11-1;          // 月(1月を0とする)
		time.tm_year = 2011-1900;   // 年(1900年を0とする)
		//time.tm_wday;             // 曜日(日曜日を0とする)
		//time.tm_yday;             // 1月1日からの日数
		//time.tm_isdst;            // 季節時間の有無

		weoSetDeadlineForSystemTimer(TIMERCATEGORY_FORMATION, &time);
		weoSetCallBackForSystemTimer(TIMERCATEGORY_FORMATION, flagSetter);
	}

	// コールバックが呼ばれるまでタイマーのアップデート
	while (!flag) {
		weoResetServerTime(time(NULL));
		weoUpdaterSystemTimer();
		Sleep(16);      // 1/60 フレームの待機時間のシミュレート

		SystemTimerState state;
		weoGetTimerStateSystemTimer(TIMERCATEGORY_FORMATION, &state);
		printState(state);
		float remain = .0f;
		//weoGetRemainTimeByFloatSystemTimer(TIMERCATEGORY_FORMATION, &remain);
		weoGetRemainTimeByFloatSystemTimer(TIMERCATEGORY_FORMATION, &remain);
		std::cout << "Remain = " << remain << "\n";
	}

	// コールバックが呼ばれていればここにたどり着く
	std::cout << "Finished CountDown!!!" << std::endl;

	// タイマークラスの後処理
	weoDestroyTimerDataSystemTimer();
}




*/



