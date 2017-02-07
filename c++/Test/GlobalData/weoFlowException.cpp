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


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iterator>
#include "weoFlowException.h"
//#include "weoFlowMessage.h"
#include "weoLexicalCast.h"


namespace pm_mode {
namespace task {


/********************************************************************
 * @brief constructor
 * @param[in]   log     今回発生した問題に関するログ
********************************************************************/
FlowException::FlowException(const std::string& log) throw()
{
	try {
		this->messageList_.push_back(log);
	} catch (const std::bad_alloc&) {
		// 出来ることがない
	}
}


/********************************************************************
 * @brief ログ情報を追加する
 * @note        メモリが足りなかった場合には何もしない
 * @param[in]   log     今回発生した問題に関するログ
 * @return      連続して << で追加するために自分自身を返却
********************************************************************/
FlowException& FlowException::operator<<(const std::string& log) throw() {
	try {
		this->messageList_.push_back(log + "\n");
	} catch (const std::bad_alloc&) {
		// 出来ることがない
	}
	return *this;
}



/********************************************************************
 * @brief ログを出力する
********************************************************************/
const char* FlowException::what() const throw() {
	return "Type[FlowException]\n";
}



/********************************************************************
 * @brief 持っている情報をすべて string にまとめて返す
 * @return      << で足されたものを含む全ての情報
 * @except      bad_alloc   メモリが足りなくなった場合
********************************************************************/
std::string FlowException::getAllInfo() const throw(std::bad_alloc) {
	std::string returnValue = this->what();
	returnValue += this->detailInfo();

	std::vector<std::string>::const_iterator ite = this->messageList_.begin();
	returnValue += ite->c_str();
	advance(ite, 1);
	for (; ite != this->messageList_.end(); ++ite) {
		returnValue.append("↑\n");
		returnValue.append(*ite);
	}
	return returnValue;
}



//! \brief destructor
//! \note   virtual でなくていい
FlowException::~FlowException() throw() {}




//! \brief constructor
CreationSerialNumberException::CreationSerialNumberException(const std::string& message) throw()
	: FlowException(message)
{

}


//! \brief 何かフローの中で論理的な問題が発生した場合
FlowLogicException::FlowLogicException(const std::string& message /* = ""*/) throw()
	: FlowException(message)
{
	
}


//! \brief constructor
FlowUnFoundException::FlowUnFoundException(const std::string& message) throw()
	: FlowException(message)
{

}


//! \brief constructor
NodeUnFoundException::NodeUnFoundException(const std::string& message) throw()
	: FlowException(message)
{

}


//! \brief constructor
//! \param[in]  message     エラーメッセージ
UnReadyLoadData::UnReadyLoadData(const std::string& message /* = ""*/) throw()
	: FlowException(message)
{
}


//! \brief constructor
//! \param[in]  message     エラーメッセージ
InvalidArgumentException::InvalidArgumentException(const std::string& message /* = ""*/) throw()
	: FlowException(message)
{
}


}    // namespace flow
}    // namespace pm_mode

