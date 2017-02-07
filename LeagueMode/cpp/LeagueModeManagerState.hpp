/**
 * @file
 * @brief LeagueMode の処理本体を担当するメソッド
 *
 * @author Takuya Shishido
 * @date   2010.04.02 13:44:12
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 13:44:12
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef LEAGUEMODE_LEAGUEMODEMANAGERSTATE_HPP_INCLUDED
#define LEAGUEMODE_LEAGUEMODEMANAGERSTATE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Library/LeagueModeException.hpp"
#include "D:/PersonalTool/xyzzy/laboratory/LeagueMode/Structure/TeamDataForCpp.hpp"


//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
namespace LeagueMode {
	class LeagueModeManager;
	class LeagueWork;
}



namespace LeagueMode {

	/**
	 * @enum ゲームマネージャーのステート一覧
	 */
	enum ManagerState {
		MANAGERSTATE_FIRST,
		MANAGERSTATE_INIT = MANAGERSTATE_FIRST,
		MANAGERSTATE_TEAMSELECT,
		MANAGERSTATE_GETDATA,
		MANAGERSTATE_GAME,
		MANAGERSTATE_RESULT,
		MANAGERSTATE_RELEASE,
		MANAGERSTATE_END,
		MANAGERSTATE_LAST = MANAGERSTATE_END,
		MANAGERSTATE_MAX,
	};


	/**
	 * @brief 処理状態を示す値
	 */
	enum RunState {
		RUNSTATE_FINISH,    //!< 処理一通り終了
		RUNSTATE_YET,       //!< まだ終わってないのでもう一度チャンスを
		RUNSTATE_TROUBLE,   //!< 問題あり。異常終了レベル。
		RUNSTATE_INVALID,   //!< 初期化用など
	};



/**
 * @brief  GameManager の状態処理クラス。ベースクラス。
 *          継承されることを前提に作成されたクラス。
 * @author Takuya Shishido
 * @date 2009-10-17
 * @version 0.01
*/
class StateBase
{
public:


	/**----------------------------------------------------
	 * @brief      constructor.
	 * @param[in]   gameManager_    GameManager object.
	 * @param[in]   userWork_       Work object.
	 *---------------------------------------------------*/
	StateBase(LeagueModeManager& leagueModeManager_, LeagueWork& leagueWork_)
		: leagueModeManager(leagueModeManager_)
		, leagueWork(leagueWork_)
	{
	}


	/**----------------------------------------------------
	 * @brief  destroctor
	 *          継承されることを前提に作成されているため、
	 *              virtual になっている
	 *---------------------------------------------------*/
	virtual ~StateBase() {}


	/**----------------------------------------------------
	 * @brief  実行関数
	 *          各内容によって変わる部分なので pure virtual
	 * @return  処理状態
	 *---------------------------------------------------*/
	virtual RunState run() = 0;


	/**----------------------------------------------------
	 * @brief   各クラスの名前のゲッタ。
	 *              これが GameManager クラスにとっての getState() を補佐。
	 * @return  Child class's name.
	 *---------------------------------------------------*/
	virtual ManagerState getState() const = 0;


	/**----------------------------------------------------
	 * @brief 状態が変更されたときに最初に実行される
	 *---------------------------------------------------*/
	virtual void insertProcess() {}


	/**----------------------------------------------------
	 * @brief 状態が変更されたときに最後に実行される
	 *---------------------------------------------------*/
	virtual void releaseProcess() {}


	/**----------------------------------------------------
	 * @brief 情報を画面やファイルに出力
	 *---------------------------------------------------*/
	virtual void printout() {}



protected:

	/**----------------------------------------------------
	 * @brief マネージャークラスのゲッタ
	 * @note    直接のアクセスは許されず、
	 *              継承クラスもこれを経由してアクセスする。
	 * @return  GameManager&    ゲーム管理クラス
	 *---------------------------------------------------*/
	LeagueModeManager& getManager() { return this->leagueModeManager; }


	/**----------------------------------------------------
	 * @brief マネージャークラスのゲッタ
	 * @note    直接のアクセスは許されず、
	 *              継承クラスもこれを経由してアクセスする。
	 * @return  GameManager&    ゲーム管理クラス
	 *---------------------------------------------------*/
	LeagueWork& getWork() { return this->leagueWork; }


private:

	LeagueModeManager&  leagueModeManager;   //!< GameManager 本体
	LeagueWork&         leagueWork;          //!< ユーザー用データ本体
};


/**
 * @brief  初期化のためのクラス
 *
 * @author  Takuya Shishido
 * @date    2010-04-02
 * @version 0.01
 */
class InitState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	InitState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~InitState()  {}


	/**----------------------------------------------------
	 * @brief  初期化実行
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;
};



/**
 * @brief  チーム選択。最初は固定値でテストを行う。
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class TeamSelectState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	TeamSelectState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~TeamSelectState()  {}


	/**----------------------------------------------------
	 * @brief  初期化実行
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;


	/**----------------------------------------------------
	 * @brief 状態が変更されたときに最初に実行される
	 *---------------------------------------------------*/
	void insertProcess();


	/**----------------------------------------------------
	 * @brief 状態が変更されたときに最後に実行される
	 *---------------------------------------------------*/
	virtual void releaseProcess();



private:

	enum Step {
		STEP_FIRSTSTEP,
		STEP_SELECTFIESTTEAM = STEP_FIRSTSTEP,
		STEP_SELECTSECONDTEAM,
		STEP_LASTSTEP = STEP_SELECTSECONDTEAM,
		STEP_MAX,
	};


	/**----------------------------------------------------
	 * @brief 選択された番号を元にチームの名前を入れた
	 *          チームを返す
	 * @param[in]   selectedNumber_     選択された番号
	 * @return      引数を元に作成された Team
	 *---------------------------------------------------*/
	TeamData createTeamDataByName(int selectedNumber_) const throw(BadSelectException);


private:

	unsigned int            step;       //!< 処理状態を示す
	std::vector<TeamList>   teamList;   //!< 対戦するチームの番号
};


/**
 * @brief  ＤＢ からデータを取得する
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class GetDataState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	GetDataState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~GetDataState()  {}


	/**----------------------------------------------------
	 * @brief  メイン
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;


	/**----------------------------------------------------
	 * @brief 状態が変更されたときに最初に実行される
	 *---------------------------------------------------*/
	void insertProcess();


};



/**
 * @brief  試合部分。結果をまとめるまで。
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class GameState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	GameState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~GameState()  {}


	/**----------------------------------------------------
	 * @brief  メイン
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;


	/**----------------------------------------------------
	 * @brief 状態が変更されたときに最初に実行される
	 *---------------------------------------------------*/
	void insertProcess();


private:


	/**----------------------------------------------------
	 * @brief   対戦を行った際に取得できるゴール数を計算
	 * @param[in]   offence_    チームの総攻撃力
	 * @return  ゴール数
	 *---------------------------------------------------*/
	int getGoal(int offence_);
};



/**
 * @brief  試合結果を表示する
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class ResultState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	ResultState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~ResultState()  {}


	/**----------------------------------------------------
	 * @brief  メイン
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;
};



/**
 * @brief  全てのまとめを行う。開放や必要な処理など。
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class ReleaseState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	ReleaseState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~ReleaseState()  {}


	/**----------------------------------------------------
	 * @brief  メイン
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;
};


/**
 * @brief  終了したことを示すステート
 *
 * @author  Takuya Shishido
 * @date    2010-04-05
 * @version 0.01
 */
class EndState : public StateBase
{
public:

	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	EndState(LeagueModeManager& leagumeModeManager_, LeagueWork& leagueWork_);

	
	/**----------------------------------------------------
	 * @brief      constructor
	 * @param[in]  manager_    GameManager's Instance
	 *---------------------------------------------------*/
	~EndState()  {}


	/**----------------------------------------------------
	 * @brief  メイン
	 * @return  処理状態
	 *---------------------------------------------------*/
	RunState run();


	/**----------------------------------------------------
	 * @brief   getter of StateName
	 *              ベースクラスの関数のオーバーライド。
	 * @return  状態の名前。
	 *---------------------------------------------------*/
	ManagerState getState() const;
};





}    // namespace LeagueMode

#endif  // LEAGUEMODE_LEAGUEMODEMANAGERSTATE_HPP_INCLUDED

