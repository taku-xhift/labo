/**
 * @file
 * @brief 街モジュール
 *
 * @author Takuya Shishido
 * @date   2009.10.20 23:05:43
 *
 * @version 0.01, Shishido Takuya, 2009.10.20 23:05:43
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef CITY_HPP_INCLUDED
#define CITY_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <list>
#include "City.hpp"
#include "StreamObject.hpp"



//-----------------------------------------------------
//  decralation
//-----------------------------------------------------
class GameManager;



/**
 * @brief 街パラメータクラス
 *          コンストラクタで街のパラメータをしていする
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
	 * @brief 初期化関数
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os               ストリームオブジェクト
	 * @param[in]  cityParameter    出力オブジェクト
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
	 * @brief      実際に出力している部分
	 * @note        実装自体は std::cout と std::ofstream を使っている。
	 * @param[in]    streamObject   出力に使っているクラスデータ
	 * @param[in]    data           出力する予定のデータ
	 *---------------------------------------------------*/
	friend so::StreamObject& operator<<(so::StreamObject& streamObject, const CityParameter& data)
	{
		//-----------------------------------------------------
		//  ファイルに関する処理
		//-----------------------------------------------------
		std::ofstream fout( streamObject.getFilename().c_str(), std::ios::app ); // test.txt を追記モードで開く

		// 開けなかった場合は終了
		if( fout.fail() )
		{
			std::cout << "file is nothing." << std::endl;
			return streamObject;
		}

		// 出力
		fout << data;

		// ファイルを閉じる
		fout.close();


		//-----------------------------------------------------
		//  コンソールに関する処理
		//-----------------------------------------------------
		std::cout << data << std::flush;

		return streamObject;
	}


	/**----------------------------------------------------
	 * @brief      operator =
	 * @param[in]    rhs    データを代入する側
	 * @return       変更を加えた本体
	 *---------------------------------------------------*/
	CityParameter& operator= (const CityParameter& rhs);



	int level;          //!< 街のレベル
	int income;         //!< 街の収入
	int node;           //!< 出発点からみた距離
	int neighbor;       //!< 隣接した街
	int group;          //!< 所属グループ
	int power;          //!< 街が保有する戦力の総数
	int importance;     //!< 街の重要性
	int cityID;         //!< 街ＩＤ
	std::string name;   //!< 街の名前
};



/**
 * @brief 街クラス
 *          戦闘などの直接的な指示は街が出す
 * @author  Takuya Shishido
 * @date    2009.10.20 23:05:43
 * @version 0.01, Shishido Takuya, 2009.10.20 23:05:43
 */
class City
{
private:

	/**----------------------------------------------------
	 * @brief 出力用の operator <<
	 * @param[in]  os      ストリームオブジェクト
	 * @param[in]  team    出力オブジェクト
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
	 * @param[in]    rhs    データを代入する側
	 * @return       変更を加えた本体
	 *---------------------------------------------------*/
	City& operator= (const City& rhs);


	/**----------------------------------------------------
	 * @brief 初期化関数
	 *---------------------------------------------------*/
	void init();


	/**----------------------------------------------------
	 * @brief initilize a City
	 *---------------------------------------------------*/
	void initCity();


	/**----------------------------------------------------
	 * @brief 毎フレーム実行すること
	 *---------------------------------------------------*/
	void action();


	/**----------------------------------------------------
	 * @brief 派兵された兵士と戦闘
	 *---------------------------------------------------*/
	void battleWithTrooper();


	/**----------------------------------------------------
	 * @brief 派兵
	 *---------------------------------------------------*/
	void troopDispatch();


	/**----------------------------------------------------
	 * @brief 政治活動
	 *---------------------------------------------------*/
	void politicking();



	/**----------------------------------------------------
	 * @brief 自チームと派兵チームの状況を整理する
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
	 * @return  派兵されたチームの ID のリスト
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
	 * @brief      主に group に関連のあるパラメータのセッタ
	 * @param[in]  troopersID_    A parameter to set.
	 *---------------------------------------------------*/
	void setParameterForGroup(int troopersID_);



private:




private:

	GameManager&        manager;        //!< GameManager

	CityParameter       cityParameter;  //!< 街のパラメータ
	std::list<int>      troopers;       //!< 街に攻めてきたチーム
	std::list<int>      losers;         //!< この街で負けたチーム
    std::list<int>      havingTeam;     //!< 街が所有するチーム
	std::vector<int>    neighbor;       //!< 隣接した街

};    // class City

#endif

