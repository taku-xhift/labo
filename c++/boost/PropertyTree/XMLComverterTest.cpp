


#include "mtm_player_management.h"
#include "boost/property_tree/json_parser.hpp"


int main() {
	XML_MTMPLAYERMANAGEMENT data;
	XML_ENTRY_INFO entryInfo;
	entryInfo.player_id_ = 40;
	entryInfo.name_ = "name";
	entryInfo.uni_num_ = 55;
	entryInfo.value_ = 40000;

	XML_SAVE_INFO saveInfo;
	saveInfo.name_ = "save name";
	saveInfo.player_id_ = 204;
	saveInfo.fee_ = 40;

	data.xml_input_.xml_entry_info_.push_back(entryInfo);
	data.xml_input_.xml_save_info_.push_back(saveInfo);
	data.xml_input_.xml_save_info_.push_back(saveInfo);

	boost::property_tree::ptree tree;
	data.save(tree);

	write_json("D:/PersonalTool/xyzzy/laboratory/c++/boost/PropertyTree/data_out.json", tree);

	XML_MTMPLAYERMANAGEMENT data2;
	//data2.xml_input_.xml_entry_info_.resize(1);
	data2.load(tree);

}

