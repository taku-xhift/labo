
#ifndef PM_MODE_MTM_PLAYER_MANAGEMENT_H_INCLUDED
#define PM_MODE_MTM_PLAYER_MANAGEMENT_H_INCLUDED


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
//#include "weCommonHeader.h"
//#include "weoFlowException.h"
#include <boost/property_tree/ptree_fwd.hpp>


//namespace pm_mode {
//
//namespace mtm_player_management {

const char* const XMLCODE_MTMPLAYERMANAGEMENT                                            = "MtmPlayerManagement";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT                                      = "MtmPlayerManagement/input";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_CHANGE                               = "MtmPlayerManagement/input/change";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_CURRENT_FUND                         = "MtmPlayerManagement/input/current_fund";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ADD_AGREEMENT_MATCHNUM               = "MtmPlayerManagement/input/add_agreement_matchnum";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT                               = "MtmPlayerManagement/input/result";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_SUCCEED                       = "MtmPlayerManagement/input/result/succeed";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CURRENT_FUND                  = "MtmPlayerManagement/input/result/current_fund";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_NEXT_ADD_AGREEMENT_MATCHNUM   = "MtmPlayerManagement/input/result/next_add_agreement_matchnum";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO              = "MtmPlayerManagement/input/result/calc_result_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_PLAYER_ID    = "MtmPlayerManagement/input/result/calc_result_info/player_id";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_NAME         = "MtmPlayerManagement/input/result/calc_result_info/name";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_UNI_NUM      = "MtmPlayerManagement/input/result/calc_result_info/uni_num";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_VALUE        = "MtmPlayerManagement/input/result/calc_result_info/value";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_AGREEMENT    = "MtmPlayerManagement/input/result/calc_result_info/agreement";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_TIRED        = "MtmPlayerManagement/input/result/calc_result_info/tired";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_DP           = "MtmPlayerManagement/input/result/calc_result_info/dp";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_LEVEL        = "MtmPlayerManagement/input/result/calc_result_info/level";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_RESULT_CALC_RESULT_INFO_FEE          = "MtmPlayerManagement/input/result/calc_result_info/fee";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO                           = "entry_info";			//MtmPlayerManagement/input [overlap]";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_PLAYER_ID                 = "player_id";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_NAME                      = "name";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_UNI_NUM                   = "uni_num";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_VALUE                     = "value";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_AGREEMENT                 = "agreement";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_TIRED                     = "tired";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_DP                        = "dp";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_LEVEL                     = "level";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_ENTRY_INFO_FEE                       = "fee";			//MtmPlayerManagement/input/entry_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO                            = "save_info";			//MtmPlayerManagement/input [overlap]";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_PLAYER_ID                  = "player_id";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_NAME                       = "name";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_UNI_NUM                    = "uni_num";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_VALUE                      = "value";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_AGREEMENT                  = "agreement";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_TIRED                      = "tired";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_DP                         = "dp";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_LEVEL                      = "level";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_INPUT_SAVE_INFO_FEE                        = "fee";			//MtmPlayerManagement/input/save_info";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_OUTPUT                                     = "MtmPlayerManagement/output";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_OUTPUT_CHANGE                              = "MtmPlayerManagement/output/change";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_OUTPUT_SELECTED_PLAYER_ID                  = "MtmPlayerManagement/output/selected_player_id";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_OUTPUT_SEL_UNI_NUM                         = "MtmPlayerManagement/output/sel_uni_num";
const char* const XMLCODE_MTMPLAYERMANAGEMENT_OUTPUT_SELECTED_ITEM_ID                    = "MtmPlayerManagement/output/selected_item_id";


// MtmPlayerManagement/output
struct XML_OUTPUT
{
	int                                change_;
	int                                selected_player_id_;
	int                                sel_uni_num_;
	int                                selected_item_id_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_OUTPUT() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};

// MtmPlayerManagement/input/save_info
struct XML_SAVE_INFO
{
	int                                player_id_;
	std::string                          name_;
	int                                uni_num_;
	int                                value_;
	int                                agreement_;
	int                                tired_;
	int                                dp_;
	int                                level_;
	int                                fee_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_SAVE_INFO() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};

// MtmPlayerManagement/input/entry_info
struct XML_ENTRY_INFO
{
	int                                player_id_;
	std::string                          name_;
	int                                uni_num_;
	int                                value_;
	int                                agreement_;
	int                                tired_;
	int                                dp_;
	int                                level_;
	int                                fee_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_ENTRY_INFO() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};

// MtmPlayerManagement/input/result/calc_result_info
struct XML_CALC_RESULT_INFO
{
	int                                player_id_;
	std::string                          name_;
	int                                uni_num_;
	int                                value_;
	int                                agreement_;
	int                                tired_;
	int                                dp_;
	int                                level_;
	int                                fee_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_CALC_RESULT_INFO() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};

// MtmPlayerManagement/input/result
struct XML_RESULT
{
	XML_CALC_RESULT_INFO                 xml_calc_result_info_;
	int                                succeed_;
	int                                current_fund_;
	int                                next_add_agreement_matchnum_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_RESULT() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};

// MtmPlayerManagement/input
struct XML_INPUT
{
	XML_RESULT                           xml_result_;
	std::vector<XML_ENTRY_INFO>          xml_entry_info_;
	std::vector<XML_SAVE_INFO>           xml_save_info_;
	int                                change_;
	int                                current_fund_;
	int                                add_agreement_matchnum_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_INPUT() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};

// MtmPlayerManagement
struct XML_MTMPLAYERMANAGEMENT
{
	XML_INPUT                            xml_input_;
	XML_OUTPUT                           xml_output_;

	void*                                parentNode_;	//parent node
	void*                                thisNode_;	//self node

	XML_MTMPLAYERMANAGEMENT() throw();

	//! Json 解析
	void save(boost::property_tree::ptree& tree, std::string parentNode = "") throw();
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw(std::bad_alloc);
};


//}    // namespace mtm_player_management
//
//}    // namespace pm_mode

#endif	//PM_MODE_MTM_PLAYER_MANAGEMENT_H_INCLUDED
