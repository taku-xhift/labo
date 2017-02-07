/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.10.07 15:20:08
 *
 * @version 0.01, Shishido Takuya, 2010.10.07 15:20:08
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef CONTROLER_HPP_INCLUDED
#define CONTROLER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <algorithm>
#include <list>
#include <bitset>

#include "Define.hpp"


// <windows.h> で定義されているらしい
#ifdef max
#undef max
#endif


//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
class ModelInterface;


//! \brief インターフェースクラス
class ControlerInterface {
private:
	friend class EqualityWithQuestion;
public:

	//! \brief constructor
	//! \param[in]  parentID_   親の ID。メッセージ用
	ControlerInterface(unsigned int parentID_ = std::numeric_limits<unsigned int>::max());

	//! \brief destructor
	//! \note   継承用
	virtual ~ControlerInterface();

	//! \brief 入力解析用
	//! \param      input_      View で取得された入力
	//! \return     子の処理を作る必要があればそれを返す
	virtual ControlerInterfaceContainer update(const Input& input_) = 0;

	//! \brief 自分が所有する Model で取得するデータ等があればその処理を走らせる
	//! \note   オーバーロード禁止
	void processing();

	//! \brief Model にメッセージがあればこれで。解析は Model の仕事
	//! \param[in]  ID_         Model の ID。
	//                          管理する時点で必要になりそうなものは各自継承先で
	//                          ID をメンバとして保存しておくこと。
	//! \param[in]  message_    伝えるメッセージ。解析は Model の仕事。
	//! \retval     true        メッセージを正常に伝えた
	//! \retval     false       ID_ が見つからなかった
	bool sendMessageToModel(unsigned int ID_, std::string message_);

	//! \brief モデルオブジェクトを登録する際の代入先
	//! \param[in]   model_  登録するモデル
	void addModelContainer(ModelerInterface* model_)                    { this->modelContainer.push_back(model_); }
	void addModelContainer(ModelerInterfaceContainer modelContainer_)   { this->modelContainer.merge(modelContainer_); }


	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	unsigned int getID() const              { return this->uniqueID; }
	unsigned int getParentID() const        { return this->parentID; }

protected:

	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	bool getFlagState(Question question_) const             { return this->flagSet[question_]; }
	void setFlagSet(Question question_, bool parameter_)    { this->flagSet[question_] = parameter_; }

private:

	static unsigned int serialNumber;   //!< unique な ID 生成用
	unsigned int        uniqueID;       //!< 自身の ID
	unsigned int        parentID;       //!< 親がいればその ID。いないなら std::numeric_limits<unsigned int>::max()

	std::bitset<Question_Max>   flagSet;            //!< 状態管理用
	ModelerInterfaceContainer   modelContainer;     //!< 描画用データと描画方法のセットコンテナ
};


//! \brief ポリシーパターンによるホスト
//! \note   template パラメータによって指定したクラスに応じて振る舞いを変える
template<typename ControlPolicy>
class Controler
	: public ControlPolicy
{
public:
	//! \brief constructor
	//! \param[in]  parentID_   親 ID
	Controler(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ControlPolicy(parentID_)
	{
	}

	//! \brief インターフェースの実装
	//! \note   ユーザからは Model オブジェクトのポインタのリストが返ってくるので
	//          それを std::shared_ptr で管理しなおす
	ControlerInterfaceContainer update(const Input& input_) {
		ControlerInterfaceContainer newControlList = this->ControlPolicy::update(input_);
		this->processing();
		return newControlList;
	}

	//! \brief 状態管理のインターフェース
	//! \note       ユーザが実装した中身をそのまま返す
	//! \param[in]  question_   今後の振る舞いに関しての質問
	bool getFlagState(Question question_) {
		return this->ControlPolicy::getFlagState(question_);
	}

};


//! \brief Controler クラスを管理する。
//! \note   メッセージ処理もここ。
//          しかしオブジェクトに問いかけるだけで主体性はこのクラス
//          オブジェクトの親子関係も子は親の ID を知っているだけ。
//          親が子を評価したりせずまったく同じレベルで行われる
class ControlManager {
public:
	//! \brief 所持しているオブジェクトを評価する
	//! \note       メッセージ処理もここ
	//! \param[in]  input_  入力
	void execute(const Input& input_);

	//! \brief 新しい画面管理などを受付
	//! \param[in]  control_    新しい画面管理クラス
	void add(ControlerInterface* control_)          { this->controlList.push_back(control_); }

	//! \brief 自身が所有している画面管理クラスの数を取得
	//! \note   0 なら処理すべきものがもう無いので消しても大丈夫かもしれない
	unsigned int getControlInterfaceSize() const    { return this->controlList.size(); }

private:
	ControlerInterfaceContainer controlList;     //!< 画面処理クラス群
};

//====================  Policy パターンによる実装  ==================================
//
// ユーザの実装部分
//    1. 実装必須 (ControlerInterface のインターフェース)
//          SpModelerInterfaceContainer update(const Input&)
//          bool getFlagState(Question)
//
//    2. 実装条件
//          デストラクタのアクセスレベルを protected にすること
//
//      上記の条件を満たせばその他は自由に作成可能
//          getFlagState を満たすためのフラグも好きな形で処理してよい。
//              (bitset を使ったり bool で管理したりなど)
//
//    3. 実装内容
//          内容は Model 評価方法とその View 方法の指定。
//          指定方法は
//              Modeler<Chat<Cout> >* temp = new Modeler<Chat<Cout> > ();
//          のような形。Modeler<Model<View>>* の形でデータを作り
//          std::list のコンテナに格納して返すと後で自動で実行される。



//! \brief テスト用 : リーグフロー管理クラス
class LeagueFlow
	: public ControlerInterface
{
public:

	LeagueFlow(unsigned int parentID_ /*= std::numeric_limits<unsigned int>::max()*/);

	//!< \brief method 実装
	ControlerInterfaceContainer update(const Input& input_);

protected:
	~LeagueFlow() {}

private:
	int step;       //!< 自身のステップ管理
};



#endif  // CONTROLER_HPP_INCLUDED
