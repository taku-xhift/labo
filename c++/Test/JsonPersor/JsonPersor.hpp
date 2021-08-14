
#ifndef JSON_JSONPARSER_HPP_INCLUDED
#define JSON_JSONPARSER_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------



#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>

namespace json {


enum Type {
	null_type,
	boolean_type,
	int_type,
	float_type,
	string_type,
	array_type,
	node_type,
};

typedef std::string String;
typedef std::vector<Holder> Array;
typedef std::map<std::string, Holder> Object;



struct Value {
	Type        type_;
	//std::string name_;
	union {
		bool    boolean_;
		int     integer_;
		float   floating_;
		String* string_;
		Array*  array_;
		Object*   node_;
	};

	Holder() throw() : type_(null_type), std::string(NULL) {}
	explicit Value(bool boolean) throw() : type_(boolean_type), boolean_(boolean) {}
	explicit Value(int integer) throw() : type_(int_type), integer_(integer) {}
	explicit Value(float floating) throw() : type_(float_type), floating_(floating) {}
	explicit Value(const String& string) throw(std::bad_alloc) : type_(string_type), string_(new String(string)) {}
	explicit Value(const Array& array) throw(std::bad_alloc) : type_(array_type), array_(new Array(array)) {}
	explicit Value(const Object& array) throw(std::bad_alloc) : type_(node_type), node_(new Object(array)) {}

	~Value() throw() { /*色々 delete */ }

	std::string serialize() throw();
};


}



#endif

