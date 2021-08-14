
#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

/**
 * @brief list �� std::pair �̗v�f�� second �̑傫�����ɕ��ёւ���
 * @note    �܂Ƃ߂�f�[�^�̓����o�ɂ�����̂őS�āB
 * @author  Takuya Shishido
 * @date    2010.03.30 15:26:25
 * @version 0.01, Shishido Takuya, 2010.03.30 15:26:25
 */
class FunctorSecondGreaterSort
{
public:

	FunctorSecondGreaterSort() { }

	template<typename Type>
	bool operator() (Type lhs_, Type rhs_) {
		return lhs_.second > rhs_.second;
	}
};

/**
 * @brief list �� Data �̗v�f�� num �̑傫�����ɕ��ёւ���
 * @note    �܂Ƃ߂�f�[�^�̓����o�ɂ�����̂őS�āB
 * @author  Takuya Shishido
 * @date    2010.03.31 15:35:25
 * @version 0.01, Shishido Takuya, 2010.03.31 15:35:25
 */
class FunctorNumGreaterSort
{
public:

	FunctorNumGreaterSort() { }

	template<typename Type>
	bool operator() (Type lhs_, Type rhs_) {
		// �l��ŗD��ŕ��ёւ�
		// �l��͏�������
		if (lhs_.race < rhs_.race) {
			return true;
		} else if (lhs_.race > rhs_.race) {
			return false;
		}

		// �l�킪�ꏏ�ł���΂��� ID �̐��ŕ��ёւ�
		// num �� ������
		return lhs_.num > rhs_.num;
	}
};



/**
 * @brief list �� std::pair �̗v�f�� first ����T���o��
 *
 * @author  Takuya Shishido
 * @date    2010.03.30 16:02:25
 * @version 0.01, Shishido Takuya, 2010.03.30 2010.03.30 15:26:25
 */
class FunctorFind
{
public:

	FunctorFind(int target_) : target(target_) { }

	template<typename Type>
	bool operator() (Type data_) {
		return data_.first == this->target;
	}

	int target;
};




/**
 * @brief list �� std::pair �̗v�f�� first ����T���o��
 *
 * @author  Takuya Shishido
 * @date    2010.03.30 16:02:25
 * @version 0.01, Shishido Takuya, 2010.03.30 2010.03.30 15:26:25
 */
class FunctorSortDataSet
{
public:

	FunctorSortDataSet() { }

	template<typename Type>
	void operator() (Type& data_) {
		data_.sortDataCount();
	}
};




#endif

