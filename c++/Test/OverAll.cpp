

#include <iostream>

enum
{
	PR_GK,
	PR_LIB,//SW�ALIB�ACB�̏��ɓ��ꂵ�������|���̂Ŏ�͏o����(�������܂߂�6�ӏ�)
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

	const int lowestOverAll = 6500;   //!< �����l�̍ŏ��̒l

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
	};      //!< �|�W�V�������Ƃ̕␳�l

}


/************************************************
 * @brief       �}�C�`�[���Ƃ��č쐬���̕␳�����v�Z����
 * @param       �ΏۂƂȂ�p�����[�^
 * @return      �␳���B�����S�p�����[�^�ɂ����Ȃ���
 * @except      ZeroDevisionException   0 ���肪���������
 ***********************************************/
float getMyTeamPlayerOffset(int overAll, int pos) throw() {
	// ���l�ȉ��̑I��͉������Ȃ�
	if (overAll < lowestOverAll) {
		return 1.0f;
	}

	const float denominator = overAll - positionOffset[pos];
	return (lowestOverAll - positionOffset[pos])/denominator;
}


/************************************************
 * @brief       �I��l���Ŏ擾�����I��p�̕␳�l�v�Z
 * @param       �ΏۂƂȂ�p�����[�^
 * @return      �␳���B�����S�p�����[�^�ɂ����Ȃ���
 * @except      ZeroDevisionException   0 ���肪���������
 ***********************************************/
float getMyTeamNewPlayerOffset(int overAll, int pos) throw() {
	// ���l�ȉ��̑I��͉������Ȃ�
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
