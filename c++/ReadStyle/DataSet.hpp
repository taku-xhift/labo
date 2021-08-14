
#ifndef DATASET_HPP_INCLUDED
#define DATASET_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include <list>
#include "StreamObject.hpp"



struct Data
{
	Data(int race_, int ID_, int num_) : race(race_), ID(ID_), num(num_) {}

	int race;       //!< �l��
	int ID;         //!< �ԍ�
	int num;        //!< ��
};


/**
 * @brief �f�[�^����܂Ƃ߂ɂ������́B
 * @note    �܂Ƃ߂�f�[�^�̓����o�ɂ�����̂őS�āB
 * @author  Takuya Shishido
 * @date    2010.03.30 11:11:25
 * @version 0.01, Shishido Takuya, 2010.03.30 11:11:25
 */
class DataSet
{
public:


	/**----------------------------------------------------
	 * @brief     getter and setter
	 * @return    Reference of std::string type.
	 *---------------------------------------------------*/
	const std::string& getDataName() const throw() { return this->dataName; }
	void setDataName(const std::string& dataName_) throw() { this->dataName = dataName_; }
	const std::list<Data>::const_iterator getDataCountIterator() const { return this->dataCount.begin(); }
	const std::list<Data>::const_iterator getDataCountIteratorEnd() const { return this->dataCount.end(); }


	/**----------------------------------------------------
	 * @brief     getter of DataCount
	 * @return    Reference of std::pair<int, int> type.
	 *---------------------------------------------------*/
	void sortDataCount() throw();


	/**----------------------------------------------------
	 * @brief �ǂݎ�����f�[�^����͂��� dataCount �Ɋi�[���Ă���
	 *---------------------------------------------------*/
	void addData(std::string race_, std::string data_) throw();


	/**----------------------------------------------------
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os               �X�g���[���I�u�W�F�N�g
	 * @param[in]  cityParameter    �o�̓I�u�W�F�N�g
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const DataSet& dataSet_)
	{
		os << "dataName: " << dataSet_.dataName << std::endl;
		os << "��̓I�ȃf�[�^" << std::endl;
		for (std::list<Data>::const_iterator ite = dataSet_.dataCount.begin(); ite != dataSet_.dataCount.end(); ++ite) {
			os << "race = " << ite->race << ", ID = " << ite->ID << ", number = " << ite->num << std::endl;
		}
		return os;
	}


private:

	std::string         dataName;         //!< �f�[�^�̖��O
	std::list<Data>     dataCount;        //!< �f�[�^�̃J�E���g�B�P�߂����, �Q�߂����̐�
};






#endif

