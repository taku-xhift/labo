

#include <iostream>

enum
{
	PR_GK,
	PR_LIB,//SW、LIB、CBの順に統一したいが怖いので手は出さず(ここも含めて6箇所)
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

};

namespace {

	const int lowestOverAll = 6500;   //!< 総合値の最小の値

	const float positionOffset[PR_MAX] = {
		-2203.00,
		-3720.00,
		-6186.00,
		-6186.00,
		-4194.00,
		-4765.00,
		-5178.00,
		-5178.00,
		-4359.00,
		-4603.00,
		-3348.00,
		-5175.00,
		-5175.00,
	};      //!< ポジションごとの補正値

}


/************************************************
 * @brief       マイチームとして作成時の補正率を計算する
 * @param       対象となるパラメータ
 * @return      補正率。これを全パラメータにかけなおす
 * @except      ZeroDevisionException   0 割りが発生する状況
 ***********************************************/
float getMyTeamPlayerOffset(int overAll, int pos) throw() {
	// 一定値以下の選手は何もしない
	if (overAll < lowestOverAll) {
		return 1.0f;
	}

	const float denominator = overAll - positionOffset[pos];
	return (lowestOverAll - positionOffset[pos])/denominator;
}


/************************************************
 * @brief       選手獲得で取得した選手用の補正値計算
 * @param       対象となるパラメータ
 * @return      補正率。これを全パラメータにかけなおす
 * @except      ZeroDevisionException   0 割りが発生する状況
 ***********************************************/
float getMyTeamNewPlayerOffset(int overAll, int pos) throw() {
	// 一定値以下の選手は何もしない
	if (overAll > lowestOverAll) {
		return 1.0f;
	}

	const weFloat denominator = overAll + positionOffset[pos];
	return (lowestOverAll + positionOffset[pos])/denominator;
}


int main(int argc, char* argv[]) {
	std::cout << "BasePara : " << argv[0] << std::endl;
	std::cout << "overAll  : " << argv[1] << std::endl;
	std::cout << "pos      : " << argv[2] << std::endl;
	std::cout << "offsetted: " << argv[0]*getMyTeamNewPlayerOffset(argv[1], argv[2]) << std::endl;
}
