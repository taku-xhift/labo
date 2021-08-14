
//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "StreamObject.hpp"
#include "DataSet.hpp"
#include "Functor.hpp"


//---------------------------------------------------------
//  define
//---------------------------------------------------------
namespace {
	const std::string readFileName = "style.csv";       //!< �ǂݍ��ރt�@�C���̖��O
	const std::string resultFileName = "result.txt";    //!< �������ތ��ʃf�[�^�̃t�@�C����
	const int invalidNum = 11;      //!< �f�[�^�̒��ł���͂̕K�v�����f�[�^�̐擪����̐�
}


//---------------------------------------------------------
//  declaration
//---------------------------------------------------------
class DataSet;


//---------------------------------------------------------
//  prototype
//---------------------------------------------------------
void readFiles(std::string fileName_, std::vector<DataSet> dataContainer_) throw();
void writeFiles(std::string fileName_) throw();
template<typename Type> std::vector<Type> eraceVector(const std::vector<Type>& container_, int num_) throw();





//---------------------------------------------------------
//  entry point
//---------------------------------------------------------
int main()
{
	std::vector<DataSet> dataContainer;

	readFiles(readFileName, dataContainer);

	return 0;
}



/**-------------------------------------------------------------
 * @breif �t�@�C���Ǎ��݊֐��B
 *          csv �t�@�C���Ǎ��݂����A���͌��ʂ��t�@�C���ɏo�͂܂ł���B
 * @param[in]   fileName_   �ǂݍ��݃t�@�C��
 *-------------------------------------------------------------*/
void readFiles(std::string fineName_, std::vector<DataSet> dataContainer_) throw()
{
	std::ifstream ifs(fineName_.c_str());
	std::string fileData;

	// �t�@�C�����ǂݍ��߂����`�F�b�N���s��
	assert(ifs.good());

	// �P�s�ړǍ���
	std::getline(ifs, fileData);

	std::vector<std::string> dataName;
	boost::algorithm::split(dataName, fileData, boost::is_any_of(","));


	// �T�C�Y�m�ہA���O�Z�b�g
	dataContainer_.resize(dataName.size());
	for (unsigned int i = 0; i < dataName.size(); ++i) {
		dataContainer_.at(i).setDataName(dataName.at(i));
	}


	//-----------------------------------------------------
	//  �t�@�C���̖{�i�I�ȓǍ���
	//      �������A�l��(�X�L���J���[)��񂪍Ő擪�ɗ��Ă��Ȃ��Ƃ����Ȃ��B
	//      ����ȊO�̏ꏊ�ɂ���̂ł���� addData �̑�������
	//      �K�؂Ȕԍ��̃f�[�^��n���悤�ɂ��Ă��������B
	//      �������� excel �̒i�K�ŕ��ёւ���Ƃ��B
	//      ���������Ή�����̖ʓ|�Ȃ�ŁB
	//-----------------------------------------------------
	int counter = 0;    // �S�̈���p�B�t���[�Y���Ԃ������ƃh�L�h�L����̂�
	while (std::getline(ifs, fileData)) {
		boost::algorithm::split(dataName, fileData, boost::is_any_of(","));
		// �Ⴆ�� �@ ��ǂݎ���Ă���ꍇ�� dataName �� �@ �ɂ����镔������͂�����
		for (unsigned int i = 0; i < dataContainer_.size(); ++i) {
			dataContainer_.at(i).addData(dataName.at(0), dataName.at(i));
		}
		++counter;
		std::cout << "counter = " << counter << std::endl;
	}

	// �\�[�g
	std::for_each(dataContainer_.begin(), dataContainer_.end(), FunctorSortDataSet());

	// ���ʂ��o�͂���
	for (std::vector<DataSet>::iterator ite = dataContainer_.begin(); ite != dataContainer_.end(); ++ite) {
		so::out << (*ite) << so::endl;
	}
}



/**-------------------------------------------------------------
 * @breif �t�@�C���������݊֐��B
 *          csv �t�@�C���Ǎ��݂����A���͌��ʂ��t�@�C���ɏo�͂܂ł���B
 * @param[in]   fileName_   �ǂݍ��݃t�@�C��
 *-------------------------------------------------------------*/
void writeFiles(std::string fineName_) throw()
{

}




/**-------------------------------------------------------------
 * @breif vector �^�̃f�[�^�̐擪���� num_ ��������������
 * @param[in]   num_    �������鐔
 *-------------------------------------------------------------*/
template<typename Type>
std::vector<Type> eraceVector(const std::vector<Type>& container_, int num_) throw()
{
	// �I���W�i���f�[�^����R�s�[
	std::vector<Type> data = container_;

	// �C�e���[�^���w�肳�ꂽ���i�߂ď���
	std::vector<Type>::iterator ite = data.begin();
	std::advance(ite, num_);
	data.erase(data.begin(), ite);

	return data;
}

