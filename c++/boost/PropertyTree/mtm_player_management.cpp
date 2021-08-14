
#include "mtm_player_management.h"
//#include "weAvsProp.h"
//#include "weDebug.h"
//#include "weoFlowDefine.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>


//namespace pm_mode {
//
//namespace mtm_player_management {


XML_MTMPLAYERMANAGEMENT::XML_MTMPLAYERMANAGEMENT() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
{
}


void XML_MTMPLAYERMANAGEMENT::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	this->xml_input_.save(tree, parentNode + "XML_MTMPLAYERMANAGEMENT.");
	this->xml_output_.save(tree, parentNode + "XML_MTMPLAYERMANAGEMENT.");
}

void XML_MTMPLAYERMANAGEMENT::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_MTMPLAYERMANAGEMENT.";
	this->xml_input_.load(tree, path);
	this->xml_output_.load(tree, path);
}

XML_INPUT::XML_INPUT() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
	, change_(0)
	, current_fund_(0)
	, add_agreement_matchnum_(0)
{
}


void XML_INPUT::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	this->xml_result_.save(tree, parentNode + "XML_INPUT.");
	{
		boost::property_tree::ptree subTree;
		BOOST_FOREACH(XML_ENTRY_INFO arg, this->xml_entry_info_) {
			boost::property_tree::ptree info;
			arg.save(info, "");
			subTree.push_back(std::make_pair("", info));
		}
		tree.add_child(parentNode + "XML_INPUT.xml_entry_info_", subTree);
	}
	{
		boost::property_tree::ptree subTree;
		BOOST_FOREACH(XML_SAVE_INFO arg, this->xml_save_info_) {
			boost::property_tree::ptree info;
			arg.save(info, "");
			subTree.push_back(std::make_pair("", info));
		}
		tree.add_child(parentNode + "XML_INPUT.xml_save_info_", subTree);
	}
	tree.put(parentNode + "XML_INPUT.change_", this->change_);
	tree.put(parentNode + "XML_INPUT.current_fund_", this->current_fund_);
	tree.put(parentNode + "XML_INPUT.add_agreement_matchnum_", this->add_agreement_matchnum_);
}

void XML_INPUT::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_INPUT.";
	this->xml_result_.load(tree, path);
	{
		int count = 0;
		unsigned int size = tree.get_child(path + "xml_entry_info_").size();
		if (this->xml_entry_info_.size() < size) { this->xml_entry_info_.resize(size); }
		BOOST_FOREACH(const boost::property_tree::ptree::value_type& child, tree.get_child(path + "xml_entry_info_")) {
			const boost::property_tree::ptree& info = child.second;
			this->xml_entry_info_.at(count).load(info);
			++count;
		}
	}
	{
		int count = 0;
		unsigned int size = tree.get_child(path + "xml_save_info_").size();
		if (this->xml_save_info_.size() < size) { this->xml_save_info_.resize(size); }
		BOOST_FOREACH(const boost::property_tree::ptree::value_type& child, tree.get_child(path + "xml_save_info_")) {
			const boost::property_tree::ptree& info = child.second;
			this->xml_save_info_.at(count).load(info);
			++count;
		}
	}
	this->change_ = tree.get<int>(path + "change_");
	this->current_fund_ = tree.get<int>(path + "current_fund_");
	this->add_agreement_matchnum_ = tree.get<int>(path + "add_agreement_matchnum_");
}

XML_RESULT::XML_RESULT() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
	, succeed_(0)
	, current_fund_(0)
	, next_add_agreement_matchnum_(0)
{
}


void XML_RESULT::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	this->xml_calc_result_info_.save(tree, parentNode + "XML_RESULT.");
	tree.put(parentNode + "XML_RESULT.succeed_", this->succeed_);
	tree.put(parentNode + "XML_RESULT.current_fund_", this->current_fund_);
	tree.put(parentNode + "XML_RESULT.next_add_agreement_matchnum_", this->next_add_agreement_matchnum_);
}

void XML_RESULT::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_RESULT.";
	this->xml_calc_result_info_.load(tree, path);
	this->succeed_ = tree.get<int>(path + "succeed_");
	this->current_fund_ = tree.get<int>(path + "current_fund_");
	this->next_add_agreement_matchnum_ = tree.get<int>(path + "next_add_agreement_matchnum_");
}

XML_CALC_RESULT_INFO::XML_CALC_RESULT_INFO() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
	, player_id_(0)
	, uni_num_(0)
	, value_(0)
	, agreement_(0)
	, tired_(0)
	, dp_(0)
	, level_(0)
	, fee_(0)
{
}


void XML_CALC_RESULT_INFO::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	tree.put(parentNode + "XML_CALC_RESULT_INFO.player_id_", this->player_id_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.name_", this->name_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.uni_num_", this->uni_num_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.value_", this->value_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.agreement_", this->agreement_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.tired_", this->tired_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.dp_", this->dp_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.level_", this->level_);
	tree.put(parentNode + "XML_CALC_RESULT_INFO.fee_", this->fee_);
}

void XML_CALC_RESULT_INFO::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_CALC_RESULT_INFO.";
	this->player_id_ = tree.get<int>(path + "player_id_");
	this->name_ = tree.get<std::string>(path + "name_");
	this->uni_num_ = tree.get<int>(path + "uni_num_");
	this->value_ = tree.get<int>(path + "value_");
	this->agreement_ = tree.get<int>(path + "agreement_");
	this->tired_ = tree.get<int>(path + "tired_");
	this->dp_ = tree.get<int>(path + "dp_");
	this->level_ = tree.get<int>(path + "level_");
	this->fee_ = tree.get<int>(path + "fee_");
}

XML_ENTRY_INFO::XML_ENTRY_INFO() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
	, player_id_(0)
	, uni_num_(0)
	, value_(0)
	, agreement_(0)
	, tired_(0)
	, dp_(0)
	, level_(0)
	, fee_(0)
{
}


void XML_ENTRY_INFO::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	tree.put(parentNode + "XML_ENTRY_INFO.player_id_", this->player_id_);
	tree.put(parentNode + "XML_ENTRY_INFO.name_", this->name_);
	tree.put(parentNode + "XML_ENTRY_INFO.uni_num_", this->uni_num_);
	tree.put(parentNode + "XML_ENTRY_INFO.value_", this->value_);
	tree.put(parentNode + "XML_ENTRY_INFO.agreement_", this->agreement_);
	tree.put(parentNode + "XML_ENTRY_INFO.tired_", this->tired_);
	tree.put(parentNode + "XML_ENTRY_INFO.dp_", this->dp_);
	tree.put(parentNode + "XML_ENTRY_INFO.level_", this->level_);
	tree.put(parentNode + "XML_ENTRY_INFO.fee_", this->fee_);
}

void XML_ENTRY_INFO::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_ENTRY_INFO.";
	this->player_id_ = tree.get<int>(path + "player_id_");
	this->name_ = tree.get<std::string>(path + "name_");
	this->uni_num_ = tree.get<int>(path + "uni_num_");
	this->value_ = tree.get<int>(path + "value_");
	this->agreement_ = tree.get<int>(path + "agreement_");
	this->tired_ = tree.get<int>(path + "tired_");
	this->dp_ = tree.get<int>(path + "dp_");
	this->level_ = tree.get<int>(path + "level_");
	this->fee_ = tree.get<int>(path + "fee_");
}

XML_SAVE_INFO::XML_SAVE_INFO() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
	, player_id_(0)
	, uni_num_(0)
	, value_(0)
	, agreement_(0)
	, tired_(0)
	, dp_(0)
	, level_(0)
	, fee_(0)
{
}


void XML_SAVE_INFO::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	tree.put(parentNode + "XML_SAVE_INFO.player_id_", this->player_id_);
	tree.put(parentNode + "XML_SAVE_INFO.name_", this->name_);
	tree.put(parentNode + "XML_SAVE_INFO.uni_num_", this->uni_num_);
	tree.put(parentNode + "XML_SAVE_INFO.value_", this->value_);
	tree.put(parentNode + "XML_SAVE_INFO.agreement_", this->agreement_);
	tree.put(parentNode + "XML_SAVE_INFO.tired_", this->tired_);
	tree.put(parentNode + "XML_SAVE_INFO.dp_", this->dp_);
	tree.put(parentNode + "XML_SAVE_INFO.level_", this->level_);
	tree.put(parentNode + "XML_SAVE_INFO.fee_", this->fee_);
}

void XML_SAVE_INFO::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_SAVE_INFO.";
	this->player_id_ = tree.get<int>(path + "player_id_");
	this->name_ = tree.get<std::string>(path + "name_");
	this->uni_num_ = tree.get<int>(path + "uni_num_");
	this->value_ = tree.get<int>(path + "value_");
	this->agreement_ = tree.get<int>(path + "agreement_");
	this->tired_ = tree.get<int>(path + "tired_");
	this->dp_ = tree.get<int>(path + "dp_");
	this->level_ = tree.get<int>(path + "level_");
	this->fee_ = tree.get<int>(path + "fee_");
}

XML_OUTPUT::XML_OUTPUT() throw()
	: parentNode_(NULL)
	, thisNode_(NULL)
	, change_(0)
	, selected_player_id_(0)
	, sel_uni_num_(0)
	, selected_item_id_(0)
{
}


void XML_OUTPUT::save(boost::property_tree::ptree& tree, std::string parentNode) throw() {
	tree.put(parentNode + "XML_OUTPUT.change_", this->change_);
	tree.put(parentNode + "XML_OUTPUT.selected_player_id_", this->selected_player_id_);
	tree.put(parentNode + "XML_OUTPUT.sel_uni_num_", this->sel_uni_num_);
	tree.put(parentNode + "XML_OUTPUT.selected_item_id_", this->selected_item_id_);
}

void XML_OUTPUT::load(const boost::property_tree::ptree& tree, std::string parentNode) throw(std::bad_alloc) {
	std::string path = parentNode + "XML_OUTPUT.";
	this->change_ = tree.get<int>(path + "change_");
	this->selected_player_id_ = tree.get<int>(path + "selected_player_id_");
	this->sel_uni_num_ = tree.get<int>(path + "sel_uni_num_");
	this->selected_item_id_ = tree.get<int>(path + "selected_item_id_");
}


//}    // namespace mtm_player_management
//
//}    // namespace pm_mode
