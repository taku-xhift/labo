/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.11.17 13:57:17
 *
 * @version 0.01, Shishido Takuya, 2010.11.17 13:57:17
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <Personal/StreamObject.hpp>
#include "DataType.hpp"
#include "Functor.hpp"
#include "Utility.hpp"


std::string DispParam::stringPosition() const throw(ConvertError) {
	return posConverter(this->position_);
}


void DispParam::position(const std::string& position) throw(ConvertError) {
	this->position_ = posConverter(position);
}

// 出力
std::ostream& operator<<(std::ostream& os, const DispParam& param) throw()
{
	os << "team = " << param.team() << "\n";
	os << "name = " << param.name() << "\n";
	try {
		std::string pos = param.stringPosition();
		os << "position = " << pos << "\n";
	} catch (ConvertError& e) {
		os << e.what() << "\n";
		os << "position = " << param.position() << "\n";
	}
	os << "side = " << param.side() << "\n";
	os << "offence = " << param.offence() << "\n";
	os << "defence = " << param.defence() << "\n";
	os << "stamina = " << param.stamina() << "\n";
	os << "speed = " << param.speed() << "\n";
	os << "power = " << param.power() << "\n";
	os << "pass = " << param.pass() << "\n";
	os << "dribble = " << param.dribble() << "\n";
	os << "gkSkill = " << param.gkSkill() << "\n";
	os << "injury = " << param.injury() << "\n";
	os << "star = " << param.star() << "\n";
	os << "\n";

	return os;
}

// 出力
std::ostream& operator<<(std::ostream& os, const SeasonRecord& param) throw()
{
	os << "rank = " << param.rank << "\n";
	os << "points = " << param.points << "\n";
	os << "win = " << param.win << "\n";
	os << "lose = " << param.lose << "\n";
	os << "draw = " << param.draw << "\n";
	os << "goal = " << param.goal << "\n";
	os << "lost = " << param.lost << "\n";
	os << "total goalPoints = " << param.goalPoints << "\n";
	os << "\n";

	return os;
}



void Team::reset() throw() {
	this->reseted_ = true;

	if (this->list_.size() == 0) {
		return;
	}

	try {
		this->team_ = this->list_.front().team();
		this->attack_ = Sum(this->list_, SumAttackWithFW()).average();
		this->defence_ = Sum(this->list_, SumDefenceWithDF()).average();
		this->stamina_ = Sum(this->list_, SumStamina()).average();
		this->speed_ = Sum(this->list_, SumSpeed()).average();
		this->power_ = Sum(this->list_, SumPower()).average();
		this->pass_ = Sum(this->list_, SumPassWithMF()).average();
		this->dribble_ = Sum(this->list_, SumDribble()).average();
		this->gkSkill_ = Sum(this->list_, SumGKSkillWithGK()).average();
		this->star_ = Sum(this->list_, SumStar()).sum();
		this->connection_ = Sum(this->list_, SumConnection()).sum();
	} catch(DevideByZero& e) {
		so::out << e.what() << so::endl;
		so::out << __LINE__ << so::endl;
		so::out << __FUNCTION__ << so::endl;
		so::out << "zero devide was happen!! Set zero!!" << so::endl;
		this->team_ = this->list_.front().team();
		this->attack_ = 0;
		this->defence_ = 0;
		this->stamina_ = 0;
		this->speed_ = 0;
		this->power_ = 0;
		this->pass_ = 0;
		this->dribble_ = 0;
		this->gkSkill_ = 0;
		this->star_ = 0;
		this->connection_ = 0;
	}
}


// 出力
std::ostream& operator<<(std::ostream& os, const Team& param) throw()
{
	os << "=======================================================" << "\n\n";
	os << "team = " << param.team() << "\n";
	os << "offence = " << param.offence() << "\n";
	os << "defence = " << param.defence() << "\n";
//	os << "stamina = " << param.stamina() << "\n";
//	os << "speed = " << param.speed() << "\n";
//	os << "power = " << param.power() << "\n";
	os << "pass = " << param.pass() << "\n";
//	os << "dribble = " << param.dribble() << "\n";
	os << "gkSkill = " << param.gkSkill() << "\n";
	os << "connection = " << param.connection() << "\n";
	os << "star = " << param.star() << "\n";
//	os << "points = " << param.points() << "\n";
//	os << "win = " << param.win() << "\n";
//	os << "lose = " << param.lose() << "\n";
//	os << "draw = " << param.draw() << "\n";
//	os << "goal = " << param.goal() << "\n";
//	os << "lost = " << param.lost() << "\n";
//	os << "goalPoints = " << param.goalPoints() << "\n";

	os << "\n";

	try {
		//os << "goalDifferencePercent = " << param.goalDifferencePercent() << "\n";
	} catch (DevideByZero& e) {
		os << e.what();
		os << "not effecteve." << "\n";
	}

	for (unsigned int i = 0; i < param.career_.size(); ++i) {
		os << "seazon " << i << " is " << param.career_.at(i);
	}
	os << "=======================================================" << "\n";

	os << "\n";

	return os;
}

// 出力
std::ostream& operator<<(std::ostream& os, const RoundRobin& param) throw()
{
	int count = 0;
	for (std::vector<std::vector<std::pair<unsigned int, unsigned int> > >::const_iterator ite = param.matchPair_.begin(); ite != param.matchPair_.end(); ++ite, ++count) {
		os << "day " << count << "\n";
		for (std::vector<std::pair<unsigned int, unsigned int> >::const_iterator ite2 = ite->begin(); ite2 != ite->end(); ++ite2) {
			std::cerr << "home = " << ite2->first << " vs " << ite2->second << " = away\n\n";
		}
		std::cerr << std::endl;
	}

	return os;
}

int homeGoalNum(const Team& attacker, const Team& defencer) throw() {
	float temp = (attacker.offence()*attacker.connection() - (defencer.defence() + defencer.gkSkill()))/5.0f;
	return std::max(0, static_cast<int>(temp));
}
int awayGoalNum(const Team& attacker, const Team& defencer) throw() {
	float temp = (2*attacker.offence() - (defencer.defence() + defencer.gkSkill()))/5.0f;
	return std::max(0, static_cast<int>(temp));
}

// 一旦完成版


int goalNum(const Team& attacker, const Team& defencer) throw() {

	float attack = 28.0f*attacker.offence()+(attacker.star()/.15f);
	float pass = 27*attacker.pass()+attacker.connection()/30.0f;
	float defence = (defencer.defence() + defencer.gkSkill())*22.0f;
	float random = gausianRandom(1.0f, .3f);

	float temp = ((attack+pass)
	                - defence)
	                * random
	                / 8.0f;

	return std::max(0, static_cast<int>(temp));
}


// defence が 30 倍されていないが再度保留
//int goalNum(const Team& attacker, const Team& defencer) throw() {
//	float attack = 30.0f*attacker.offence()+(attacker.star()/.10f);
//	float pass = 10*attacker.pass()+attacker.connection()/100.0f;
//	float defence = defencer.defence() + defencer.gkSkill()*30.0f;
//	float temp = ((attack+pass)
//	                - defence)
//	                //* gausianRandom(1.0f, .3f)/5.0f;
//		            / 8.0f;
//	return std::max(0, static_cast<int>(temp));
//}



// 一旦完成版
//int goalNum(const Team& attacker, const Team& defencer) throw() {
//	float temp = (attacker.offence()*attacker.connection()*(attacker.star()/60.0f)/4.0f
//	                - (defencer.defence() + defencer.gkSkill()))
//	                * gausianRandom(1.0f, .3f)/5.0f;
//	return std::max(0, static_cast<int>(temp));
//}

OneMatchResult matchup(Team& home, Team& away, unsigned int restDay, unsigned int maxNameSize) throw()
{
	// エラー処理
	//if (restDay == -1) { throw std::invalid_argument(ExceptionMessage("")); }

	float homeGoal = static_cast<float>(home.goalPoints())/static_cast<float>((restDay+1)*100);
	float random = gausianRandom(.0f,static_cast<float>(homeGoal)/2.0f);
	homeGoal += random;
	homeGoal = std::max(homeGoal, .0f);
	float awayGoal = static_cast<float>(away.goalPoints())/static_cast<float>((restDay+1)*100);
	awayGoal += gausianRandom(.0f,static_cast<float>(awayGoal)/2.0f);
	awayGoal = std::max(awayGoal, .0f);

	home.addGoal(homeGoal);
	home.addLost(awayGoal);
	home.goalPoints(home.goalPoints()-static_cast<int>(homeGoal)*100);
	away.addGoal(awayGoal);
	away.addLost(homeGoal);
	away.goalPoints(away.goalPoints()-static_cast<int>(awayGoal)*100);


	// 勝利カウント
	if (static_cast<int>(homeGoal) > static_cast<int>(awayGoal)) {
		home.addWin();
		away.addLose();
	} else if (static_cast<int>(homeGoal) == static_cast<int>(awayGoal)) {
		home.addDraw();
		away.addDraw();
	} else {
		home.addLose();
		away.addWin();
	}

	// 返り値作る
	return OneMatchResult(home.team(), homeGoal, away.team(), awayGoal, maxNameSize);
}


// 出力
std::ostream& operator<<(std::ostream& os, const OneMatchResult& param) throw()
{
	os << param.home_;
	std::string space(" ");
	for (unsigned int i = 0; i < param.maxNameSize_ - param.home_.size(); ++i) {
		os << space;
	}
	os << "   " << param.homeGoal_ << " vs " << param.awayGoal_ << "   " << param.away_ << std::endl;

	return os;
}


// 出力
std::ostream& operator<<(std::ostream& os, const OneDayMatchResult& param) throw() {
	os << "day : " << param.day_ << "\n";
	for (unsigned int i = 0; i < param.result_.size(); ++i) {
		os << param.result_.at(i);
	}
	os << std::endl;

	return os;
}


void SeasonResult::finishSeazon() throw() {
	// 順位に応じて並び替え
	//this->sortTeam(SortByGoalPointsGreater());
	this->sortTeam(SortByPointsGreater());
	for (unsigned int i = 0; i < this->teamList_.size(); ++i) {
		// 並べ替えられた順位を渡す
		this->teamList_.at(i).rank(i);
		this->teamList_.at(i).goNextSeazon();
	}
	this->record_.push_back(this->result_);
	this->day_ = 0u;
	this->culcGoalPoints();
}


// 出力
std::ostream& operator<<(std::ostream& os, const SeasonResult& param) throw()
{
	unsigned int count = 0;
	os << "SeasonResult" << std::endl;
	for (std::vector<std::vector<OneDayMatchResult> >::const_iterator ite1 = param.record_.begin(); ite1 != param.record_.end(); ++ite1) {
		so::out << "Season " << count << "\n";
		for (std::vector<OneDayMatchResult>::const_iterator ite2 = ite1->begin(); ite2 != ite1->end(); ++ite2) {
			os << *ite2;
		}
		so::out << "\n";
		++count;
	}
	os << std::endl;

	return os;
}






