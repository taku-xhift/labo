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

#ifndef VIEWER_HPP_INCLUDED
#define VIEWER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <algorithm>
#include <bitset>
#include "Utility.hpp"

// <windows.h> で定義されているらしい
#ifdef max
#undef max
#endif


//! \brief インターフェースクラス
class ViewerInterface {
private:
	friend class EqualityWithQuestion;
public:

	//! \brief constructor
	//! \param[in]  parentID_   親の ID。メッセージ用
	ViewerInterface(int parentID_ = std::numeric_limits<unsigned int>::max());

	//! \brief destructor
	//! \note   継承用
	virtual ~ViewerInterface() {}

	//! \brief 描画処理
	virtual void draw() = 0;

	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	unsigned int getID() const          { return this->uniqueID; }
	unsigned int getParentID() const    { return this->parentID; }

protected:

	//-----------------------------------------------------
	//  accessor
	//-----------------------------------------------------
	bool getFlagState(Question question_) const             { return this->flagSet[question_]; }
	void setFlagSet(Question question_, bool parameter_)    { this->flagSet[question_] = parameter_; }

private:

	static unsigned int serialNumber;   //!< unique な ID 生成用
	unsigned int uniqueID;              //!< 自身の ID
	unsigned int parentID;              //!< 親がいればその ID。いないなら std::numeric_limits<unsigned int>::max()

	std::bitset<Question_Max>   flagSet;            //!< getFl状態管理用
};


//===============================================================================
// ユーザの実装部分
//    1. 実装必須 (ControlerInterface のインターフェース)
//          void method()
//          bool getFlagState(Question question_)
//    2. 実装条件
//          2.1 デストラクタのアクセスレベルを protected にすること
//          2.2 method で受け取るデータは const Type& の形で受け取り、データを変更しないこと
//          2.3 method は static 関数にすること。state の管理は Model の仕事。state で処理が変わるならクラスを作り直す。
//
//      上記の条件を満たせばその他は自由に作成可能
//          基本的に Controler の時と同じ
//
//    3. 実装内容
//          描画メソッド。



//! \brief cout を使用しての表示
class Cout
	: public ViewerInterface {
public:
	template<typename Type>
	static void draw(const Type& data_) {
		std::cout << typeid(Cout).name() << " : " << data_ << std::endl;
	}

	bool getFlagState(Question question_) { return this->flagSet[question_]; }

protected:
	~Cout() {}
private:
	std::bitset<Question_Max>    flagSet;
};

//! \brief printf を使用しての表示
class Printf
	: public ViewerInterface {
public:

	static void draw(const char* data_) { printf("%s : %s", typeid(Printf).name(), data_); }

	bool getFlagState(Question question_) { return this->flagSet[question_]; }

protected:
	~Printf() {}
private:
	std::bitset<Question_Max>    flagSet;
};

#endif  // VIEWER_HPP_INCLUDED
