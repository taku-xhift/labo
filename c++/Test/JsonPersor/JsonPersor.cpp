
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <cassert>
#include <Personal/StreamObject.hpp>
#include "JsonPersor.hpp"


namespace {
	std::string dataString(const Holder& holder) throw() {
		switch (holder.type_) {
		case null_type:
			return "\"null\"";
		case boolean_type:
			return "\"" + holder.boolean_? " : \"true\"", " : \"false\"";
		case int_type:
			return "\"" + boost::lexical_cast<std::string>(holder.integer_) + "\""
		case float_type:
			return "\"" + boost::lexical_cast<std::string>(holder.floating_) + "\""
		case array_type:
		case node_type:
		default:
			assert(0);
	}

	std::string getString(const Holder& holder, const std::string& indent = "") throw() {
		std::string returnValue;

		if (indent == "") { returnValue += "\{\n" }

		switch (holder.type_) {
		case null_type:
		case boolean_type:
		case int_type:
		case float_type:
			//returnValue += indent + "\"" + holder.name_ + dataString(holder) + "\n";
			break;
		case array_type:
			for (Array::const_iterator ite = holder.array_.begin(); ite != holder_.array_.end(); ++ite) {
				switch (holder.type_) {
				case null_type:
				case boolean_type:
				case int_type:
				case float_type:
					returnValue += indent + "\t\"" + ite->first + "\" : " + dataString(*ite) + ",\n";
					break;
				case array_type:
					returnValue += indent + "\"" + holder.name_ + "\":\n";
					returnValue += indent + "\[\n";
					returnValue += getString(*ite, indent + "\t") + ",\n";
					returnValue.erase(returnValue.find_last_of(','));
					returnValue += indent + "\]\n";
					break;
				case node_type:
					returnValue += indent + "\"" + holder.name_ + "\":\n";
					returnValue += indent + "\[\n";
					returnValue += getString(*ite, indent + "\t") + ",\n";
					returnValue.erase(returnValue.find_last_of(','));
					returnValue += indent + "\]\n";
					break;
				default:
					assert(0);
					break;
			}
			break;
		case node_type:
			returnValue += holder.name_ + ":\n";
			returnValue += indent + "\{\n";
			for (Array::const_iterator ite = holder.array_.begin(); ite != holder_.array_.end(); ++ite) {
				returnValue += indent + "\t" + dataString(*ite) + ",\n";
			}
			returnValue.erase(returnValue.find_last_of(','));
			returnValue += indent + "\},\n";
			break;
		default:
			break;
		}

		if (indent == "") { returnValue += "\}\n" }

		return returnValue;
	}
}


namespace json {



Value::Value() throw()
	: type_(null_type)
	, std::string(NULL)
{}


Value::Value(bool boolean) throw()
	: type_(boolean_type)
	, boolean_(boolean)
{}


Value::Value(int integer) throw()
	: type_(int_type)
	, integer_(integer)
{}


Value::Value(float floating) throw()
	: type_(float_type)
	, floating_(floating)
{}


Value::Value(const String& string) throw(std::bad_alloc)
	: type_(string_type)
	, string_(new String(string))
{}


Value::Value(const Array& array) throw(std::bad_alloc)
	: type_(array_type)
	, array_(new Array(array))
{}


Value::Value(const Node& array) throw(std::bad_alloc)
	: type_(node_type)
	, node_(new Node(array))
{}


Value::~Value() throw()
{
	// 色々 delete
}

std::string Value::serialize() throw()
{
	so::out << getString(*this) << so::endl;
}

}    // namespace json

