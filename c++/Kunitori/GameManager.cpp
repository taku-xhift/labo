/**
 * @file
 * @brief ゲームの管理をするためのモジュール
 *
 * @author Takuya Shishido
 * @date 2009.10.20 23:11:19
 *
 * @version 0.01, Shishido Takuya, 2009.10.20 23:11:19
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <algorithm>
#include "StreamObject.hpp"
#include "GameManager.hpp"
#include "Define.hpp"


using namespace so;


namespace NewMode {


//-----------------------------------------------------
//  functor
//-----------------------------------------------------
/**
 * @brief 初期化用のファンクタ
 * @author  Takuya Shishido
 * @date    2009/11/03 22:44
 * @version 0.01, Shishido Takuya, 2009/11/03 22:44
 */
template<typename Type>
class Initializer
{
public:

	/**----------------------------------------------------
	 * @brief operator()
	 * @note    初期化を専門に扱うファンクタ。
	 *          使い方はどこか検索してみたください。
	 * @param[in]   data    初期化したいデータ
	 *---------------------------------------------------*/
	void operator() (Type& data) {
		data.init();
	}
};

/**
 * @brief データの delete を専門に請け負う
 * @author  Takuya Shishido
 * @date    2009/11/04 0:08
 * @version 0.01, Shishido Takuya, 2009/11/04 0:08
 */
template<typename Type>
class Deleter
{
public:

	/**----------------------------------------------------
	 * @brief operator()
	 * @note    delete を専門に扱うファンクタ。
	 * @param[in]   data    消去したいデータ
	 *---------------------------------------------------*/
	void operator() (const Type& data) {
		delete data;
	}
};


/**----------------------------------------------------
 * @brief 引数にあわせて State* を作り出す
 * @param[in]   manager_     ゲームマネージャー
 * @param[in]   stateData_   欲しい State の指定
 * @return  コンストラクタによって作られるデータのアドレス
 *---------------------------------------------------*/
State* makeState(GameManager& manager_, StateData stateData_)
{
	// 渡されたデータの有効性をチェック
	if (stateData_ > STATEDATA_NUM) {
		out << __FILE__ << __LINE__ << "中身の状態を受け取りましたので、消去します" << endl;
		return NULL;
	}


	// 上記関門をクリアしたもののみチェックしてデータ作成
	switch (stateData_) {
	case STATEDATA_INVALID:
		return NULL;
	case STATEDATA_INIT:
		return new InitState(manager_, stateData_);
	case STATEDATA_ORDINARY:
		return new OrdinaryState(manager_, stateData_);
	case STATEDATA_SHOWALLIANCABLETEAM:
		return new ShowAlliancableTeam(manager_, stateData_);
	case STATEDATA_SIGNWITHTEAM:
		return new SignWithTeam(manager_, stateData_);
	case STATEDATA_ENDGAME:
		return new EndGame(manager_, stateData_);
	default:
		out << "無効なデータが渡されました" << endl;
		return NULL;
	}
}


/**----------------------------------------------------
 * @brief 引数にもらったコンテナに
 *          StateData の数分だけ State* を作って入れる。
 *          State の中身は StateData に見あった中身
 * @param[in]   manager     GameManager データ。
 * @param[in]   container   push_back の使えるもの。
  *---------------------------------------------------*/
template<typename Type>
void makeStates(GameManager& manager, Type& container)
{
	State* state;

	// 自動的に State の数だけ State を作って保存
	for (unsigned int i = 0; i < STATEDATA_NUM; ++i) {
		state = makeState(manager, static_cast<StateData>(i));
		container.push_back(state);
		//delete state;
	}
}


/**----------------------------------------------------
 * @brief constructor
 *---------------------------------------------------*/
GameManager::GameManager()
	: preStateID(STATEDATA_INVALID)
	, nowStateID(STATEDATA_INVALID)
{
	// State を作成
	makeStates(*this, this->stateContainer);

	// 初期化ステート
	//this->init();

	// ステートの決定
	this->nowState = this->stateContainer.at(STATEDATA_INIT);
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
GameManager::~GameManager()
{
	// 状態管理クラスのコンテナを消去
	this->stateContainer.clear();
}


/**----------------------------------------------------
 * @brief destructor
 *---------------------------------------------------*/
void GameManager::init(int playerNum)
{
	// その他のパラメータ
	this->preStateID = STATEDATA_INIT;
	this->nowStateID = STATEDATA_ORDINARY;

	this->nowState = stateContainer.at(STATEDATA_ORDINARY);
}


/**----------------------------------------------------
 * @brief main roop
 *---------------------------------------------------*/
GameManager::GameState GameManager::run()
{
	// 指定された状態の実行関数を呼び出す
	this->nowState->action();


	// 前回のループでのステートの保存
	// ステートの変化が起きていれば過去のものを保存
	if (this->preRoopStateID != this->preStateID) {
		this->preRoopStateID = this->preStateID;
	// ステートの変化が起きていなければ現在のステートを保存
	} else {
		this->preRoopStateID = this->nowStateID;
	}

	// 終了条件を満たすか？
	if (this->nowState->getStateName() == STATEDATA_ENDGAME) {
		return GAMESTATE_EXIT;
	} else {
		return GAMESTATE_RUN;
	}
}


}   // namespace NewMode

