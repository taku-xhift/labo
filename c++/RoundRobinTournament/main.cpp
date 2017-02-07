


#include <iostream>
#include <vector>
#include <utility>


class MatchPairList {
public:
	std::vector<std::pair<int, int> > matchPair_;

	friend std::ostream& operator<<(std::ostream& os, const MatchPairList& obj);

};

// 出力用の<<演算子定義
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
 * @brief min <= return < max に収まる数字を返す
 * @note    max と = になる事は無いが、min と同じになることはある
 * @param[in]   min     最小値
 * @param[in]   max     最大値
 * @param[in]   num     変換したい数値
 * @return      min <= return < max に収まる数字
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
 * @brief RoundRobin のループ順を満たす配列
 * @param[in]   teamNum     リーグの参加チーム数
 * @return      ループを満たす配列 (1, 2, 5, 4, 3 等)
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
 * @brief 日程に沿った対戦表を取得する
 * @param[in]   teamNum     リーグの参加チーム数
 * @param[in]   day         節数
 * @return      対戦表（0-3 等、0 スタートの番号のペアのリストを返す）
 ***************************************************************/
MatchPairList getMatchPairList(int teamNum, int day) throw() {
	MatchPairList pair;

	// 配列情報を取得する
	const std::vector<int>& matchArray = getList(teamNum);

	// 0 番目の対戦相手を決める過程
	const int accessNumber = getRoopNum(0, matchArray.size(), teamNum-1+day-1);
	const int num = matchArray.at(accessNumber);
	const int matchTeam = getRoopNum(1, matchArray.size()+1, num);

	// 0 番目だけ位置を変更せず対戦相手だけを変更する
	pair.matchPair_.push_back(std::make_pair(0, matchTeam));

	// 0 番目以降のペアを決める
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
