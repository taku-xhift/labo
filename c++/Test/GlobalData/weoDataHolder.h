/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.04 19:49:52
 *
 * @version 0.01, Shishido Takuya, 2011.04.04 19:49:52
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_DATAHOLDER_HPP_INCLUDED
#define PM_MODE_DATAHOLDER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <bitset>
#include "weDebug.h"
#include "weoSpTypeInfo.h"
#include "weoFlowException.h"
#include "weoCallBackFunctor.h"
#include "weoJsonParser.h"
#include "weoJsonIODeclaration.h"


namespace pm_mode {


template<typename Type>
class DataHolder
{
public:

	typedef Type DataType;      //!< template で指定された型の別名


	/****************************************************************
	 * @brief constructor
	 ***************************************************************/
	DataHolder() throw()
		: data_(NULL)
		, callBack_(NULL)
	{
	}


	/****************************************************************
	 * @brief destructor
	 * @note    継承されるので virtual
	 ***************************************************************/
	virtual ~DataHolder() throw() {
		this->release();
	}


	/****************************************************************
	 * @brief get して良いかどうかの判定関数
	 * @note    判定しているのは NULL かどうかだけ。
	 *              サーバから更新されたかは getState で確認
	 * @retval  true    get 可能
	 * @retval  false   get 不可能
	 ***************************************************************/
	bool hasData() const throw() {
		return (this->data_ != NULL);
	}


	/****************************************************************
	 * @brief getter
	 * @note    hasData でチェックしてから使うようにする
	 * @return  持っているデータの参照
	 * @except  UnReadyLoadData     サーバからデータがセットされていなかった場合
	 ***************************************************************/
	const DataType& get() const throw(task::UnReadyLoadData) {
		if (this->data_ == NULL) { throw task::UnReadyLoadData(ExceptionMessage("The object has not been made yet!!!")); }
		return *this->data_;
	}


	/****************************************************************
	 * @brief コールバックを登録する
	 * @note    一度呼び出されたらリセットされる
	 * @param[in]   object              呼び出しオブジェクト
	 * @param[in]   function            object のメンバ関数
	 * @tparam      ObjectType          コールバック関数をメンバ関数に持っているクラス
	 * @except      FlowLogicException          サーバからの返答よりも先に再度登録された
	 * @except      MemoryAllocateException     メモリ確保失敗
	 ***************************************************************/
	template<typename ObjectType>
	void setCallBack(ObjectType& object, void (ObjectType::*function)(const DataType&)) throw(task::MemoryAllocateException)
	{
		if (this->data_ == NULL) {
			try {
				this->callBack_ = NEW pm_mode::task::CallBackFunctor<ObjectType, DataType>(object, function);
				if (this->callBack_ == NULL) { throw std::bad_alloc(ExceptionMessage(typeid_of(DataType).name())); }
			} catch (std::bad_alloc& e) {
				throw task::MemoryAllocateException(ExceptionMessage(e.what()));
			}
		} else {
			//pm_mode::task::CallBackFunctor<ObjectType, DataType>(object, function)(*this->data_);
			this->callBack_ = new pm_mode::task::CallBackFunctor<ObjectType, DataType>(object, function);
		}
	}


	/****************************************************************
	 * @brief setter
	 * @note    データの保持だけで、アップロードはしない
	 * @param[in]   data    保存するデータの参照
	 * @except      MemoryAllocateException     メモリ確保に失敗
	 ***************************************************************/
	void set(const DataType& data) throw(task::MemoryAllocateException) {
		try {
			//this->release();
			if (this->data_ == NULL) {
				this->data_ = NEW DataType(data);
			} else {
				*this->data_ = data;
			}
			if (this->data_ == NULL) { throw std::bad_alloc(ExceptionMessage(typeid_of(DataType).name())); }
		} catch (std::bad_alloc& e) {
			throw task::MemoryAllocateException(ExceptionMessage(e.what()));
		}
	}


	/****************************************************************
	 * @brief サーバからのデータセット
	 * @note    コールバックが登録してあればそれの呼び出しも
	 * @param[in]   data    保存するデータの参照
	 * @except      MemoryAllocateException     メモリ確保に失敗
	 ***************************************************************/
	void setFromServer(const DataType& data) throw(task::MemoryAllocateException) {
		if (this->callBack_ != NULL) {
			(*this->callBack_)(data);
			//delete this->callBack_;
			//this->callBack_ = NULL;
		}

		try {
			if (this->data_ == NULL) {
				this->data_ = NEW DataType(data);
			} else {
				*this->data_ = data;
			}
			if (this->data_ == NULL) { throw std::bad_alloc(ExceptionMessage(typeid_of(DataType).name())); }
		} catch (std::bad_alloc& e) {
			throw task::MemoryAllocateException(ExceptionMessage(e.what()));
		}
	}


	/****************************************************************
	 * @brief データの解放関数
	 ***************************************************************/
	void create() throw(pm_mode::task::MemoryAllocateException) {
		if (this->data_ != NULL) {
			return;
		}

		try {
			this->data_ = NEW DataType();
			if (this->data_ == NULL) { throw std::bad_alloc(ExceptionMessage("")); }
		} catch (std::bad_alloc& e) {
			throw pm_mode::task::MemoryAllocateException(ExceptionMessage(e.what()));
		}
	}


	/****************************************************************
	 * @brief データの解放関数
	 ***************************************************************/
	void release() throw() {
		if (this->data_ != NULL) {
			delete this->data_;
			this->data_ = NULL;
		}
		if (this->callBack_ != NULL) {
			delete this->callBack_;
			this->callBack_ = NULL;
		}
	}

	/****************************************************************
	 * @brief 保持しているデータをサーバへアップする
	 * @note    仮
	 * @except  FlowLogicException  保持しているデータがない
	 ***************************************************************/
	void upload(json::object& object) const throw(task::FlowLogicException) {
		if (this->data_ == NULL) { throw task::FlowLogicException(ExceptionMessage(typeid_of(DataType).name())); }
		pm_mode::save(object, *this->data_);
	}


	/****************************************************************
	 * @brief サーバにデータ問い合わせをする
	 * @note    setCallBack との違いはコールバックオブジェクトを設定しなくていい
	 * @note    データが準備されているかは hasData でチェック
	 ***************************************************************/
	void ready() throw() {
		try {
			// 仮
			if (this->data_ == NULL) {
				this->data_ = NEW DataType();
			}
		} catch (std::bad_alloc&) {}

		WE_PRINTF("Ready of %s", typeid_of(DataType).name());
	}


	/****************************************************************
	 * @brief ファイルから読み取った json オブジェクトからデータを読み取らせる
	 * @param[in]   object  json オブジェクト
	 ***************************************************************/
	void load(const json::object& object) throw() {
		weoGlobalDataLoad(object, *this->data_);
	}



private:

	DataType*   data_;          //!< 格納されているデータ本体
	task::CallBackFunctorBase<DataType>* callBack_;      //!< 登録されたコールバック

};



}    // namespace pm_mode


#endif

