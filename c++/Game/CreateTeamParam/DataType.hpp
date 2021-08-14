
#ifndef DATATYPE_HPP_INCLUDED
#define DATATYPE_HPP_INCLUDED

#pragma warning(disable:4996)
#pragma warning(disable:4290)

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <Personal/StreamObject.hpp>
#include "Define.hpp"


class DispParam {
public:
	DispParam() throw() {
		this->clear();
	}

	void clear() throw() {
		this->team_ = "";
		this->name_ = "";
		this->position_ = PosList_max;
		this->side_ = 0;
		this->attack_ = 0;
		this->defence_ = 0;
		this->stamina_ = 0;
		this->speed_ = 0;
		this->power_ = 0;
		this->pass_ = 0;
		this->dribble_ = 0;
		this->gkSkill_ = 0;
		this->connection_ = 0;
	}

	std::string team() const throw()    { return this->team_; }
	std::string name() const throw()    { return this->name_; }
	PosList position() const throw()    { return this->position_; }
	std::string stringPosition() const throw(ConvertError);
	int side() const throw()            { return this->side_; }
	int offence() const throw()          { return this->attack_; }
	int defence() const throw()         { return this->defence_; }
	int stamina() const throw()         { return this->stamina_; }
	int speed() const throw()           { return this->speed_; }
	int power() const throw()           { return this->power_; }
	int pass() const throw()            { return this->pass_; }
	int dribble() const throw()         { return this->dribble_; }
	int gkSkill() const throw()         { return this->gkSkill_; }
	int connection() const throw()      { return this->connection_; }
	std::string injury() const throw()  { return this->injury_; }
	int star() const throw()            { return this->star_; }

	bool skill(SkillCard skill) const throw(std::out_of_range) { return this->skill_.test(skill); }



	void team(const std::string& team) throw()  { this->team_ = team; }
	void name(const std::string& name) throw()  { this->name_ = name; }
	void position(const std::string& position) throw(ConvertError);
	void position(PosList position) throw()     { this->position_ = position; }
	void side(int side) throw()                 { this->side_ = side; }
	void attack(int attack) throw()             { this->attack_ = attack; }
	void defence(int defence) throw()           { this->defence_ = defence; }
	void stamina(int stamina) throw()           { this->stamina_ = stamina; }
	void speed(int speed) throw()               { this->speed_ = speed; }
	void power(int power) throw()               { this->power_ = power; }
	void pass(int pass) throw()                 { this->pass_ = pass; }
	void dribble(int dribble) throw()           { this->dribble_ = dribble; }
	void gkSkill(int gkSkill) throw()           { this->gkSkill_ = gkSkill; }
	void connection(int connection) throw()     { this->connection_ = connection; }
	void injury(std::string injury) throw()     { this->injury_ = injury; }
	void star(int star) throw()                 { this->star_ = star; }

	void skill(SkillCard skill, bool value) throw(std::out_of_range) { this->skill_.set(skill, value); }

private:
	friend std::ostream& operator<<(std::ostream& os, const DispParam& param);

private:
	std::string team_;
	std::string name_;
	PosList position_;
	int side_;
	int attack_;
	int defence_;
	int stamina_;
	int speed_;
	int power_;
	int pass_;
	int dribble_;
	int gkSkill_;
	int connection_;
	std::string injury_;
	int star_;
	std::bitset<SkillCard_max>  skill_;
};

// 出力
std::ostream& operator<<(std::ostream& os, const DispParam& param) throw();



struct SeasonRecord
{
	unsigned int seazon;
	unsigned int rank;
	unsigned int points;
	unsigned int win;
	unsigned int lose;
	unsigned int draw;
	unsigned int goal;
	unsigned int lost;
	unsigned int goalPoints;

	SeasonRecord() throw()
		: seazon(0)
		, rank(0)
		, points(0)
		, win(0)
		, lose(0)
		, draw(0)
		, goal(0)
		, lost(0)
		, goalPoints(0)
	{
	}

	void goNextSeazon() throw() {
		++this->seazon;
		this->rank = 0;
		this->points = 0;
		this->win = 0;
		this->lose = 0;
		this->draw = 0;
		this->goal = 0;
		this->lost = 0;
		this->goalPoints = 0;
	}
};

// 出力
std::ostream& operator<<(std::ostream& os, const SeasonRecord& param) throw();




class Team {
public:
	Team() throw()
		: attack_(0)
		, defence_(0)
		, stamina_(0)
		, speed_(0)
		, power_(0)
		, pass_(0)
		, dribble_(0)
		, gkSkill_(0)
		, connection_(0)
		, star_(0)
//		, goal_(0)
//		, lost_(0)
//		, win_(0)
//		, lose_(0)
//		, draw_(0)
		, allPoints_(std::numeric_limits<unsigned int>::max())
		, reseted_(true)
	{
	}

	void reset() throw();

	void add(const DispParam& param) throw() {
		this->list_.push_back(param);
		this->reseted_ = false;
	}

	std::string team() const throw()    { return this->team_; }
	int offence() const throw()          { return this->attack_; }
	int defence() const throw()         { return this->defence_; }
	int stamina() const throw()         { return this->stamina_; }
	int speed() const throw()           { return this->speed_; }
	int power() const throw()           { return this->power_; }
	int pass() const throw()            { return this->pass_; }
	int dribble() const throw()         { return this->dribble_; }
	int gkSkill() const throw()         { return this->gkSkill_; }
	int connection() const throw()      { return this->connection_; }
	int star() const throw()            { return this->star_; }


	int goal() const throw()            { return this->record_.goal; }
	int lost() const throw()            { return this->record_.lost; }
	int win() const throw()             { return this->record_.win; }
	int lose() const throw()            { return this->record_.lose; }
	int draw() const throw()            { return this->record_.draw; }
	int points() const throw()          { return 3*(this->record_.win) + this->record_.draw; }
	int goalDifference() const throw()  { return this->record_.goal - this->record_.lost; }
	int rank() const throw()            { return this->record_.rank; }
	SeasonRecord record() const throw() { return this->record_; }

	unsigned int allRankSum() throw() {
		if (this->allPoints_ == std::numeric_limits<unsigned int>::max()) {
			for (std::vector<SeasonRecord>::const_iterator ite = this->career_.begin(); ite != this->career_.end(); ++ite) {
				this->allPoints_ += ite->rank;
			}
		}
		return this->allPoints_;
	}

	int goalPoints() const throw()      { return this->goalPoints_; }


	bool reseted() const throw()        { return this->reseted_; }

	float goalDifferencePercent() const throw(DevideByZero)  {
		if (this->record_.lost != 0) {
			return static_cast<float>(this->record_.goal)/static_cast<float>(this->record_.lost);
		} else {
			throw DevideByZero(ExceptionMessage("DevideByZero"));
		}
	}


	void team(const std::string& team) throw()  { this->team_ = team; }
//	void attack(int attack) throw()             { this->attack_ = attack; }
//	void defence(int defence) throw()           { this->defence_ = defence; }
//	void stamina(int stamina) throw()           { this->stamina_ = stamina; }
//	void speed(int speed) throw()               { this->speed_ = speed; }
//	void power(int power) throw()               { this->power_ = power; }
//	void pass(int pass) throw()                 { this->pass_ = pass; }
//	void dribble(int dribble) throw()           { this->dribble_ = dribble; }
//	void star(int star) throw()                 { this->star_ = star; }


	void goalPoints(int goalPoints) throw() { this->goalPoints_ = goalPoints; }

	void goal(unsigned int goal) throw()        { this->record_.goal = goal; }
	void lost(unsigned int lost) throw()        { this->record_.lost = lost; }
	void win(unsigned int win) throw()          { this->record_.win = win; }
	void lose(unsigned int lose) throw()        { this->record_.lose = lose; }
	void draw(unsigned int draw) throw()        { this->record_.draw = draw; }
	void rank(unsigned int rank) throw()        { this->record_.rank = rank; }
	void saveGoalPoints(unsigned int goalPoints) throw() { this->record_.goalPoints = goalPoints; }

	void addGoal(int goal) throw()              { this->record_.goal += goal; }
	void addLost(int lost) throw()              { this->record_.lost += lost; }
	void addWin() throw()                       { ++this->record_.win; }
	void addLose() throw()                      { ++this->record_.lose; }
	void addDraw() throw()                      { ++this->record_.draw; }

	void goNextSeazon() throw() {
		this->career_.push_back(this->record_);
		this->record_.goNextSeazon();
	}



private:
	friend std::ostream& operator<<(std::ostream& os, const Team& param) throw();

private:
	std::string team_;
	int attack_;
	int defence_;
	int stamina_;
	int speed_;
	int power_;
	int pass_;
	int dribble_;
	int gkSkill_;
	int connection_;
	int star_;

	SeasonRecord record_;
	std::vector<SeasonRecord> career_;


	int goalPoints_;
	int allPoints_;

	bool reseted_;

	std::vector<DispParam> list_;
};

// 出力
std::ostream& operator<<(std::ostream& os, const Team& param) throw();




// 参考 http://www.prm.nau.edu/prm280/tournament_round_robin.htm
class RoundRobin {
public:

	friend std::ostream& operator<<(std::ostream& os, const RoundRobin& param) throw();


	unsigned int day() const throw() { return this->teamList_.size()-1; }

	//! \brief
	//! \note   持っているスケジュールの日程より大きい場合
	//              ２週、３週目に入っていると判断する
	const std::vector<std::pair<unsigned int, unsigned int> >& matchList(unsigned int day) const throw() {
		unsigned int reducedDay = day;
		while (this->matchPair_.size()-1 < reducedDay) {
			reducedDay -= this->matchPair_.size();
		}
		return this->matchPair_.at(reducedDay);
	}


	void print() const throw() {
		int count = 0;
		for (std::vector<std::vector<std::pair<unsigned int, unsigned int> > >::const_iterator ite = this->matchPair_.begin(); ite != this->matchPair_.end(); ++ite, ++count) {
			std::cerr << "day " << count << "\n";
			for (std::vector<std::pair<unsigned int, unsigned int> >::const_iterator ite2 = ite->begin(); ite2 != ite->end(); ++ite2) {
				std::cerr << "home = " << ite2->first << " vs " << ite2->second << " = away\n\n";
			}
			std::cerr << std::endl;
		}
	}


	RoundRobin(const std::vector<Team>& teamList) throw()
		: teamList_(teamList)
	{
		// サイズは事前に準備
		std::vector<unsigned int> homeContainer(teamList.size()/2);
		std::vector<unsigned int> awayContainer(teamList.size()/2);

		// 仕分け用にラベル作成
		for (unsigned int i = 0; i < homeContainer.size(); ++i) {
			homeContainer.at(i) = i;
		}
		for (unsigned int i = 0; i < awayContainer.size(); ++i) {
			awayContainer.at(i) = i + homeContainer.size();
		}

		// 対戦表作成
		std::vector<std::pair<unsigned int, unsigned int> > dayMatch;
		for (unsigned int i = 0; i < teamList.size()-1; ++i) {
			for (unsigned int j = 0; j < teamList.size()/2; ++j) {
				dayMatch.push_back(std::make_pair(homeContainer.at(j), awayContainer.at(j)));
			}
			this->matchPair_.push_back(dayMatch);
			// 入れ替え
			awayContainer.insert(awayContainer.begin(), homeContainer.at(1));
			homeContainer.push_back(awayContainer.back());
			homeContainer.erase(++(homeContainer.begin()));     // 1 番目の要素を消す
			awayContainer.pop_back();
			dayMatch.clear();
		}
	}


private:
	const std::vector<Team>&            teamList_;
	std::vector<std::vector<std::pair<unsigned int, unsigned int> > >    matchPair_;
};

// 出力
std::ostream& operator<<(std::ostream& os, const RoundRobin& param) throw();




int goalNum(const Team& attacker, const Team& defencer) throw();


int homeGoalNum(const Team& attacker, const Team& defencer) throw();
int awayGoalNum(const Team& attacker, const Team& defencer) throw();


struct OneMatchResult
{
private:
	friend std::ostream& operator<<(std::ostream& os, const OneMatchResult& param) throw();

public:

	OneMatchResult(const Team& home, const Team& away, unsigned int maxNameSize) throw()
		: home_(home.team())
		, homeGoal_(0)
		, away_(away.team())
		, awayGoal_(0)
		, maxNameSize_(maxNameSize)
	{
		this->culcGoalPoints(home, away);
	}

	void culcGoalPoints(const Team& home, const Team& away) throw() {
		this->homeGoal_ = goalNum(home, away);
		this->awayGoal_ = goalNum(away, home);
	}

	OneMatchResult(const std::string& home, unsigned int homeGoal, const std::string& away, unsigned int awayGoal, unsigned int maxNameSize) throw()
		: home_(home)
		, homeGoal_(homeGoal)
		, away_(away)
		, awayGoal_(awayGoal)
		, maxNameSize_(maxNameSize)
	{
	}

	void maxNameSize(unsigned int maxNameSize) throw() { this->maxNameSize_ = maxNameSize; }

//	OneMatchResult& operator=(const OneMatchResult& other) {
//		this->maxNameSize_ = other.maxNameSize_;
//		this->home_ = other.home_;
//		this->homeGoal_ = other.homeGoal_;
//		this->away_ = other.away_;
//		this->awayGoal_ = other.awayGoal_;
//		return *this;
//	}

	unsigned int    maxNameSize_;
	std::string     home_;
	unsigned int    homeGoal_;
	std::string     away_;
	unsigned int    awayGoal_;
};
// 出力
std::ostream& operator<<(std::ostream& os, const OneMatchResult& param) throw();


OneMatchResult matchup(Team& home, Team& away, unsigned int restDay, unsigned int maxNameSize) throw(std::invalid_argument);


struct OneDayMatchResult
{
private:
	friend std::ostream& operator<<(std::ostream& os, const OneDayMatchResult& param) throw();

public:

	OneDayMatchResult(unsigned int day, const std::vector<Team>& teamList) throw()
		: day_(day)
		, maxNameSize_(0)
	{
		for (std::vector<Team>::const_iterator ite = teamList.begin(); ite != teamList.end(); ++ite) {
			if (ite->team().size() > this->maxNameSize_) {
				this->maxNameSize_ = ite->team().size();
			}
		}
	}

	OneDayMatchResult(unsigned int day, const std::vector<std::pair<unsigned int, unsigned int> >& matchPair, std::vector<Team>& teamList) throw()
		: day_(day)
		, maxNameSize_(0)
	{
		this->culcGoalPoints(matchPair, teamList);
	}

	void culcGoalPoints(const std::vector<std::pair<unsigned int, unsigned int> >& matchPair, std::vector<Team>& teamList) throw() {
		for (std::vector<Team>::const_iterator ite = teamList.begin(); ite != teamList.end(); ++ite) {
			if (ite->team().size() > this->maxNameSize_) {
				this->maxNameSize_ = ite->team().size();
			}
		}

		std::pair<unsigned int, unsigned int> pair;
		for (unsigned int i = 0; i < matchPair.size(); ++i) {
			pair = matchPair.at(i);
			this->result_.push_back(OneMatchResult(teamList.at(pair.first), teamList.at(pair.second), this->maxNameSize_));
			teamList.at(pair.first).addGoal(this->result_.back().homeGoal_);
			teamList.at(pair.first).addLost(this->result_.back().awayGoal_);
			teamList.at(pair.second).addGoal(this->result_.back().awayGoal_);
			teamList.at(pair.second).addLost(this->result_.back().homeGoal_);
		}
	}


	void add(const OneMatchResult& result) throw() {
		this->result_.push_back(result);
	}

	unsigned int maxNameSize() const throw() { return this->maxNameSize_; }

//	OneDayMatchResult& operator=(const OneDayMatchResult& other) {
//		this->day_ = other.day_;
//		this->maxNameSize_ = other.maxNameSize_;
//		this->result_ = other.result_;
//		return *this;
//	}


	unsigned int                day_;
	unsigned int                maxNameSize_;
	std::vector<OneMatchResult> result_;
};
// 出力
std::ostream& operator<<(std::ostream& os, const OneDayMatchResult& param) throw();



class SeasonResult {
private:
	friend std::ostream& operator<<(std::ostream& os, const SeasonResult& param) throw();

public:

	SeasonResult(std::vector<Team>& teamList, unsigned int roop = 1) throw()
		: teamList_(teamList)
		, schedule_(teamList)
		, roop_(roop)
		, day_(0)
	{
		this->culcGoalPoints();
	}


	void culcGoalPoints() throw() {
		for (unsigned int roopTimes = 0; roopTimes < this->roop_; ++roopTimes) {
			for (unsigned int i = 0; i < this->schedule_.day(); ++i) {
				std::vector<std::pair<unsigned int, unsigned int> > pair = this->schedule_.matchList(i);
				this->result_.push_back(OneDayMatchResult(i + this->schedule_.day()*roopTimes, pair, this->teamList_));
			}
		}

		for (std::vector<Team>::iterator ite = this->teamList_.begin(); ite != this->teamList_.end(); ++ite) {
			ite->goalPoints(ite->goal());
			ite->saveGoalPoints(ite->goal());
			ite->win(0);
			ite->lose(0);
			ite->draw(0);
			ite->goal(0);
			ite->lost(0);
		}

		//this->record_.push_back(this->result_);
		this->result_.clear();
	}

	void stepADay() throw() {
		std::vector<std::pair<unsigned int, unsigned int> > match = this->schedule_.matchList(this->day_);

		OneDayMatchResult container(this->day_, this->teamList_);
		for (std::vector<std::pair<unsigned int, unsigned int> >::iterator ite = match.begin(); ite != match.end(); ++ite) {
			container.add(matchup(this->teamList_.at(ite->first), this->teamList_.at(ite->second), this->schedule_.day()*this->roop_-this->day_, container.maxNameSize()));
		}
		this->result_.push_back(container);
		++this->day_;
	}

	template<typename Sorter>
	void sortTeam(const Sorter& functor) throw() {
		std::sort(this->teamList_.begin(), this->teamList_.end(), functor);
	}

	/**
	 * コメントテスト
	 */
	void finishSeazon() throw();

	bool isAllScheduleFinished() const throw() { return (this->schedule_.day()*this->roop_ == this->day_); }

private:
	std::vector<Team>&              teamList_;
	std::vector<OneDayMatchResult>  result_;
	std::vector<std::vector<OneDayMatchResult> > record_;
	RoundRobin                      schedule_;
	unsigned int                    roop_;
	unsigned int                    day_;
};

// 出力
std::ostream& operator<<(std::ostream& os, const SeasonResult& param);



#endif

