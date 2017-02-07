/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.05 18:24:33
 *
 * @version 0.01, Shishido Takuya, 2011.04.05 18:24:33
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_GLOBALDATACLASSBASE_HPP_INCLUDED
#define PM_MODE_GLOBALDATACLASSBASE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "weCommonType.h"
#include "weoGlobalDataClassBaseImpl.h"
#include "weoJsonParser.h"


namespace pm_mode {

/********************************************************************
 * @brief 
 *******************************************************************/
template<typename TypeList, weUint enumMax>
class GlobalDataClassBase
{
public:

	typedef typename TypeList TypeList;


	//! \brief constructor
	GlobalDataClassBase() throw() {}


	//! \brief destructor
	~GlobalDataClassBase() throw() {}


	/****************************************************************
	 * @brief get して良いかどうかの判定関数
	 * @note    サーバから更新されたかは getState で確認
	 * @tparam  i       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 * @retval  true    get 可能
	 * @retval  false   get 不可能
	 ***************************************************************/
	template<weUint i>
	bool hasData() const throw() {
		return this->impl_.hasData<i>();
	}


	/****************************************************************
	 * @brief getter
	 * @tparam      i           TypeList の中でアクセスしたい番号。enum で定義したもの。
	 * @return      i で指定した型のオブジェクト
	 * @except      UnReadyLoadData     メモリが確保されていない場合。
	 ***************************************************************/
	template<weUint i>
	typename const task::CulcResultType<TypeList, i>::Result&
		get() const throw(task::UnReadyLoadData)
	{
		try {
			return this->impl_.get<i>();
		} catch(task::UnReadyLoadData& e) {
			e << ExceptionMessage("");
			throw;
		}
	}


	/****************************************************************
	 * @brief set CallBack
	 * @tparam      i           TypeList の中でアクセスしたい番号。enum で定義したもの。
	 * @param[in]   object      呼び出しオブジェクト
	 * @param[in]   function    object のメンバ関数
	 * @tparam      ObjectType  コールバック関数をメンバ関数に持っているクラス
	 * @return      i で指定した型のオブジェクト
	 ***************************************************************/
	template<weUint i, typename ObjectType>
	void setCallBack(ObjectType& object,
	                 void (ObjectType::*function)(typename const task::CulcResultType<TypeList, i>::Result&))
		throw(task::FlowLogicException)
	{
		try {
			this->impl_.setCallBack<i>(object, function);
		} catch (task::FlowLogicException& e) {
			e << ExceptionMessage("");
			throw;
		} catch (task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}


	/****************************************************************
	 * @brief setter
	 * @param[in]   data    保存するデータの参照
	 * @except      MemoryAllocateException     メモリが確保できなかった
	 ***************************************************************/
	template<weUint i, typename DataType>
	void set(const DataType& data) throw(task::MemoryAllocateException) {
		try {
			this->impl_.set<i>(data);
		} catch(task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}


	/****************************************************************
	 * @brief setter
	 * @param[in]   data    保存するデータの参照
	 * @except  task::MemoryAllocateException     所持しているデータが NULL。判定は hasData で。
	 ***************************************************************/
	template<weUint i, typename ValueType>
	void setFromServer(const ValueType& value) throw(task::MemoryAllocateException) {
		try {
			this->impl_.setFromServer<i>(value);
		} catch(task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}


	/****************************************************************
	 * @brief メモリを解放する
	 * @tparam[in]  i       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 ***************************************************************/
	template<weUint i>
	void create() throw(pm_mode::task::MemoryAllocateException) {
		try {
			this->impl_.create<i>();
		} catch (pm_mode::task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}


	/****************************************************************
	 * @brief メモリを解放する
	 * @tparam[in]  i       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 ***************************************************************/
	template<weUint i>
	void release() throw() {
		this->impl_.release<i>();
	}


	/****************************************************************
	 * @brief メモリを解放する
	 * @tparam      i       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 ***************************************************************/
	template<weUint i>
	void upload() throw() {
		this->impl_.upload<i>();
	}


	/****************************************************************
	 * @brief サーバへデータを問い合わせる
	 * @tparami       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 ***************************************************************/
	template<weUint i>
	void ready() throw() {
		this->impl_.ready<i>();
	}


	/****************************************************************
	 * @brief Fileにセーブする
	 * @tparam      i       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 ***************************************************************/
	template<weUint i>
	void saveFile() throw() {
		this->impl_.upload<i>();
	}


	/****************************************************************
	 * @brief Fileからロードする
	 * @tparami       TypeList の中でアクセスしたい番号。enum で定義したもの。
	 ***************************************************************/
	template<weUint i>
	void loadFile() throw() {
		this->impl_.ready<i>();
	}


	/****************************************************************
	 * @brief ファイルから読み取った json オブジェクトからデータを読み取らせる
	 * @param[in]   object  json オブジェクト
	 ***************************************************************/
	template<weUint i>
	void load(const json::object& object) throw() {
		this->impl_.load<i>(object);
	}


private:

	GlobalDataClassBaseImpl<TypeList, enumMax> impl_;   //!< データ本体

};    // class GlobalDataClassBase

}    // namespace pm_mode


#endif

