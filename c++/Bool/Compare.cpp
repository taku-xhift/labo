


#include <iostream>
#include <bitset>

bool isTrue() {
	return true;
}

typedef unsigned int weUint;
typedef enum
{
	PR_GK,
	PR_LIB,
	PR_SW,
	PR_CB,
	PR_SB,
	PR_DH,
	PR_WB,
	PR_CH,
	PR_SH,
	PR_OH,
	PR_WG,
	PR_ST,
	PR_CF,
	PR_NULL,
	PR_MAX

} PLAYER_POSITION;

enum SkillList {
	SKILLLIST_DRIBBLER,
	SKILLLIST_POSTPLAYER,
	SKILLLIST_POSITIONING,
	SKILLLIST_BLASTOFF,
	SKILLLIST_STRIKER,
	SKILLLIST_PLAYMAKER,
	SKILLLIST_PASSER,
	SKILLLIST_PKKICKER,
	SKILLLIST_1VS1SHOOT,
	SKILLLIST_LONGTHROGH,   // 10
	SKILLLIST_DIRECTPLAY,
	SKILLLIST_MANMARK,
	SKILLLIST_MANAGEDFLINE,
	SKILLLIST_1VS1KEEPER,
	SKILLLIST_PKKEEPER,
	SKILLLIST_OUTSIDE,
	SKILLLIST_DRIBBLEKEEP,
	SKILLLIST_LINEPOSITIONING,
	SKILLLIST_MIDDLESHOOT,
	SKILLLIST_SIDEPLAYER,   // 20
	SKILLLIST_CENTERPLAYER,
	SKILLLIST_SUPERSUB,
	SKILLLIST_SLIDING,
	SKILLLIST_COVERING,
	SKILLLIST_MAX,
};



class DispParam
{
public:

	//! \brief constructor
	DispParam() throw() {}


	//! \brief constructor
	//DispParam(const CSVPlayerData& base) throw();


	//! \brief パラメータの初期化
	void clear() throw();


//	std::string stringPosition() const throw(ConvertError);
//	void position(const std::string& position) throw(ConvertError);
	const std::string& name() const throw()             { return this->name_; }
	void name(const std::string& name) throw()          { this->name_ = name; }
	PLAYER_POSITION position() const throw()            { return this->position_; }
	void position(PLAYER_POSITION position) throw()     { this->position_ = position; }
	weUint side() const throw()                         { return this->side_; }
	void side(weUint side) throw()                      { this->side_ = side; }
	weUint offence() const throw()                      { return this->offence_; }
	void offence(weUint offence) throw()                { this->offence_ = offence; }
	weUint defence() const throw()                      { return this->defence_; }
	void defence(weUint defence) throw()                { this->defence_ = defence; }
	weUint stamina() const throw()                      { return this->stamina_; }
	void stamina(weUint stamina) throw()                { this->stamina_ = stamina; }
	weUint speed() const throw()                        { return this->speed_; }
	void speed(weUint speed) throw()                    { this->speed_ = speed; }
	weUint power() const throw()                        { return this->power_; }
	void power(weUint power) throw()                    { this->power_ = power; }
	weUint pass() const throw()                         { return this->pass_; }
	void pass(weUint pass) throw()                      { this->pass_ = pass; }
	weUint dribble() const throw()                      { return this->dribble_; }
	void dribble(weUint dribble) throw()                { this->dribble_ = dribble; }
	weUint gkSkill() const throw()                      { return this->gkSkill_; }
	void gkSkill(weUint gkSkill) throw()                { this->gkSkill_ = gkSkill; }
	weUint connection() const throw()                   { return this->connection_; }
	void connection(weUint connection) throw()          { this->connection_ = connection; }
	weUint injury() const throw()                       { return this->injury_; }
	void injury(weUint injury) throw()                  { this->injury_ = injury; }
	weUint star() const throw()                         { return this->star_; }
	void star(weUint star) throw()                      { this->star_ = star; }

	bool skillList(SkillList skill) const throw()       { return this->skillList_.test(skill); }
	void skillList(SkillList skill, bool value) throw() { this->skillList_.set(skill, value); }
	void isRegular(bool isRegular) throw()              { this->isRegular_ = isRegular; }
	bool isRegular() const throw()                      { return this->isRegular_; }


//private:
public:

//	std::string     team_;          //!< 所属しているチーム名
	std::string     name_;          //!< 自分の名前
	PLAYER_POSITION position_;      //!< ポジション
	weUint          side_;
	weUint          offence_;
	weUint          defence_;
	weUint          stamina_;
	weUint          speed_;
	weUint          power_;
	weUint          pass_;
	weUint          dribble_;
	weUint          gkSkill_;
	weUint          connection_;    //!< 連携
	weUint          injury_;        //!< 怪我し易さ
	weUint          star_;          //!< スター性
	bool            isRegular_;     //!< true でレギュラー

	std::bitset<SKILLLIST_MAX> skillList_;
};


int main() {
	DispParam param;
	param.name_ = "D. GIMﾃ丑EZ";
	param.position_ = PR_GK;
	param.side_ = 2;
	param.offence_ = 36;
	param.defence_ = 77;
	param.stamina_ = 60;
	param.speed_ = 68;
	param.power_ = 78;
	param.pass_ = 56;
	param.dribble_ = 52;
	param.gkSkill_ = 77;
	param.connection_ = 71;
	param.injury_ = 0;
	param.star_ = 2;
	param.isRegular_ = true;

		std::cout << "true => " << true << std::endl;
		std::cout << "false => " << false << std::endl;
		std::cout << "param.isRegular_ => " << param.isRegular_ << std::endl;
		std::cout << "param.isRegular() => " << param.isRegular() << std::endl;
		std::cout << "(param.isRegular() == true) => " << (param.isRegular() == true) << std::endl;
		std::cout << "(param.isRegular() != true) => " << (param.isRegular() != true) << std::endl;
		std::cout << "(param.isRegular() == false) => " << (param.isRegular() == false) << std::endl;
		std::cout << "(param.isRegular() != false) => " << (param.isRegular() != false) << std::endl;


	if (param.isRegular() == true) {
		std::cout << "return true;" << std::endl;
	}
}


