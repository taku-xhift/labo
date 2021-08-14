

#include <iostream>
#include <ctime>
//#include <windows.h>
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

		weoSetRemainTimeForSystemTimer(TIMERCATEGORY_FORMATION, systemTimerInfinitTime);
		//weoSetCallBackForSystemTimer(TIMERCATEGORY_FORMATION, flagSetter);
		weoStartCountDownSystemTimer(TIMERCATEGORY_FORMATION, true);

	// コールバックが呼ばれるまでタイマーのアップデート
	while (!flag) {
		weoResetServerTime(time(NULL));
		weoUpdaterSystemTimer();
		//Sleep(16);      // 1/60 フレームの待機時間のシミュレート

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


