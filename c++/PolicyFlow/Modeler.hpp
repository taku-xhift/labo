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

#ifndef MODELER_HPP_INCLUDED
#define MODELER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include <string>
#include <bitset>
#include <limits>
#include "DB.hpp"
#include "Define.hpp"


// <windows.h> で定義されているらしい
#ifdef max
#undef max
#endif



//! \brief インターフェースクラス
class ModelerInterface {
private:
	friend class EqualityWithQuestion;
public:

	//! \brief constructor
	//! \param[in]  parentID_   親の ID。メッセージ用
	ModelerInterface(unsigned int parentID_ = std::numeric_limits<unsigned int>::max());

	//! \brief destructor
	//! \note   継承用
	virtual ~ModelerInterface() {}

	//! \brief 自分が処理すべき内容を記述
	virtual void process() = 0;

	//! \brief メッセージを受け取るためのインターフェース
	//! \param[in]  message_    内容。解析は必要があれば継承先で実装。
	void setMessage(std::string message_)   { this->message = message_; }

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

	std::bitset<Question_Max>   flagSet;        //!< 状態管理用
	std::string                 message;        //!< control 側からメッセージがあれば入ってる
};

template<typename ModelPolicy>
class Modeler
	: public ModelPolicy
{
public:
	//! \brief constructor
	//! \param[in]  parentID_   親 ID。
	Modeler(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelPolicy(parentID_)
	{
	}

	//! \brief 自分に実装されている処理を行う
	//! \note   継承元の実装を呼び出すだけ
	void process() {
		this->ModelPolicy::process();
	}
};

//===============================================================================
// ユーザの実装部分
//    1. 実装必須 (ControlerInterface のインターフェース)
//          void process()
//          bool getFlagState(Question question_)
//
//    2. 実装条件
//          デストラクタのアクセスレベルを protected にすること
//
//      上記の条件を満たせばその他は自由に作成可能
//          基本的に Controler の時と同じ
//
//    3. 実装内容
//          データを処理して描画に必要なデータを準備する。
//          準備が出来たら
//              ViewPolicy::method(this->message);
//          のような形でデータ渡して View を評価する。
//          当たり前だがここで View を評価しなければ描画されない。
//          評価するしないの判断くらいは許可されている。



//! brief チャット処理
template<typename ViewPolicy>
class Chat
	: public ModelerInterface {
public:

	//! \brief 引数つきコンストラクタ
	//! \note   引数をつけると Controler 側でインスタンス化の方法が難しくなる。
	//          不可能ではないが慣れが必要なので、setData のようなインターフェースを
	//          準備してセットしてもらうという方法もいいのかもしれない。
	Chat(std::string message_, unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelerInterface(parentID_)
		, message(message_)
	{
	}

	//! \brief 引数なしコンストラクタ
	//! \note   上記の理由で引数無しも準備
	Chat(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelerInterface(parentID_)
	{
	}

	void process() {
		std::cout << typeid(Chat).name() << " : ";
		ViewPolicy::draw(this->message);
		this->setFlagSet(Question_MayIKillYou, true);
	}

	void sendMessage(std::string message_) { this->message = message_; }

protected:

	~Chat() {}

private:

	std::string     message;    //!< チャット用メッセージ
};


//! \brief DB アクセス
template<typename ViewPolicy>
class AskDataBase
	: public ModelerInterface {
public:

	AskDataBase(unsigned int parentID_ = std::numeric_limits<unsigned int>::max())
		: ModelerInterface(parentID_)
	{
	}

	void process() {
		int data = ++userID;
		std::cout << typeid(AskDataBase).name() << " : ";
		ViewPolicy::draw(data);
		this->setFlagSet(Question_MayIKillYou, true);
	}

protected:

	~AskDataBase() {}
};

#endif  // MODELER_HPP_INCLUDED
