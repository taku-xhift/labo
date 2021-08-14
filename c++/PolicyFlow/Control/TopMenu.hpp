
#ifndef TOPMENU_HPP_INCLUDED
#define TOPMENU_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------


/**
 * @brief 
 *          
 * @author  Takuya Shishido
 * @date    2010.10.13 13:03:57
 * @version 0.01, Shishido Takuya, 2010.10.13 13:03:57
 */


//! \brief TopMenu ��ʊǗ�
class TopMenuControl {
public:
	//!< \brief method ����
	ModelerInterfaceContainer update();

	bool getFlagState(Question question_) { return this->flagSet[question_]; }

	LeagueFlow() : step(0) {
		this->flagSet.reset();
	}


protected:
	~TopMenuControl() {}

private:

	std::bitset<Question_Max>   flagSet;    //!< getFlagState �p
};

#endif

