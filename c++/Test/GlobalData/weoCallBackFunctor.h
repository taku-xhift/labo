/**
 * @file  CallBackFunctor.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.06.01 15:02:24
 *
 * @version 0.01, Shishido Takuya, 2011.06.01 15:02:24
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef CALLBACKFUNCTOR_HPP_INCLUDED
#define CALLBACKFUNCTOR_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------


namespace pm_mode {
namespace task {


template<typename DataType>
class CallBackFunctorBase {
public:
	virtual ~CallBackFunctorBase() throw() {
		
	}

	virtual void operator()(const DataType& data) throw() = 0;
};



// 今後これを特殊化していく
template<typename ObjectType, typename DataType>
struct CallBackFunctor
	: public CallBackFunctorBase<DataType>
{
	typedef void (ObjectType::*CallBack)(const DataType&);

	CallBackFunctor(ObjectType& object, CallBack callBack) throw()
		: object_(object)
		, callBack_(callBack)
	{
		
	}

	// 何もしない
	~CallBackFunctor() {}

	CallBackFunctor& operator=(const CallBackFunctor& other) throw() {
		this->object_ = other.object_;
		this->callBack_ = other.callBack_;
	}

	void operator()(const DataType& data) throw() {
		(object_.*callBack_)(data);
	}

	ObjectType& object_;
	CallBack    callBack_;
};


}   // namespace task
}   // namespace pm_mode

#endif

