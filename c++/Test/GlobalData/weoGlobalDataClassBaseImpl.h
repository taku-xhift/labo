/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.05 10:56:01
 *
 * @version 0.01, Shishido Takuya, 2011.04.05 10:56:01
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_GLOBALDATAIMPL_HPP_INCLUDED
#define PM_MODE_GLOBALDATAIMPL_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "weDebug.h"
#include "weCommonType.h"
#include "weoDataHolder.h"
#include "weoJsonParser.h"


namespace pm_mode {

/********************************************************************
 * @brief 実装本体
 *******************************************************************/
template<typename TypeList, unsigned int typeListLength>
class GlobalDataClassBaseImpl
{
public:

	typedef TypeList List;


	//! \brief constructor
	GlobalDataClassBaseImpl() throw() {
		// ここに引っかかる場合には各 GlobalObject で指定したオブジェクトの enum の数と
		// TypeList に追加した型の数があっているか確認してください
		STATIC_ASSERT((task::Length<TypeList::TList>::value == typeListLength), "TypeList で指定された型の数とオブジェクトの数が不一致");
	}

	//! \brief destructor
	virtual ~GlobalDataClassBaseImpl() throw() {}

	template<unsigned int i>
	bool hasData() const throw() {
		return task::Field<i>(this->list_).hasData();
	}

	template<unsigned int i>
	typename const task::FieldHelper<List, i>::ResultType::DataType& get() const throw(task::UnReadyLoadData) {
		try {
			return task::Field<i>(this->list_).get();
		} catch (task::UnReadyLoadData& e) {
			e << ExceptionMessage("");
			throw;
		}
	}

	template<weUint i, typename ObjectType>
	void setCallBack(ObjectType& object,
	                 void (ObjectType::*function)(typename const task::FieldHelper<List, i>::ResultType::DataType&))
		throw(task::FlowLogicException, task::MemoryAllocateException)
	{
		try {
			return task::Field<i>(this->list_).setCallBack(object, function);
		} catch (task::FlowLogicException& e) {
			e << ExceptionMessage("");
			throw;
		} catch (task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}

	template<weUint i, typename ValueType>
	void set(const ValueType& value) throw(task::MemoryAllocateException) {
		try {
			return task::Field<i>(this->list_).set(value);
		} catch (task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}

	template<weUint i, typename ValueType>
	void setFromServer(const ValueType& value) throw(task::MemoryAllocateException) {
		try {
			return task::Field<i>(this->list_).setFromServer(value);
		} catch (task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}

	template<weUint i>
	void create() throw(pm_mode::task::MemoryAllocateException) {
		try {
			task::Field<i>(this->list_).create();
		} catch (pm_mode::task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}

	template<weUint i>
	void release() throw() {
		task::Field<i>(this->list_).release();
	}

	template<weUint i>
	void upload() throw() {
		task::Field<i>(this->list_).upload();
	}

	template<weUint i>
	void ready() throw() {
		task::Field<i>(this->list_).ready();
	}

	template<weUint i>
	void load(const json::object& object) throw() {
		task::Field<i>(this->list_).load(object);
	}


private:

	TypeList list_;     //!< データ本体

};    // class GlobalDataClassBaseImpl

}    // namespace pm_mode


#endif

