/**
 * @file
 * @brief フレームワークで使用するための例外クラス群
 *
 * @author Takuya Shishido
 * @date   2010.11.29 11:19:15
 *
 * @version 0.01, Shishido Takuya, 2010.11.29 11:19:15
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef WEO_FLOW_WEOFLOWEXCEPTION_HPP_INCLUDED
#define WEO_FLOW_WEOFLOWEXCEPTION_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <stdexcept>
#include <string>
//#include "weCommonType.h"


//-----------------------------------------------------
//  declaration
//-----------------------------------------------------
namespace pm_mode {
	namespace task {
		class FlowMessage;
	}
}



namespace pm_mode {
namespace task {


//! \brief フレームワークで使う例外クラスの規定クラス
class FlowException
	: public std::exception
{
public:


	/********************************************************************
	 * @brief constructor
	 * @param[in]   log     今回発生した問題に関するログ
	 ********************************************************************/
	explicit FlowException(const std::string& log) throw() {log;}


	/********************************************************************
	 * @brief ログ情報を追加する
	 * @note        メモリが足りなかった場合には何もしない
	 * @param[in]   log     今回発生した問題に関するログ
	 * @return      連続して << で追加するために自分自身を返却
	 ********************************************************************/
	virtual FlowException& operator<<(const std::string& log) throw() { log; return *this; }


	/********************************************************************
	 * @brief ログを出力する
	 ********************************************************************/
	virtual const char* what() const throw() { return ""; }


	/********************************************************************
	 * @brief 持っている情報をすべて string にまとめて返す
	 * @return     << で足されたものを含む全ての情報
	 * @except      bad_alloc   メモリが足りなくなった場合
	 ********************************************************************/
	std::string getAllInfo() const throw(std::bad_alloc) { return std::string(); }


protected:

	/********************************************************************
	 * @brief destructor
	 * @note    virtual でなくていい
	 ********************************************************************/
	~FlowException() throw() {}


	/********************************************************************
	 * @brief クラスごとの詳細データを返却
	 * @note    getAllInfo() を呼び出した際に呼び出される。
	 *              template method パターン
	 ********************************************************************/
	virtual std::string detailInfo() const throw() { return std::string(""); }

private:
	std::vector<std::string> messageList_;
};




/********************************************************************
 * @brief メモリ取得に関するエラー
********************************************************************/
class MemoryAllocateException : public FlowException {
public:
	explicit MemoryAllocateException(const std::string& message = "") throw()
		: FlowException(message)
	{
		
	}

	virtual const char* what() const throw()        { return "Type[FlowException]\n"; }
};



//! \brief メッセージ授受に関するエラー
class MessageErrorException : public FlowException
{
public:

	//! \brief constructor
	//! \param[in]  receiverID  エラーが発生した、受信側の ID
	//! \param[in]  mail        メール本体
	//! \param[in]  message     エラーメッセージ
	MessageErrorException(const task::FlowMessage& mail, const std::string& message = "") throw();


	//! \brief Output error message.
	virtual const char* what() const throw()        { return "Type[MessageErrorException]\n"; }

};


//! \brief 画面クラスを生成するのに失敗した場合に使用される例外
class CreationSerialNumberException : public FlowException
{
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit CreationSerialNumberException(const std::string& message = "") throw();

	virtual const char* what() const throw()        { return "Type[CreationSerialNumberException]\n"; }
};



//! \brief 何かフローの中で論理的な問題が発生した場合
class FlowLogicException : public FlowException
{
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit FlowLogicException(const std::string& message = "") throw()
		: FlowException(message)
	{}

	virtual const char* what() const throw()        { return "Type[FlowLogicException]\n"; }
};



//! \brief 探索の結果見つからなかった場合
class FlowUnFoundException : public FlowException
{
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit FlowUnFoundException(const std::string& message = "") throw();

	//! \brief overload
	virtual const char* what() const throw()        { return "Type[FlowUnFoundException]\n"; }
};

//! \brief xmlノードの探索ので見つからなかった場合
class NodeUnFoundException : public FlowException
{
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit NodeUnFoundException(const std::string& message = "") throw();

	//! \brief overload
	virtual const char* what() const throw()        { return "Type[NodeUnFoundException]\n"; }
};


/********************************************************************
 * @brief データの準備が不完全な状態の場合
********************************************************************/
class UnReadyLoadData : public FlowException {
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit UnReadyLoadData(const std::string& message = "") throw();

	//! \brief overload
	virtual const char* what() const throw()        { return "Type[UnReadyLoadData]\n"; }
};


/********************************************************************
 * @brief 引数に問題があるときのためのエラー
 * @note    引数を渡したいが、template だと catch 不可能なので
********************************************************************/
class InvalidArgumentException : public FlowException {
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit InvalidArgumentException(const std::string& message = "") throw();

	//! \brief overload
	virtual const char* what() const throw()        { return "Type[InvalidArgumentException]\n"; }
};



/********************************************************************
 * @brief 0 除算をした際に返す例外
********************************************************************/
class ZeroDevisionException : public FlowException {
public:

	//! \brief constructor
	//! \param[in]  message     エラーメッセージ
	explicit ZeroDevisionException(const std::string& message = "") throw();

	//! \brief overload
	virtual const char* what() const throw()        { return "Type[ZeroDevisionException]\n"; }
};




}    // namespace task
}    // namespace pm_mode


#endif

