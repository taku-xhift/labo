
#ifndef CITY_HPP_INCLUDED
#define CITY_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <list>
#include "City.hpp"
#include "StreamObject.hpp"


namespace NewMode {

//-----------------------------------------------------
//  decralation
//-----------------------------------------------------
class GameManager;



/**
 * @brief �X�p�����[�^�N���X
 *          �R���X�g���N�^�ŊX�̃p�����[�^�����Ă�����
 * @author  Takuya Shishido
 * @date    2009.10.20 23:05:43
 * @version 0.01, Shishido Takuya, 2009.10.20 23:05:43
 */
struct CityParameter
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	CityParameter();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~CityParameter();


	/**----------------------------------------------------
	 * @brief �������֐�
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os               �X�g���[���I�u�W�F�N�g
	 * @param[in]  cityParameter    �o�̓I�u�W�F�N�g
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const CityParameter& cityParameter)
	{
		os << "level : " << cityParameter.level << std::endl;
		os << "income : " << cityParameter.income << std::endl;
		os << "node : " << cityParameter.node << std::endl;
		os << "neighbor : " << cityParameter.neighbor << std::endl;
		os << "group : " << cityParameter.group << std::endl;
		os << "power : " << cityParameter.power << std::endl;
		os << "importance : " << cityParameter.importance << std::endl;
		os << "cityID : " << cityParameter.cityID << std::endl;
		os << "name : " << cityParameter.name << std::endl;

		return os;
	}



	/**----------------------------------------------------
	 * @brief      ���ۂɏo�͂��Ă��镔��
	 * @note        �������̂� std::cout �� std::ofstream ���g���Ă���B
	 * @param[in]    streamObject   �o�͂Ɏg���Ă���N���X�f�[�^
	 * @param[in]    data           �o�͂���\��̃f�[�^
	 *---------------------------------------------------*/
	friend so::StreamObject& operator<<(so::StreamObject& streamObject, const CityParameter& data)
	{
		//-----------------------------------------------------
		//  �t�@�C���Ɋւ��鏈��
		//-----------------------------------------------------
		std::ofstream fout( streamObject.getFilename().c_str(), std::ios::app ); // test.txt ��ǋL���[�h�ŊJ��

		// �J���Ȃ������ꍇ�͏I��
		if( fout.fail() )
		{
			std::cout << "file is nothing." << std::endl;
			return streamObject;
		}

		// �o��
		fout << data;

		// �t�@�C�������
		fout.close();


		//-----------------------------------------------------
		//  �R���\�[���Ɋւ��鏈��
		//-----------------------------------------------------
		std::cout << data << std::flush;

		return streamObject;
	}


	/**----------------------------------------------------
	 * @brief      operator =
	 * @param[in]    rhs    �f�[�^�������鑤
	 * @return       �ύX���������{��
	 *---------------------------------------------------*/
	CityParameter& operator= (const CityParameter& rhs);



	int level;          //!< �X�̃��x��
	int income;         //!< �X�̎���
	int node;           //!< �o���_����݂�����
	int neighbor;       //!< �אڂ����X
	int group;          //!< �����O���[�v
	int power;          //!< �X���ۗL�����͂̑���
	int importance;     //!< �X�̏d�v��
	int cityID;         //!< �X�h�c
	std::string name;   //!< �X�̖��O
};



/**
 * @brief �X�N���X
 *          �퓬�Ȃǂ̒��ړI�Ȏw���͊X���o��
 * @author  Takuya Shishido
 * @date    2009.10.20 23:05:43
 * @version 0.01, Shishido Takuya, 2009.10.20 23:05:43
 */
class City
{
private:

	/**----------------------------------------------------
	 * @brief �o�͗p�� operator <<
	 * @param[in]  os      �X�g���[���I�u�W�F�N�g
	 * @param[in]  team    �o�̓I�u�W�F�N�g
	 *---------------------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const City& city)
	{
		os << city.getCityParameter();

		return os;
	}


public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	City(GameManager& gameManager, const CityParameter& cityParameter_);


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~City();


	/**----------------------------------------------------
	 * @brief      operator =
	 * @param[in]    rhs    �f�[�^�������鑤
	 * @return       �ύX���������{��
	 *---------------------------------------------------*/
	City& operator= (const City& rhs);


	/**----------------------------------------------------
	 * @brief �������֐�
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief initilize a City
	 *---------------------------------------------------*/
	void initCity();


	/**----------------------------------------------------
	 * @brief ���t���[�����s���邱��
	 *---------------------------------------------------*/
	void action();


	/**----------------------------------------------------
	 * @brief �h�����ꂽ���m�Ɛ퓬
	 *---------------------------------------------------*/
	void battleWithTrooper();


	/**----------------------------------------------------
	 * @brief �h��
	 *---------------------------------------------------*/
	void troopDispatch();


	/**----------------------------------------------------
	 * @brief ��������
	 *---------------------------------------------------*/
	void politicking();



	/**----------------------------------------------------
	 * @brief ���`�[���Ɣh���`�[���̏󋵂𐮗�����
	 *---------------------------------------------------*/
	void policeBattleSituation();




	/**----------------------------------------------------
	 * @brief add a Team to trooper
	 *---------------------------------------------------*/
	void addTroopersID(std::list<int> trooperIDs) {
		this->troopers.merge(trooperIDs);
	}


	/**----------------------------------------------------
	 * @brief   getter of troopersID
	 * @return  �h�����ꂽ�`�[���� ID �̃��X�g
	 *---------------------------------------------------*/
	std::list<int> getTroopersID() {
		return this->troopers;
	}


	/**----------------------------------------------------
	 * @brief      setter of havingTeam
	 * @param[in]  havingTeam_    A parameter to set.
	 *---------------------------------------------------*/
	void addHavingTeam(int newTeamID_) {
		this->havingTeam.push_back(newTeamID_);
	}


	/**----------------------------------------------------
	 * @brief   getter of cityParameter
	 * @return  Reference of CityParameter type.
	 *---------------------------------------------------*/
	const CityParameter& getCityParameter() const {
		return this->cityParameter;
	}


	/**----------------------------------------------------
	 * @brief      setter of cityParameter
	 * @param[in]  cityParameter_    A parameter to set.
	 *---------------------------------------------------*/
	void setCityParameter(const CityParameter& cityParameter_) {
		this->cityParameter = cityParameter_;
	}


	/**----------------------------------------------------
	 * @brief      ��� group �Ɋ֘A�̂���p�����[�^�̃Z�b�^
	 * @param[in]  troopersID_    A parameter to set.
	 *---------------------------------------------------*/
	void setParameterForGroup(int troopersID_);



private:




private:

	GameManager&        manager;        //!< GameManager

	CityParameter       cityParameter;  //!< �X�̃p�����[�^
	std::list<int>      troopers;       //!< �X�ɍU�߂Ă����`�[��
	std::list<int>      losers;         //!< ���̊X�ŕ������`�[��
    std::list<int>      havingTeam;     //!< �X�����L����`�[��
	std::vector<int>    neighbor;       //!< �אڂ����X

};    // class City


}   // namespace NewMode

#endif

