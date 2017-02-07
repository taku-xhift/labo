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
#include "Object.hpp"


namespace NewMode {

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
		os << "group : " << cityParameter.group << std::endl;
		os << "power : " << cityParameter.power << std::endl;
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
	int group;          //!< 所属グループ
	int power;          //!< 街が保有する戦力の総数
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
class City : public Object
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
    std::list<int>      havingTeam;     //!< 街が所有するチーム

};    // class City


}   // namespace NewMode

#endif

