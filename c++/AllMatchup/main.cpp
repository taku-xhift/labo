


#include <iostream>
#include <vector>
#include <utility>  // std::pair
#include <algorithm>

const int bye = -1;    //!< �s�폟

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
	DaySchedule daySchedule;    //!< �����̃X�P�W���[���Ǘ�
	Schedule schedule;          //!< �S�̃X�P�W���[��

	std::vector<int> left;      //!< �o�͌��ʂ� vs �̍����ɏo�����
	std::vector<int> right;     //!< �o�͌��ʂ� vs �̉E���ɏo�����

	// ��Ȃ�s�폟������
	if (teamNum_ % 2 == 1) {
		left.push_back(bye);
	}

	// �����ɔ����A�E���Ɏc�������B
	for (int i = 0; i < teamNum_/2; ++i) {
		left.push_back(i);
	}
	for (int i = teamNum_/2; i < teamNum_; ++i) {
		right.push_back(i);
	}

	// �X�P�W���[���i�[
	// �A���S���Y���Q�l -> http://www.prm.nau.edu/prm280/tournament_round_robin.htm
	// e.g.
	//
	//  �Œ� ->  1  vs  4
	//           2  vs  5
	//           3  vs  6
	//
	// ������Œ�ɂ��āA�c��̂T�`�[�������v���ɂ��炵�Ă����B
	//
	//  �Œ� ->  1  vs  2
	//           3  vs  4
	//           6  vs  5
	//
	// ���[�v�X�g�b�v�����́A��ԍŏ��ɉE��ɂ������`�[����������x�����Ƃ�
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
		left.erase(eraceIte);   // �Q�߂��������߃C���N�������g������

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

