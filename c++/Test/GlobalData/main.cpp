

#pragma warning(disable: 4290)

#include <iostream>
#include "Personal/StreamObject.hpp"
#include "weoGlobalData.h"
#include "weoAbstractCallBackBase.h"



class CallbackObject
	: public AbstractCallBackBase<UserInfo>
{
public:

	const UserInfo& get() const throw() {
		return this->info_;
	}

	void callBackFunction(const UserInfo& info) throw() {
		this->info_ = info;
	}

private:
	UserInfo info_;
};

class Printer
	: public AbstractCallBackBase<UserInfo>
{
public:

	void callBackFunction(const UserInfo& userInfo) throw() {
		std::cout << __FUNCTION__ << std::endl;
		std::cout << userInfo.name_ << std::endl;
		std::cout << userInfo.integer_ << std::endl;
	}
};



int main() {
try {
	CallbackObject object;

	// Mode Side
	{
		std::cerr << "Mode Side\n";

		// メモリ確保
		GlobalData::create();
		GlobalData::create<GLOBALMEMBER_LEAGUE>();

		// モード毎のグローバルデータの取得法
		//const LeagueGlobalData& league = GlobalData::get<GLOBALMEMBER_LEAGUE>();

		// enum で定義された ID でアクセスするモードとオブジェクトを決めて
		//      引数にデータをセットする
		//GlobalData::set<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>(3);
		GlobalData::set<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>(UserInfo(100, "name"));

		GlobalData::setCallBack<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO, CallbackObject>(object, &CallbackObject::callBackFunction);
	}

	// NetWork Side
	{
		std::cerr << "\nNetWork Side\n";

		UserInfo info;
		info.name_ = "test";
		GlobalData::setFromServer<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>(info);
	}

	// コールバックでセットされたものが正しいか検証
	{
		std::cerr << "\nコールバックでセットされたものが正しいか検証\n";

		std::cout << "userInfo.integer_ = " << object.get().integer_    << std::endl;
		std::cout << "userInfo.name_ = "    << object.get().name_       << std::endl;
	}

	// 再度登録した際にすぐにデータがセットされたか確認
	{
		std::cerr << "\n再度登録した際にすぐにデータがセットされたか確認\n";

		CallbackObject subObject;
		GlobalData::setCallBack<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>(subObject, &CallbackObject::callBackFunction);
	}

	// 普通に get 出来るかテスト
	{
		std::cerr << "\n普通に get 出来るかテスト\n";

		//std::cerr << "GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>() => " << GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>() << std::endl;;
		std::cerr << "GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_DATA>().integer_ => " << GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>().integer_ << std::endl;;
		std::cerr << "GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_DATA>().name_ => " << GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>().name_ << std::endl;;
	}

	// ready でデータを先に準備させて取得できるか確認
	{
		std::cerr << "\nready でデータを先に準備させて取得できるか確認\n";

		GlobalData::ready<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>();
		if (GlobalData::hasData<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>() == true) {
			std::cerr << "Get by globalData : " << GlobalData::get<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>() << std::endl;
		} else {
			WE_ASSERT(0);
		}
	}

	// ID でその他関数を呼び出す
	// 呼び出せる関数の大本は class DataHolder で
	// class LeagueGlobalData はそれをラップしたものになる
	GlobalData::upload<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>();
	//GlobalData::upload<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_MYTEAM>();
	GlobalData::release<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_ID>();

	std::cerr << "request" << std::endl;
	//pm_mode::task::CallBackFunctor<Printer, UserInfo> callBackFunctor(new Printer(), &Printer::callBackFunction);
	//pm_mode::task::Requester<int, pm_mode::task::CallBackFunctor<Printer, UserInfo> > requestor(3, callBackFunctor);

	GlobalData::release<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>();
	int integer = 3;
	Printer printer;
	GlobalData::request<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>(integer, printer, &Printer::callBackFunction);
	GlobalData::setFromServer<GLOBALMEMBER_LEAGUE, LEAGUEMEMBER_USER_INFO>(UserInfo());

} catch (pm_mode::task::UnReadyLoadData& e) {
	so::out << e.getAllInfo() << so::endl;
} catch (pm_mode::task::MemoryAllocateException& e) {
	so::out << e.getAllInfo() << so::endl;
} catch (pm_mode::task::FlowLogicException& e) {
	so::out << e.getAllInfo() << so::endl;
} catch (...) {
	so::out << "Catch unknown exception!!!" << so::endl;
}


	std::cerr << "\nEnd All Fase\n" << std::endl;
}
