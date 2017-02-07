/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.04 15:08:30
 *
 * @version 0.01, Shishido Takuya, 2011.04.04 15:08:30
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#include "pm_mode.cnf"
#if (PM_MODE_ALLMENU_OFF != 1)

#ifndef PM_MODE_GLOBALDATA_HPP_INCLUDED
#define PM_MODE_GLOBALDATA_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <string>
#include "boost/thread/shared_mutex.hpp"
#include "boost/thread/locks.hpp"
#include "weoGlobalDataRequestImpl.h"
#include "weoGlobalDataType.h"
#include "weoGlobalDataHolder.h"
#include "weoFlowMutex.h"
#include "weoIntType.h"
#include "weoNonCopyable.h"
#include "weoFlowException.h"
#include "weDebug.h"
#include "weoSpTypeInfo.h"
#include "weoJsonParser.h"
#include "weoTypeList.h"
#include "weoJsonIODeclaration.h"
#include "weoDLLModefied.h"


// グローバルデータの型
#include "weoCommonGlobalData.h"
#include "weoLeagueGlobalData.h"
#include "weoMyTeamGlobalData.h"
#include "weoUnrankMatchGlobalData.h"



template<unsigned int Type>
std::string getDataFileName();

template<> inline
std::string getDataFileName<GLOBALMEMBER_COMMON>() {
	return "Common.json";
}
template<> inline
std::string getDataFileName<GLOBALMEMBER_LEAGUE>() {
	return "League.json";
}
template<> inline
std::string getDataFileName<GLOBALMEMBER_MYTEAM>() {
	return "MyTeam.json";
}
template<> inline
std::string getDataFileName<GLOBALMEMBER_UNRANKMATCH>() {
	return "Unrank.json";
}
void weoGlobalDataSave(::pm_mode::json::object& obj, int value) throw();
void weoGlobalDataLoad(const ::pm_mode::json::object& obj, int& value) throw();
void weoGlobalDataSave(::pm_mode::json::object& obj, const UserInfo& value) throw();
void weoGlobalDataLoad(const ::pm_mode::json::object& obj, UserInfo& value) throw();



//-----------------------------------------------------
//  define
//-----------------------------------------------------
typedef pm_mode::WindowsMutex GlobalDataMutex;

/*
 * @brief str から trimmer を取り除く
 * @param[in, out]  str         取り除かれる文字列
 * @param[in]       trimmer     取り除く文字列
 */
WE_MODE_DLL_EXPORT void strTrimming(std::string& str, const std::string& trimmer) throw();


// オブジェクトの型計算。それをキーにしているので OBJ_NAME
#define OBJ_NAME                            \
typeid_of(                                  \
    pm_mode::task::TypeAt<                  \
        pm_mode::task::TypeAt<              \
            GlobalDataTypeList::TList, modeID>::Result::TypeList::TList, objectID>::Result\
            ).name()

//#define OBJ_TYPE                            \
//    typename pm_mode::task::TypeAt<         \
//        typename pm_mode::task::TypeAt<     \
//            GlobalDataTypeList::TList, modeID>::Result::TypeList::TList, objectID>::Result



// GlobalData の扱い方
//
//  シングルトン。
//      LeagueGlobalData が基本的な使い方になる。
//              1. typedef の中身を増やす(データの型を決定している)
//              2. enum の中にアクセスする名前を登録する
//          以上で新規オブジェクトの追加は終了
//
//      全オブジェクト共有の関数などは
//          class DataHolder に追加する。
//          実際 set, get, create, release 等はこれで自動で追加されていて、
//          必要なものが増えたり減ったりした場合にはこのクラス内をいじるだけで
//          全てのオブジェクトに影響がでるようになっている。
//          いちいち共有のために１つのクラスを継承したクラスにする必要はない。
//
//          インターフェースを変更した際には
//          LeagueGlobalData 等のインターフェースも適時操作すること。
//          また、特定のオブジェクトの set はさせたくない、などは
//          LeagueGlobalData の set 等で、引数にもらっている i を使って
//          STATIC_ASSERT を仕掛けるとコンパイルエラーを発生させられるのでそれでチェックする。
//
//  ■ 使用例
//
//      main.cpp
//
//
//  #include <iostream>
//  #include "weoGlobalData.h"
//
//
//  int main() {
//      // メモリ確保
//      GlobalData::create();
//      GlobalData::create<GLOBALMEMBER_LEAGUE>();
//
//      // モード毎のグローバルデータの取得法
//      const LeagueGlobalData& league = GlobalData::get<GLOBALMEMBER_LEAGUE>();
//
//      // enum で定義された ID でアクセスするモードとオブジェクトを決めて
//      //      引数にデータをセットする
//      GlobalData::set<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>(3);
//
//      UserInfo inputUserInfo;
//      inputUserInfo.name_ = "test";
//      GlobalData::set<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USERINFO>(inputUserInfo);
//
//      MyTeam inputMyTeam;
//      GlobalData::set<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_MYTEAM>(inputMyTeam);
//
//
//      // ID でゲットしてくる
//      // 取得方法は２パターン
//      int id              = GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>();
//      UserInfo userInfo   = league.get<LEAGUEMEMBER_USERINFO>();
//      MyTeam myTeam       = league.get<LEAGUEMEMBER_MYTEAM>();
//
//
//      // ゲットしたものが正しいか検証
//      std::cout << "id = "                << id               << std::endl;
//      std::cout << "userInfo.name_ = "    << userInfo.name_   << std::endl;
//      std::cout << "userInfo.win_ = "     << userInfo.win_    << std::endl;
//      std::cout << "myTeam.teamName__ = " << myTeam.teamName_ << std::endl;
//
//
//      // ID でその他関数を呼び出す
//      // 呼び出せる関数の大本は class DataHolder で
//      // class LeagueGlobalData はそれをラップしたものになる
//      GlobalData::release<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>();
//      GlobalData::create<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>(33);
//  }
//
//




//! \brief グローバルデータを一括管理するクラス
class WE_MODE_DLL_EXPORT GlobalData
	: private pm_mode::NonCopyable
{
	typedef boost::shared_mutex                     Mutex;
	typedef boost::shared_lock<Mutex>               ReadLock;
	typedef boost::upgrade_lock<Mutex>              UpLock;
	typedef boost::upgrade_to_unique_lock<Mutex>    WriteLock;

public:


	/****************************************************************
	 * @brief getInstance 可能かどうか
	 * @retval      true    可能。
	 * @retval      false   不可能。create がされていない
	 ***************************************************************/
	static bool hasData() throw();


	/****************************************************************
	 * @brief オブジェクト取得
	 * @note    const 参照の返却。
	 *            データをセットしたい場合は素直に set を呼ぶこと
	 * @return      クラスオブジェクト
	 * @except      UnReadyLoadData     メモリが NULL だった
	 ***************************************************************/
	static const GlobalData& getInstance() throw(pm_mode::task::UnReadyLoadData);


	/****************************************************************
	 * @brief メモリ確保
	 ***************************************************************/
	static void create() throw(pm_mode::task::MemoryAllocateException);


	/****************************************************************
	 * @brief メモリ解放
	 ***************************************************************/
	static void destroy() throw();


	/********************************************************************
	 * @brief get して良いかどうかの判定関数
	 * @note    モード ID を指定する必要がある
	 * @retval  true    get 可能
	 * @retval  false   get 不可能
	 * @tparam  modeID      モード ID
	 * @tparam  objectID    モード毎に定義したオブジェクト ID
	 *******************************************************************/
	template<GlobalDataMember modeID>
	static bool hasData() throw();

	template<GlobalDataMember modeID, weUint objectID>
	static bool hasData() throw();


	/********************************************************************
	 * @brief getter
	 * @return  ID で指定したオブジェクト型の参照。
	 * @tparam  modeID      モード ID
	 * @tparam  objectID    モード毎に定義したオブジェクト ID
	 * @except  FlowLogicException     所持しているデータが NULL。判定は hasData で。
	 *******************************************************************/
	template<GlobalDataMember modeID>
	static typename const pm_mode::task::CulcResultType<GlobalDataTypeList, modeID>::Result&
		get() throw(pm_mode::task::UnReadyLoadData);

	template<GlobalDataMember modeID, weUint objectID>
	static typename const pm_mode::task::CulcGetterResultType<GlobalDataTypeList, modeID, objectID>::Result&
		get() throw(pm_mode::task::UnReadyLoadData);


	/********************************************************************
	 * @brief コールバックオブジェクトを登録する
	 * @parma[in]   callBackFunction() を実装したオブジェクト
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @except      InvalidArgumentException    object が NULL オブジェクトだった
	 * @except      FlowLogicException          サーバからの返答よりも先に再度登録された
	 * @except      MemoryAllocateException     メモリ確保失敗
	 *******************************************************************/
	template<GlobalDataMember modeID, weUint objectID, typename ObjectType>
	static void setCallBack(ObjectType& object, 
							void (ObjectType::*function)(const OBJ_TYPE&))
		throw(pm_mode::task::FlowLogicException, pm_mode::task::MemoryAllocateException, pm_mode::task::InvalidArgumentException);


	/********************************************************************
	 * @brief setter
	 * @note    getInstance で const でない参照を返すとスレッドセーフでなくなる。
	 *              なのでこれで mode と そのオブジェクトの ID を指定してもらって保存する
	 * @param[in]   value       保存するオブジェクト
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @tparam      ValueType   保存するオブジェクトの型。特に指定しなくてもいい
	 * @except      UnReadyLoadData             モード単位でのメモリが確保されていない
	 * @except      MemoryAllocateException     メモリ確保失敗
	 *******************************************************************/
	template<GlobalDataMember modeID, weUint objectID, typename ValueType>
	static void set(const ValueType& value) throw();


	/****************************************************************
	 * @brief setter
	 * @note    getInstance で const でない参照を返すとスレッドセーフでなくなる。
	 *              なのでこれで mode と そのオブジェクトの ID を指定してもらって保存する
	 * @param[in]   value       保存するオブジェクト
	 * @tparam      modeID      モードの指定
	 * @tparam      obuectID    オブジェクトの指定
	 * @tparam      ValueType   保存するオブジェクトの型。特に指定しなくてもいい
	 * @except      UnReadyLoadData             モード単位でのメモリが確保されていない
	 * @except      MemoryAllocateException     メモリ確保失敗
	 ***************************************************************/
	template<GlobalDataMember modeID, weUint objectID, typename ValueType>
	static void setFromServer(const ValueType& value) throw();


	/****************************************************************
	 * @brief データの作成関数
	 * @tparam      modeID      モード
	 * @tparam      objectID    オブジェクトの ID
	 * @tparam      ValueType   引数に要求しているデータの型
	 * @except      MemoryAllocateException     メモリ確保失敗
	 ***************************************************************/
	// モード等の大きいデータを作成する
	template<GlobalDataMember modeID>
	static void create() throw(pm_mode::task::MemoryAllocateException);

	template<GlobalDataMember modeID, weUint objectID>
	static void create() throw(pm_mode::task::MemoryAllocateException);


	/****************************************************************
	 * @brief データの解放関数
	 * @tparam      modeID      モード
	 * @tparam      objectID    オブジェクトの ID
	 ***************************************************************/
	template<GlobalDataMember modeID>
	static void release() throw();

	template<GlobalDataMember modeID, weUint objectID>
	static void release() throw();


	/****************************************************************
	 * @brief サーバにデータをアップする
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
	 ***************************************************************/
	template<GlobalDataMember modeID, weUint objectID>
	static void upload() throw();


	/****************************************************************
	 * @brief コールバック等を登録せずにサーバにデータを問い合わせる
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
	 ***************************************************************/
	template<GlobalDataMember modeID>
	static void ready() throw(pm_mode::task::MemoryAllocateException);

	template<GlobalDataMember modeID, weUint objectID>
	static void ready() throw(pm_mode::task::MemoryAllocateException);

	/****************************************************************
	 * @brief ファイルにデータをアップする
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
	 ***************************************************************/
	template<GlobalDataMember modeID, weUint objectID>
	static void saveFile() throw();


	/****************************************************************
	 * @brief ファイルからデータを問い合わせる
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
	 ***************************************************************/
	template<GlobalDataMember modeID>
	static void loadFile() throw(pm_mode::task::MemoryAllocateException);

	template<GlobalDataMember modeID, weUint objectID>
	static void loadFile() throw(pm_mode::task::MemoryAllocateException);


	/****************************************************************
	 * @brief コールバック等を登録しつつ、サーバにデータを問い合わせる
	 * @note    現在はメンバ関数しか受け付けていない
	 * @tparam      modeID      モード ID
	 * @tparam      objectID    モード毎に定義したオブジェクト ID
	 * @tparam      RequestData サーバ側に要求されているデータ
	 * @tparam      Instance    コールバック関数を所有する
	 ***************************************************************/
	template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
	static void request(Instance& instance, void (Instance::*callback)(const OBJ_TYPE&)) throw();


	template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
	static void request(const RequestData& requestData) throw();

	template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
	static void request(const RequestData& requestData, Instance& instance, void (Instance::*callback)(const OBJ_TYPE&)) throw();


private:


	/****************************************************************
	 * @brief constructor
	 ***************************************************************/
	GlobalData() throw();


	/****************************************************************
	 * @brief destructor
	 ***************************************************************/
	~GlobalData() throw();


	/****************************************************************
	 * @brief copy constructor の禁止
	 ***************************************************************/
	GlobalData(const GlobalData&) throw();


	/****************************************************************
	 * @brief = の禁止
	 ***************************************************************/
	GlobalData& operator=(const GlobalData&) throw();


	/********************************************************************
	 * @brief 自分自身で使うためのゲッタ
	 * @note    const でない参照を返す。これを外部に公開するとスレッドアンセーフになるので。
	 * @param[in]   オーバーロード用
	 * @tparam      modeID      モード ID
	 *******************************************************************/
	template<GlobalDataMember modeID>
	static typename pm_mode::task::CulcResultType<GlobalDataTypeList, modeID>::Result&
		get(pm_mode::IntType<modeID>) throw(pm_mode::task::UnReadyLoadData);


private:

	GlobalDataTypeList  list_;      //!< モード用グローバルデータ本体

	static GlobalData*  this_;      //!< 自分自身
	static Mutex        mutex_;     //!< Mutex。マルチスレッド対応用。typedef を入れ替えると切り替えが可能。

};








////  以下、実装本体   //////////////////////////////////////////////


/********************************************************************
 * @brief get して良いかどうかの判定関数
 * @note    モード ID を指定する必要がある
 * @retval  true    get 可能
 * @retval  false   get 不可能
 * @tparam  modeID      モード ID
 * @tparam  objectID    モード毎に定義したオブジェクト ID
 *******************************************************************/
template<GlobalDataMember modeID>
bool GlobalData::hasData() throw() {
	ReadLock lock(mutex_);
	return pm_mode::task::Field<modeID>(this_->list_).hasData();
}

template<GlobalDataMember modeID, weUint objectID>
bool GlobalData::hasData() throw() {
	if (hasData<modeID>() == false) { return false; }

	ReadLock lock(mutex_);
	return get<modeID>().hasData<objectID>();
}


/********************************************************************
 * @brief getter
 * @return  ID で指定したオブジェクト型の参照。
 * @tparam  modeID      モード ID
 * @tparam  objectID    モード毎に定義したオブジェクト ID
 * @except  FlowLogicException     所持しているデータが NULL。判定は hasData で。
 *******************************************************************/
template<GlobalDataMember modeID>
typename const pm_mode::task::CulcResultType<GlobalDataTypeList, modeID>::Result&
GlobalData::get() throw(pm_mode::task::UnReadyLoadData)
{
	if (GlobalData::hasData<modeID>() == false) {
		throw pm_mode::task::UnReadyLoadData(ExceptionMessage("The object has not been made yet!!!"));
	}

	try {
		ReadLock lock(mutex_);
		return pm_mode::task::Field<modeID>(this_->list_).get();
	} catch (pm_mode::task::UnReadyLoadData& e) {
		e << ExceptionMessage("");
		throw;
	}
}

template<GlobalDataMember modeID, weUint objectID>
typename const pm_mode::task::CulcGetterResultType<GlobalDataTypeList, modeID, objectID>::Result&
GlobalData::get() throw(pm_mode::task::UnReadyLoadData)
{
	if (GlobalData::hasData<modeID>() == false
		|| GlobalData::hasData<modeID, objectID>() == false)
	{
		throw pm_mode::task::UnReadyLoadData(ExceptionMessage("The object has not been made yet!!!"));
	}

	try {
		ReadLock lock(mutex_);
		return pm_mode::task::Field<modeID>(this_->list_).get().get<objectID>();
	} catch (pm_mode::task::UnReadyLoadData& e) {
		e << ExceptionMessage("");
		throw;
	}
}


/********************************************************************
 * @brief コールバックオブジェクトを登録する
 * @parma[in]   callBackFunction() を実装したオブジェクト
 * @tparam  modeID      モード ID
 * @tparam  objectID    モード毎に定義したオブジェクト ID
 * @except      FlowLogicException          サーバからの返答よりも先に再度登録された
 * @except      MemoryAllocateException     メモリ確保失敗
 *******************************************************************/
template<GlobalDataMember modeID, weUint objectID, typename ObjectType>
void GlobalData::setCallBack(ObjectType& object,
							void (ObjectType::*function)(const OBJ_TYPE&))
throw(pm_mode::task::FlowLogicException, pm_mode::task::MemoryAllocateException)
{
	try {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		// ここでコンパイルエラーになる場合は
		// CallBack 関数の未登録が原因です。
		// weoAbstractCallBackBase.h の AbstractCallBackBase を継承するか
		// callBackFunction(const T value) を実装してください。
		pm_mode::task::Field<modeID>(this_->list_).get().setCallBack<objectID>(object, function);
	} catch (pm_mode::task::FlowLogicException& e) {
		e << ExceptionMessage("");
		throw;
	} catch (pm_mode::task::MemoryAllocateException& e) {
		e << ExceptionMessage("");
		throw;
	}
}


/********************************************************************
 * @brief setter
 * @note    getInstance で const でない参照を返すとスレッドセーフでなくなる。
 *              なのでこれで mode と そのオブジェクトの ID を指定してもらって保存する
 * @param[in]   value       保存するオブジェクト
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @tparam      ValueType   保存するオブジェクトの型。特に指定しなくてもいい
 * @except      UnReadyLoadData             モード単位でのメモリが確保されていない
 * @except      MemoryAllocateException     メモリ確保失敗
 *******************************************************************/
template<GlobalDataMember modeID, weUint objectID, typename ValueType>
void GlobalData::set(const ValueType& value) throw(pm_mode::task::UnReadyLoadData, pm_mode::task::MemoryAllocateException)
{
	if (hasData<modeID>() == false) { create<modeID>(); }
	if (hasData<modeID, objectID>() == false) { create<modeID, objectID>(); }

	try {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		//get<modeID>(pm_mode::IntType<modeID>()).set<objectID>(value);
		pm_mode::task::Field<modeID>(this_->list_).get().set<objectID>(value);
	} catch (pm_mode::task::MemoryAllocateException& e) {
		e << ExceptionMessage("");
		throw;
	}
}


/********************************************************************
 * @brief setter
 * @note    getInstance で const でない参照を返すとスレッドセーフでなくなる。
 *              なのでこれで mode と そのオブジェクトの ID を指定してもらって保存する
 * @param[in]   value       保存するオブジェクト
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @tparam      ValueType   保存するオブジェクトの型。特に指定しなくてもいい
 * @except      UnReadyLoadData             モード単位でのメモリが確保されていない
 * @except      MemoryAllocateException     メモリ確保失敗
*******************************************************************/
template<GlobalDataMember modeID, weUint objectID, typename ValueType>
void GlobalData::setFromServer(const ValueType& value) throw(pm_mode::task::UnReadyLoadData, pm_mode::task::MemoryAllocateException)
{
	try {
		if (hasData<modeID>() == false) {
			create<modeID>();
		}
		if (hasData<modeID, objectID>() == false) {
			create<modeID, objectID>();
		}

		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		//get<modeID>(pm_mode::IntType<modeID>()).setFromServer<objectID>(value);
		pm_mode::task::Field<modeID>(this_->list_).get().setFromServer<objectID>(value);
	} catch (pm_mode::task::MemoryAllocateException& e) {
		e << ExceptionMessage("");
		throw;
	}
}


/********************************************************************
 * @brief データの作成関数
 * @note    既に作られていれば何もしない
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @tparam      ValueType   引数に要求しているデータの型
 * @except      MemoryAllocateException     メモリ確保失敗
 *******************************************************************/
template<GlobalDataMember modeID>
void GlobalData::create() throw(pm_mode::task::MemoryAllocateException)
{
	if (hasData<modeID>() == true) { return; }

	try {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		pm_mode::task::Field<modeID>(this_->list_).create();
	} catch (pm_mode::task::MemoryAllocateException& e) {
		e << ExceptionMessage("");
		throw;
	}
}
template<GlobalDataMember modeID, weUint objectID>
void GlobalData::create() throw(pm_mode::task::MemoryAllocateException)
{
	if (hasData<modeID>() == true && hasData<modeID, objectID>() == true) { return; }

	try {
		if (hasData<modeID>() == false) {
			UpLock uplock(mutex_);
			WriteLock writeLock(uplock);

			create<modeID>();
		}
	} catch (pm_mode::task::MemoryAllocateException& e) {
		e << ExceptionMessage("");
		throw;
	}

	try {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		pm_mode::task::Field<modeID>(this_->list_).get().create<objectID>();
	} catch (pm_mode::task::MemoryAllocateException& e) {
		e << ExceptionMessage("");
		throw;
	}
}


/********************************************************************
 * @brief データの解放関数
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 *******************************************************************/
template<GlobalDataMember modeID>
void GlobalData::release() throw()
{
	if (hasData<modeID>() == false) { return; }

	UpLock uplock(mutex_);
	WriteLock writeLock(uplock);

	pm_mode::task::Field<modeID>(this_->list_).release();
}

template<GlobalDataMember modeID, weUint objectID>
void GlobalData::release() throw()
{
	if (hasData<modeID>() == false || hasData<modeID, objectID>() == false) {
		return;
	}

	UpLock uplock(mutex_);
	WriteLock writeLock(uplock);

	//get<modeID>(pm_mode::IntType<modeID>()).release<objectID>();
	pm_mode::task::Field<modeID>(this_->list_).get().release<objectID>();
}


/****************************************************************
 * @brief ファイルにデータをアップする
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
 ***************************************************************/
template<GlobalDataMember modeID, weUint objectID>
void GlobalData::saveFile() throw(pm_mode::task::MemoryAllocateException)
{
	if (hasData<modeID>() == false || hasData<modeID, objectID>() == false) {
		throw pm_mode::task::UnReadyLoadData(ExceptionMessage("The object has not been made yet!!!"));
	}

	const std::string& fileName = getDataFileName<modeID>();

	pm_mode::json::value value(pm_mode::json::object_type);
	std::string name = OBJ_NAME;
	strTrimming(name, " ");

	const bool couldRead = pm_mode::json::readJsonFile(value, fileName.c_str());
	bool isExist = false;
	if (couldRead == true) {
		isExist = !value.get(name).is<pm_mode::json::null>();
	}

	if (isExist == true) {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		pm_mode::json::object& obj = value.get<pm_mode::json::object>()[name].get<pm_mode::json::object>();
		weoGlobalDataSave(obj, pm_mode::task::Field<modeID>(this_->list_).get().get<objectID>());
	} else {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		pm_mode::json::object obj;
		weoGlobalDataSave(obj, pm_mode::task::Field<modeID>(this_->list_).get().get<objectID>());
		pm_mode::json::object& temp = value.get<pm_mode::json::object>();
		temp.insert(name, pm_mode::json::value(obj));
	}


	const std::string& data = value.serialize();

	// ファイル出力
	{
		std::ofstream ofs(fileName.c_str(), std::ios::out|std::ios::trunc);
		const std::ios_base::io_state state = ofs.rdstate();

		if (state != std::ios_base::goodbit) {
			WE_ASSERT(false, "some error");
		}

		ofs << data << std::endl;
		ofs.close();
	}
}

/****************************************************************
 * @brief サーバにデータをアップする
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
 ***************************************************************/
template<GlobalDataMember modeID, weUint objectID>
void GlobalData::upload() throw(pm_mode::task::MemoryAllocateException)
{
	GlobalData::saveFile<modeID, objectID>();
}


/****************************************************************
 * @brief      ファイルからデータを読み込む
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
 ***************************************************************/
template<GlobalDataMember modeID>
void GlobalData::loadFile() throw(pm_mode::task::MemoryAllocateException)
{
	if (GlobalData::hasData<modeID>() == false) { GlobalData::create<modeID>(); }

	std::string fileName = getConfigDirecotry();
	fileName += getDataFileName<modeID>();

	pm_mode::json::value value;
	std::string name = OBJ_NAME;
	strTrimming(name, " ");

	if (pm_mode::json::readJsonFile(value, fileName.c_str())) {
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);
		//get<modeID>(pm_mode::IntType<modeID>()).load(value.get(name));
		pm_mode::task::Field<modeID>(this_->list_).load(value.get(name));
	} else {
		if (GlobalData::hasData<modeID>() == false) { GlobalData::create<modeID>(); }
	}
}

template<GlobalDataMember modeID, weUint objectID>
void GlobalData::loadFile() throw(pm_mode::task::UnReadyLoadData)
{
	if (hasData<modeID>() == false) { create<modeID>(); }
	if (hasData<modeID, objectID>() == false) { create<modeID, objectID>(); }

	const std::string fileName = getDataFileName<modeID>();

	pm_mode::json::value value;
	std::string name = OBJ_NAME;
	strTrimming(name, " ");


	bool couldRead = pm_mode::json::readJsonFile(value, fileName.c_str());
	bool isExist = false;
	if (couldRead == true && value.is<pm_mode::json::object>() == true) {
		isExist = !value.get(name).is<pm_mode::json::null>();
	}

	if (isExist == true)
	{
		UpLock uplock(mutex_);
		WriteLock writeLock(uplock);

		pm_mode::json::object& obj = value.get<pm_mode::json::object>()[name].get<pm_mode::json::object>();
		//get<modeID>(pm_mode::IntType<modeID>()).load<objectID>(obj);
		pm_mode::task::Field<modeID>(this_->list_).get().load<objectID>(obj);
	} else {
		try {
			GlobalData::create<modeID, objectID>();
		} catch (pm_mode::task::MemoryAllocateException& e) {
			e << ExceptionMessage("");
			throw;
		}
	}
}


/****************************************************************
 * @brief コールバック等を登録せずにサーバにデータを問い合わせる
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @except      UnReadyLoadData     モード単位でのメモリが確保されていない
 ***************************************************************/
template<GlobalDataMember modeID>
void GlobalData::ready() throw(pm_mode::task::MemoryAllocateException) {
	loadFile<modelID>();
}

template<GlobalDataMember modeID, weUint objectID>
void GlobalData::ready() throw(pm_mode::task::UnReadyLoadData) {
	loadFile<modeID, objectID>();
}


/****************************************************************
 * @brief コールバック等を登録しつつ、サーバにデータを問い合わせる
 * @note    現在はメンバ関数しか受け付けていない
 * @tparam      modeID      モード ID
 * @tparam      objectID    モード毎に定義したオブジェクト ID
 * @tparam      RequestData サーバ側に要求されているデータ
 * @tparam      Instance    コールバック関数を所有する
 ***************************************************************/
template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
void GlobalData::request(Instance& instance, void (Instance::*callback)(const OBJ_TYPE&)) throw() {
	UpLock uplock(mutex_);
	WriteLock writeLock(uplock);

	globaldata::placeholder<modeID, objectID, Instance>(instance, callback);
}


template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
void GlobalData::request(const RequestData& requestData) throw() {
	UpLock uplock(mutex_);
	WriteLock writeLock(uplock);

	globaldata::placeholder<modeID, objectID, RequestData, pm_mode::NullType>::placeholder(requestData);
}
template<GlobalDataMember modeID, weUint objectID, typename RequestData, typename Instance>
void GlobalData::request(const RequestData& requestData, Instance& instance, void (Instance::*callback)(const OBJ_TYPE&)) throw() {
	UpLock uplock(mutex_);
	WriteLock writeLock(uplock);

	globaldata::placeholder<modeID, objectID, RequestData, Instance>(requestData, instance, callback);
}


/********************************************************************
 * @brief 自分自身で使うためのゲッタ
 * @note    const でない参照を返す。これを外部に公開するとスレッドアンセーフになるので。
 * @param[in]   オーバーロード用。意味は無い。
 * @tparam      modeID      モード ID
 *******************************************************************/
template<GlobalDataMember modeID>
typename pm_mode::task::CulcResultType<GlobalDataTypeList, modeID>::Result&
	GlobalData::get(pm_mode::IntType<modeID>) throw(pm_mode::task::UnReadyLoadData)
{
	if (hasData<modeID>() == false) {
		throw pm_mode::task::UnReadyLoadData(ExceptionMessage("The object has not been made yet!!!"));
	}

	ReadLock lock(mutex_);
	return pm_mode::task::Field<modeID>(this_->list_).get();
}


/// 特殊化のinclude


#if defined (OBJ_NAME)
#undef OBJ_NAME
#endif
#if defined (OBJ_TYPE)
#undef OBJ_TYPE
#endif

#endif    // PM_MODE_GLOBALDATA_HPP_INCLUDED
#endif    // #if (PM_MODE_ALLMENU_OFF != 1)
