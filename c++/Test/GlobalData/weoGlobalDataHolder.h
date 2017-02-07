/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.06 17:24:30
 *
 * @version 0.01, Shishido Takuya, 2011.04.06 17:24:30
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_GLOBALDATAHOLDER_HPP_INCLUDED
#define PM_MODE_GLOBALDATAHOLDER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "weDebug.h"
#include "weCommonType.h"
#include "weoFlowException.h"
//#include "weoFlowDefine.h"
#include "weoExceptionMessageCreator.h"


namespace pm_mode {


template<typename Type>
class GlobalDataHolder
{
public:
	typedef Type DataType;


	//! \brief constructor
	GlobalDataHolder() throw() : data_(NULL) {}


	//! \brief destructor
	virtual ~GlobalDataHolder() throw() {
		this->destroy();
	}


	//! \brief copy constructor
	GlobalDataHolder(const GlobalDataHolder& other) throw()
		: data_(NEW DataType(*other.data_))
	{
	}


	//! \brief operator
	GlobalDataHolder& operator=(const GlobalDataHolder& other) throw() {
		*this->data_ = *other.data_;
		return *this;
	}


	/****************************************************************
	 * @brief メモリを確保する
	 * @except  MemoryAllocateException     メモリの確保に失敗
	 ***************************************************************/
	void create() throw(pm_mode::task::MemoryAllocateException) {
		try {
			if (this->data_ == NULL) {
				this->data_ = NEW DataType();
				if (this->data_ == NULL) { throw std::bad_alloc(ExceptionMessage("")); }
			}
		} catch (std::bad_alloc& e) {
			throw pm_mode::task::MemoryAllocateException(ExceptionMessage(e.what()));
		}
	}


	/****************************************************************
	 * @brief メモリを解放する
	 ***************************************************************/
	void destroy() throw() {
		if (this->data_ != NULL) {
			delete this->data_;
			this->data_ = NULL;
		}
	}


	/****************************************************************
	 * @brief get 出来るかどうかのチェッカー
	 * @retval      true    可能。
	 * @retval      false   不可能。create しておくこと。
	 ***************************************************************/
	bool hasData() throw() {
		return (this->data_ != NULL);
	}


	/****************************************************************
	 * @brief オブジェクトを取得する
	 * @return  const でない参照。get にも使われるので。
	 * @except  UnReadyLoadData     メモリを確保していない場合。create を呼ぶこと
	 ***************************************************************/
	DataType& get() throw(pm_mode::task::UnReadyLoadData) {
		if (this->data_ == NULL) { throw pm_mode::task::UnReadyLoadData(ExceptionMessage("Dont create object!!!")); }
		return *this->data_;
	}


private:

	DataType* data_;        //!< データ本体

};    // class GlobalDataHolder

}    // namespace pm_mode


#endif

