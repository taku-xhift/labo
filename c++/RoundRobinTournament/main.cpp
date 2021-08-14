


#include <iostream>
#include <vector>
#include <utility>


class MatchPairList {
public:
	std::vector<std::pair<int, int> > matchPair_;

	friend std::ostream& operator<<(std::ostream& os, const MatchPairList& obj);

};

// �o�͗p��<<���Z�q��`
std::ostream& operator<<(std::ostream& os, const MatchPairList& obj)
{
	for (std::vector<std::pair<int, int> >::const_iterator ite = obj.matchPair_.begin();
		 ite != obj.matchPair_.end(); ++ite)
	{
		std::cout << "Match of " << ite->first << " : " << ite->second << "\n";
	}

	return os;
}



/****************************************************************
 * @brief min <= return < max �Ɏ��܂鐔����Ԃ�
 * @note    max �� = �ɂȂ鎖�͖������Amin �Ɠ����ɂȂ邱�Ƃ͂���
 * @param[in]   min     �ŏ��l
 * @param[in]   max     �ő�l
 * @param[in]   num     �ϊ����������l
 * @return      min <= return < max �Ɏ��܂鐔��
 ***************************************************************/
int getRoopNum(int min, int max, int num) {
	while (!(min <= num && num < max)) {
		if (max <= num) {
			num -= max - min;
		} else if (num < min) {
			num += max - min;
		}
	}

	return num;
}


/****************************************************************
 * @brief RoundRobin �̃��[�v���𖞂����z��
 * @param[in]   teamNum     ���[�O�̎Q���`�[����
 * @return      ���[�v�𖞂����z�� (1, 2, 5, 4, 3 ��)
 ***************************************************************/
std::vector<int> getList(int teamNum) {
	std::vector<int> array(teamNum-1);

	for (int i = 1; i < teamNum; ++i) {
		if (i < teamNum/2) {
			array.at(i-1) = i;
		} else {
			array.at(i-1) = 3*teamNum/2-i-1;
		}
	}

	return array;
}


/****************************************************************
 * @brief �����ɉ������ΐ�\���擾����
 * @param[in]   teamNum     ���[�O�̎Q���`�[����
 * @param[in]   day         �ߐ�
 * @return      �ΐ�\�i0-3 ���A0 �X�^�[�g�̔ԍ��̃y�A�̃��X�g��Ԃ��j
 ***************************************************************/
MatchPairList getMatchPairList(int teamNum, int day) throw() {
	MatchPairList pair;

	// �z������擾����
	const std::vector<int>& matchArray = getList(teamNum);

	// 0 �Ԗڂ̑ΐ푊������߂�ߒ�
	const int accessNumber = getRoopNum(0, matchArray.size(), teamNum-1+day-1);
	const int num = matchArray.at(accessNumber);
	const int matchTeam = getRoopNum(1, matchArray.size()+1, num);

	// 0 �Ԗڂ����ʒu��ύX�����ΐ푊�肾����ύX����
	pair.matchPair_.push_back(std::make_pair(0, matchTeam));

	// 0 �Ԗڈȍ~�̃y�A�����߂�
	for (int i = 1; i < teamNum/2; ++i) {
		const int leftAccessNumber = getRoopNum(0, matchArray.size(), i+day-1);
		const int left = matchArray.at(leftAccessNumber);
		const int rightAccessNumber = getRoopNum(0, matchArray.size(), teamNum-i-1+day-1);
		const int right = matchArray.at(rightAccessNumber);
		pair.matchPair_.push_back(std::make_pair(left, right));
	}

	return pair;
}



int main() {
	int teamNum = 8;
	for (int i = 0; i < teamNum; ++i) {
		std::cout << getMatchPairList(teamNum, i) << std::endl;
	}

	//for (int i = 0; i < teamNum; ++i) {
	//	std::cout << getListNumber(teamNum, i) << std::endl;
	//}


	//for (int i = 0; i < teamNum; ++i) {
	//	std::cout << getListNumber(teamNum, getListNumber(teamNum, getRoopNum(0, teamNum, teamNum/2+1))) << std::endl;
	//}
}
