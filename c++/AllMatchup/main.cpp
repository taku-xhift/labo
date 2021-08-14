


#include <iostream>
#include <vector>
#include <utility>  // std::pair
#include <algorithm>

const int bye = -1;    //!< 不戦勝

typedef std::vector<std::pair<int, int> > DaySchedule;
typedef std::vector<DaySchedule> Schedule;


/**----------------------------------------------------
 * @brief   Getter of game by day.
 * @param[in]   schedule_      game schedule.
 * @return      game number by day.
 *---------------------------------------------------*/
int getGamesByDay(const Schedule& schedule_) {
	if (schedule_.size() != 0) {
		return schedule_.front().size();
	} else {
		return 0;
	}
}


/**----------------------------------------------------
 * @brief   Getter of all days.
 * @param[in]   schedule_      game schedule.
 * @return      Day of this schecule.
 *---------------------------------------------------*/
int getMatchDays(const Schedule& schedule_) {
	return schedule_.size();
}


/**----------------------------------------------------
 * @brief   Getter of day match.
 * @note    Return no schecule if your assign is over schedule.
 * @param[in]   schedule_   game schedule.
 * @param[in]   day_        A day of match you want.
 * @return      Match schecule you name.
 *---------------------------------------------------*/
DaySchedule getMatchDays(const Schedule& schedule_, int day_) {
	if (getMatchDays < day_) {
		return DaySchedule();
	} else {
		return schedule_.at(day_);
	}
}



/**----------------------------------------------------
 * @brief   Schecule creater of Group League.
 * @note        Match pair '-1' is restTime.
 * @param[in]   teamNum_    Participating team number.
 * @return      Schecule of match.
 *---------------------------------------------------*/
Schedule scheduleCreater(int teamNum_)
{
	DaySchedule daySchedule;    //!< 日毎のスケジュール管理
	Schedule schedule;          //!< 全体スケジュール

	std::vector<int> left;      //!< 出力結果で vs の左側に出るもの
	std::vector<int> right;     //!< 出力結果で vs の右側に出るもの

	// 奇数なら不戦勝が存在
	if (teamNum_ % 2 == 1) {
		left.push_back(bye);
	}

	// 左側に半分、右側に残りを入れる。
	for (int i = 0; i < teamNum_/2; ++i) {
		left.push_back(i);
	}
	for (int i = teamNum_/2; i < teamNum_; ++i) {
		right.push_back(i);
	}

	// スケジュール格納
	// アルゴリズム参考 -> http://www.prm.nau.edu/prm280/tournament_round_robin.htm
	// e.g.
	//
	//  固定 ->  1  vs  4
	//           2  vs  5
	//           3  vs  6
	//
	// 左上を固定にして、残りの５チームを時計回りにずらしていく。
	//
	//  固定 ->  1  vs  2
	//           3  vs  4
	//           6  vs  5
	//
	// ループストップ条件は、一番最初に右上にあったチームがもう一度来たとき
	do {
		for (int i = 0; i < left.size(); ++i) {
			daySchedule.push_back(std::pair<int, int>(left.at(i), right.at(i)));
		}
		schedule.push_back(daySchedule);
		daySchedule.clear();

		left.push_back(right.back());
		right.pop_back();

		right.insert(right.begin(), 1, left.at(1));
		std::vector<int>::iterator eraceIte = left.begin();
		++eraceIte;
		left.erase(eraceIte);   // ２つめを消すためインクリメント後入れる

	} while (schedule.front().front().second != right.front());

	return schedule;
}


struct PrintDaySchedule {
	void operator()(const std::pair<int, int>& pair_) {
		std::cerr << "		" << pair_.first << " vs " << pair_.second << std::endl;
	}
};

struct PrintSchedule {
	PrintSchedule() : day(0) {}

	void operator()(const DaySchedule& daySchedule_) {
		std::cerr << "	day " << day++ << std::endl;
		std::for_each(daySchedule_.begin(), daySchedule_.end(), PrintDaySchedule());
	}

private:
	int day;
};


int main() {

	Schedule schedule = scheduleCreater(9);

	std::cout << "schedule" << std::endl;
	std::cout << "match days : " << getMatchDays(schedule) << std::endl;
	std::cout << "match by day : " << getGamesByDay(schedule) << std::endl;
	std::for_each(schedule.begin(), schedule.end(), PrintSchedule());

	return 0;
}

