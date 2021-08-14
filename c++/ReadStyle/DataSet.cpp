
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <limits>
#include <sstream>
#include <cassert>
#include "DataSet.hpp"
#include "Functor.hpp"


/**----------------------------------------------------
 * @brief     getter of DataCount
 * @return    Reference of std::pair<int, int> type.
 *---------------------------------------------------*/
void DataSet::sortDataCount() throw() {
	this->dataCount.sort(FunctorNumGreaterSort());
}



/**----------------------------------------------------
 * @brief �ǂݎ�����f�[�^����͂��� dataCount �Ɋi�[���Ă���
 *---------------------------------------------------*/
void DataSet::addData(std::string race_, std::string data_) throw()
{
	// �l��Ɋւ��Ă̒���
	int raceCheck = std::numeric_limits<int>::max();
	std::istringstream is(race_);
	is >> raceCheck;
	if (raceCheck == std::numeric_limits<int>::max()) {
		so::out << "�l��ǂݎ��ɂ����ς����܂����B" << so::endl;
		assert(0);
		return;
	}

	// �擾�����f�[�^�� int �ɕϊ�
	int integer = std::numeric_limits<int>::max();
	is.str("");
	is.clear();
	is.str(data_);
	is >> integer;

	// �ǂݎ�ꂽ���̊m�F
	if (integer == std::numeric_limits<int>::max()) {
		if (data_ == "") {
			// ���������Ă��Ȃ��\���͂������ɂ���̂�
		} else {
			// ����L��B�Ȃɂ��ǂݎ��Ɏ��s����\���ɂȂ��Ă���ɈႢ�Ȃ�
			so::out << data_ << so::endl;
			assert(false);
		}
	}

	// �t������
	bool checker = false;
	for (std::list<Data>::iterator ite = this->dataCount.begin(); ite != this->dataCount.end(); ++ite) {
		if (ite->race == raceCheck && ite->ID == integer) {
			++(ite->num);
			checker = true;
			break;
		}
	}

	// ������Ȃ������ꍇ
	if (checker == false) {
		this->dataCount.push_back(Data(raceCheck, integer, 1));
	}
}



