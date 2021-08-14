
//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------
#include "weoJsonParser.h"
#include "weoJsonIODeclaration.h"
#include "boost/foreach.hpp"
#include "Personal/RangeManipulator.hpp"
#include "weoLeagueGlobalData.h"


void weoGlobalDataSave(::pm_mode::json::object& obj, int value) throw() {
	pm_mode::json::value temp;

	JSON_INSERTER("int", value);
}

void weoGlobalDataLoad(const ::pm_mode::json::object& obj, int& value) throw() {
	value = static_cast<int32_t>(obj.find("int").get<weDouble>());
}

void weoGlobalDataSave(::pm_mode::json::object& obj, const UserInfo& value) throw() {
	pm_mode::json::value temp;

	JSON_INSERTER("integer_", value.integer_);
	JSON_INSERTER("name_", value.name_);
}

void weoGlobalDataLoad(const ::pm_mode::json::object& obj, UserInfo& value) throw() {
	value.integer_ = static_cast<int32_t>(obj.find("integer_").get<weDouble>());
	value.name_ = obj.find("name_").get<std::string>();
}



