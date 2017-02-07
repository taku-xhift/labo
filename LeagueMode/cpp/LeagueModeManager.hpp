/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueModeManagerState.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/cpp/LeagueWork.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/GameResultForCpp.hpp"


namespace LeagueMode {


	/**
	 * @brief リーグモードができる処理一覧。
	 * @note    LeagueModeManager::executeModule で使用する
	 */
	enum LeaugeModeManagerBehavior {
		LEAGUEMODEMANAGERBEHAVIOR_TEAMSELECT,   //!< チームセレクト
		LEAGUEMODEMANAGERBEHAVIOR_AUTOGAME,     //!< 操作なしで試合結果を出す
		LEAGUEMODEMANAGERBEHAVIOR_MAX,
	};



/**
 * @brief リーグを管理するためのマネージャー
 *          
 * @author  Takuya Shishido
 * @date    2010.04.02 10:44:24
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 */
class LeagueModeManager
{
private:

	static LeagueModeManager* uniqueInstance;   //!< シングルトンなのでユニークなオブジェクト定義

	friend class InitState;
	friend class TeamSelectState;
	friend class GetDataState;
	friend class GameState;
	friend class ResultState;
	friend class ReleaseState;


public:

	/**----------------------------------------------------
	 * @brief インスタンス取得
	 *          必要な時にメモリを確保させるので、Create を作らなかった
	 * @return  GameManager のユニークなオブジェクト
	 *----------------------------------------------------*/
	static LeagueModeManager* getInstance() {
		if (uniqueInstance == NULL) {
			uniqueInstance = new LeagueModeManager();
		}
		return uniqueInstance;
	}


	/**----------------------------------------------------
	 * @brief インスタンスの破壊
	 *          インスタンスの破壊をするためのクラス。
	 *          確保していなかった場合でも安全。
	 *----------------------------------------------------*/
	static void destroyInstance() {
		if (uniqueInstance != NULL) {
			delete uniqueInstance;
			uniqueInstance = NULL;
		}
	}


	/**----------------------------------------------------
	 * @brief  destructor
	 *----------------------------------------------------*/
	~LeagueModeManager();


	/**----------------------------------------------------
	 * @brief   実行関数
	 *              State Pattern で書かれているため、
	 *              nowState に依存する処理が行われる。
	 * @return  現在の状態の名前
	 *----------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief 引数で割り当てられた仕事のみを行う
	 * @param[in]   state_          処理内容の指定
	 *----------------------------------------------------*/
	static void executeModule(LeaugeModeManagerBehavior behavior_);


	/**----------------------------------------------------
	 * @brief  データ出力
	 * @note    ボタンを押したときのみ
	 *----------------------------------------------------*/
	void opParameter();


	/**----------------------------------------------------
	 * @breif 状態をセットする際に受け付けるためのゲッタ
	 *----------------------------------------------------*/
	ManagerState getNowState() const { return this->nowState->getState(); }


	/**----------------------------------------------------
	 * @breif 状態を文字列で取得する
	 *----------------------------------------------------*/
	const char* getNowStateByString() const { return this->getStateString(this->nowState->getState()); }


	/**----------------------------------------------------
	 * @brief   現在の状態の名前取得
	 * @return  現在の状態の名前
	 *----------------------------------------------------*/
	ManagerState getPreState() const {
		return this->preState;
	}


	/**----------------------------------------------------
	 * @brief       状態のセッタ
	 * @param[in]   state_          次の状態クラス
	 * @param[in]   nextState_      state_ の次の指定。ただし必ず反映されるとは限らない。
	 *----------------------------------------------------*/
	void setState(ManagerState state_, ManagerState nextState_ = MANAGERSTATE_MAX);


private:

	/**----------------------------------------------------
	 * @brief constructor
	 *           Singleton Pattern によっているため、private なコンストラクタ
	 *----------------------------------------------------*/
	LeagueModeManager();



	/**----------------------------------------------------
	 * @brief copy constructor
	 *          Singleton Pattern で記述されているため、
	 *          コピーコンストラクタは private で未定義にする
	 *----------------------------------------------------*/
	LeagueModeManager(const LeagueModeManager& leagueModeManager_);



	/**----------------------------------------------------
	 * @brief operator =
	 *          Singleton Pattern で記述されているため、
	 *          operator = も private で未定義にする
	 *----------------------------------------------------*/
	LeagueModeManager& operator =(const LeagueModeManager& leagueModeManager_);



	/**----------------------------------------------------
	 * @brief 現在の状態を文字列で取得する
	 *----------------------------------------------------*/
	const char* getStateString(ManagerState state_) const;



	/**----------------------------------------------------
	 * @brief state_ で指定されたデータを作成する
	 * @param[in]   state_      作成する処理
	 *----------------------------------------------------*/
	StateBase* createState(ManagerState state_);


public:
	/**----------------------------------------------------
	 * @brief チームセレクトに関する一連の処理を行う
	 *----------------------------------------------------*/
	void behaviorTeamSelect();



	/**----------------------------------------------------
	 * @brief 試合結果計算に関する一連の処理を行う
	 * @param[in]   homeTeam_   ホーム側チームの名前
	 * @param[in]   awayTeam_   アウェイ側チームの名前
	 *----------------------------------------------------*/
	static void behaviorGame(const char* homeTeam_, const char* awayTeam_);


private:
	/**----------------------------------------------------
	 *  メンバ
	 *----------------------------------------------------*/
	StateBase*                  nowState;           //!< 現在の状態オブジェクト

	//std::vector<StateBase*>     stateContainer;     //!< 状態管理コンテナ
	LeagueWork                  leagueWork;         //!< ゲームのメインのデータを管理するクラス
	ManagerState                preState;           //!< 直前のステートの名前
	ManagerState                nextState;          //!< 次のステートの名前

	std::string                 messageForNext;     //!< 次のステートへのメッセージを保存

	std::vector<TeamData>       teamData;           //!< 対戦する２チームのチーム情報
	std::vector<GameResult>     gameResult;         //!< 試合結果を保存する

};    // class LeagueModeManager
}    // namespace LeagueMode

#endif

