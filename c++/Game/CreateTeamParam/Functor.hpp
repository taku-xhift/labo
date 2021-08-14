
#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

#pragma warning(disable:4996)
#pragma warning(disable:4290)

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <assert.h>
#include "Define.hpp"
#include "DataType.hpp"

struct Sum
{
	template<typename Functor>
	Sum(const std::vector<DispParam>& list, Functor& functor) throw()
		: sum_(0)
		, count_(0)
	{
		Functor functor_ = std::for_each(list.begin(), list.end(), functor);
		this->sum_ = functor_.sum();
		this->count_ = functor_.count();
	}


	int average() const throw(DevideByZero) {
		if (this->count_ != 0) {
			return this->sum_/this->count_;
		} else {
			assert(0);
			throw DevideByZero(ExceptionMessage("DevideByZero"));
		}
	}

	int sum() const throw() { return this->sum_; }
	int count() const throw() { return this->count_; }

private:
	int sum_;
	int count_;
};

struct SumBase {
	SumBase() : sum_(0), count_(0) {}
	virtual ~SumBase() {}
	virtual void add(int param) throw() { this->sum_ += param; ++this->count_; }

	int sum() const throw() { return this->sum_; }
	int count() const throw() { return this->count_; }

private:
	int sum_;
	int count_;
};

struct SumAttack : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.offence()); }
};

struct SumDefence : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.defence());}
};

struct SumStamina : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.stamina()); }
};

struct SumSpeed : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.speed()); }
};

struct SumPower : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.power()); }
};

struct SumDribble : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.dribble()); }
};

struct SumPass : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.pass()); }
};

struct SumGKSkill : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.gkSkill()); }
};

struct SumConnection : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.connection()); }
};

struct SumStar : public SumBase {
	void operator()(const DispParam& param) throw() { this->add(param.star()); }
};

struct SumAttackWithFW : public SumBase {
	void operator()(const DispParam& param) throw() {
		if (param.position() == PosList_CF
			|| param.position() == PosList_ST
			|| param.position() == PosList_OMF
			)
		{
			this->add(param.offence());
		}
	}
};

struct SumDefenceWithDF : public SumBase {
	void operator()(const DispParam& param) throw() {
		if (param.position() == PosList_CMF
			|| param.position() == PosList_CB
			|| param.position() == PosList_DMF
			|| param.position() == PosList_WG
			)
		{
			this->add(param.defence());
		}
	}
};

struct SumPassWithMF : public SumBase {
	void operator()(const DispParam& param) throw() {
		if (param.position() == PosList_CMF
			|| param.position() == PosList_OMF
			|| param.position() == PosList_DMF
			|| param.position() == PosList_SMF
			|| param.position() == PosList_CMF
			//|| param.position() == PosList_SB
			)
		{
			this->add(param.pass());
		}
	}
};

struct SumGKSkillWithGK : public SumBase {
	void operator()(const DispParam& param) throw() {
		if (param.position() == PosList_GK) {
			this->add(param.gkSkill());
		}
	}
};
class PlayerParamMakeAverage
{
public:
	//! \brief constructor
	PlayerParamMakeAverage() throw()
		: importance_(.0f)
		, param_(.0f)
	{
	}

	void add(float importance, float param) throw() {
		this->importance_ += importance;
		this->param_      += importance * param;
	}

	virtual int get() const throw() = 0;


protected:

	unsigned char averageGet(float base, float add) const throw() {
		float	point = .0f;
		float	importance = .0f;
		float	param = .0f;

		importance = this->importance_;
		param      = this->param_;

		point = (this->param_/this->importance_) * base + add;
		point = std::min(point, 99.0f);
		return static_cast<unsigned char>(point);
	}

	// accessor
	void importance(float importance) throw() { this->importance_ = importance; }
	void param(float param) throw() { this->param_ = param; }
	float importance() const throw() { return this->importance_; }
	float param() const throw() { return this->param_; }

private:
	float importance_;
	float param_;
};

class AttackDispParam
	: public PlayerParamMakeAverage
{
public:
	AttackDispParam(float offence, float shotacc, float shottech) throw() {
		this->add(2, offence);
		this->add(1, shotacc);
		this->add(1, shottech);
	}

	int get() const throw() {
		return this->averageGet(1.02f, .0f);
	}
};

class DefenceDispParam
	: public PlayerParamMakeAverage
{
public:
	DefenceDispParam(float defence) throw() {
		this->add(1, defence);
	}

	int get() const throw() {
		return std::max(static_cast<unsigned char>(30), this->averageGet(1.0f, .0f));
	}
};

class StaminaDispParam
	: public PlayerParamMakeAverage
{
public:
	StaminaDispParam(float stamina) throw() {
		this->add(1, stamina);
	}

	int get() const throw() {
		return this->averageGet(1.0f, .0f);
	}
};

class SpeedDispParam
	: public PlayerParamMakeAverage
{
public:
	SpeedDispParam(float dash, float kasoku, float aggility) throw() {
		this->add(2, dash);
		this->add(1, kasoku);
		this->add(1, aggility);
	}

	int get() const throw() {
		return std::max(static_cast<unsigned char>(30), this->averageGet(.97f, 4.0f));
	}
};

class PowerDispParam
	: public PlayerParamMakeAverage
{
public:
	PowerDispParam(float atari, float shotpower) throw() {
		this->add(2, atari);
		this->add(1, shotpower);
	}

	int get() const throw() {
		return this->averageGet(1.01f, .0f);
	}
};

class DribbleDispParam
	: public PlayerParamMakeAverage
{
public:
	DribbleDispParam(float trap, float dribble, float dribbleSpeed) throw() {
		this->add(1, trap);
		this->add(2, dribble);
		this->add(1, dribbleSpeed);
	}

	int get() const throw() {
		return std::max(static_cast<unsigned char>(30), this->averageGet(.98f, .0f));
	}
};

class PassDispParam
	: public PlayerParamMakeAverage
{
public:
	PassDispParam(float trap, float passacc, float longacc) throw() {
		this->add(1, trap);
		this->add(2, passacc);
		this->add(2, longacc);
	}

	int get() const throw() {
		return std::max(static_cast<unsigned char>(30), this->averageGet(1.01f, .0f));
	}
};

class GkSkillDispParam
	: public PlayerParamMakeAverage
{
public:
	GkSkillDispParam(float gk_skill) throw() {
		this->add(1, gk_skill);
	}

	int get() const throw() {
		return this->averageGet(1.0f, .0f);
	}
};


struct FindTeamName {
	FindTeamName(std::string team) : team_(team) {}

	template<typename ValueType>
	bool operator()(const ValueType& value) throw() {
		return (value.team().compare(this->team_) == 0);
	}

	std::string team_;
};



class TeamSelector {
public:
	TeamSelector(std::string teamName, bool equality = true) throw()
		: teamName_(teamName)
		, equality_(equality)
	{
	}

	bool operator()(const DispParam& param) {
		if (this->equality_) {
			return (param.team().compare(this->teamName_) == 0);
		} else {
			return (param.team().compare(this->teamName_) != 0);
		}
	}

	std::string teamName_;
	bool equality_;
};


class Print {
public:
	template<typename ValueType>
	void operator()(const ValueType& value) throw() {
		//so::out << value << so::endl;
		so::out << value << so::endl;
	}
};


struct SortByPointsGreater {

	bool operator()(const Team& lhs, const Team& rhs) {
		if (lhs.points() == rhs.points()) {
			return lhs.goalDifference() > rhs.goalDifference();
		} else {
			return lhs.points() > rhs.points();
		}
	}
};


struct SortByGoalPointsGreater {
	bool operator()(const Team& lhs, const Team& rhs) {
		return lhs.record().goalPoints > rhs.record().goalPoints;
	}
};


struct SortByAllSeasonPointsGreater {
	bool operator()(Team& lhs, Team& rhs) {
		return lhs.allRankSum() < rhs.allRankSum();
	}
};



#endif

