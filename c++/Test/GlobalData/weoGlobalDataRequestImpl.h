/**
 * @file  GlobalDataRequestImpl.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.07.20 18:37:17
 *
 * @version 0.01, Shishido Takuya, 2011.07.20 18:37:17
 *			0.02  Miayzaki Tomohiro Tue Feb 14 16:11:35 2012 監督リストのリクエストをUserDataServerAccess に投げるようにしました。
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef GLOBALDATA_GLOBALDATAREQUESTIMPL_HPP_INCLUDED
#define GLOBALDATA_GLOBALDATAREQUESTIMPL_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include "weoGlobalDataType.h"
#include "weoTypeList.h"


// weoGlobalData.h でも使用されるマクロ。一応 weoGlobalData.h で undef はしてる
#define OBJ_TYPE                            \
    typename pm_mode::task::TypeAt<         \
        typename pm_mode::task::TypeAt<     \
            GlobalDataTypeList::TList, modeID>::Result::TypeList::TList, objectID>::Result

//template<typename RequestFunctor>
//struct placeholder<GLOBALMEMBER_MYTEAM, MYTEAMMEMBER_USERTEAMDATA, RequestFunctor> {
//	void operator()(RequestFunctor& requestData) const throw() {
//		GlobalData::getInstance().getMyTeamAccessPoint().requestCreationMyTeamInfo(requestData.requestData_);
//		GlobalData::setCallBack<GLOBALMEMBER_MYTEAM, MYTEAMMEMBER_USERTEAMDATA, pm_mode::MyTeamSelectCreateModel>(requestData.response_.object_, requestData.response_.callBack_);
//	}
//};


namespace globaldata {


/********************************************************************
 * @brief dummy
 *******************************************************************/
template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
struct placeholder {
	// constructor
	placeholder(const RequestData& /*requestData*/, Instance& instance, void (Instance::*callback)(const OBJ_TYPE&)) throw() {
		(instance.*callback)(OBJ_TYPE());
	}
};
template<GlobalDataMember modeID, weUint objectID, typename RequestData>
struct placeholder<modeID, objectID, RequestData, pm_mode::NullType> {
	// constructor
	placeholder(const RequestData& /*requestData*/) throw() {
	}
};



template<GlobalDataMember modeID, weUint objectID, typename Instance>
struct placeholder<modeID, objectID, pm_mode::NullType, Instance> {
	placeholder(Instance& instance, void (Instance::*callback)(const OBJ_TYPE&)) throw() {
		(instance.*callback)(OBJ_TYPE());
	}
};



}    // namespace globaldata



// weoGlobalData.h でも使用されるマクロ。一応 weoGlobalData.h で undef はしてる
//#ifdef OBJ_TYPE
//#undef OBJ_TYPE
//#endif

#endif

