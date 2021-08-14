/* Copyright 2009 Cybozu Labs, Inc.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY CYBOZU LABS, INC. ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL CYBOZU LABS, INC. OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Cybozu Labs, Inc.
 *
 */
#ifndef PM_MODE_JSONPARSER_HPP_INCLUDED
#define PM_MODE_JSONPARSER_HPP_INCLUDED



typedef int weInt;
typedef unsigned int weUint;
typedef double weDouble;
typedef const char* weString;



#include "weoJsonParserFwd.h"
//#include "weoJsonIODeclaration.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
//#include <map>
#include <string>
#include <vector>
#include <algorithm>
//#include "weDebug.h"
//#include "weCommonType.h"
//#include "weoFlowException.h"
//#include "weoExceptionMessageCreator.h"


#ifdef _MSC_VER
    #define SNPRINTF _snprintf_s
    #pragma warning(push)
    #pragma warning(disable : 4244) // conversion from int to char
#else
    #define SNPRINTF snprintf
#endif


struct FindByName {
	FindByName(const std::string& name) throw() : name_(name) {}

	template<typename Value>
	bool operator()(const Value& value) const throw() {
		return value.name_ == this->name_;
	}

private:
	const std::string& name_;
};

#define JSON_INSERTER(name, data)\
	obj[name] = temp.reset(data);

#define JSON_STRUCT_INSERTER(structure, name)\
	weoGlobalDataSave(object, structure.name);\
	JSON_INSERTER(#name, object);\
	object.clear();

#define JSON_PTR_STRUCT_INSERTER(structure, name)\
	if (structure.name == NULL) { WE_ASSERT(0, ""); }\
	weoGlobalDataSave(object, *structure.name);\
	JSON_INSERTER(#name, object);\
	object.clear();

#define JSON_DATA_SETTER(structure, member, type)\
	try {\
		temp = &obj.find(#member);\
		structure.member = temp->get<type>();\
	} catch (pm_mode::task::FlowUnFoundException& e) {\
		e << ExceptionMessage("Catch and through");\
		WE_PRINTF("%s\n", e.getAllInfo());\
	}

#define JSON_STRING_SETTER(structure, member, size)\
	try {\
		temp = &obj.find(#member);\
		memmove(structure.member, temp->get<std::string>().c_str(), size-1);\
		structure.member[size-1] = '\0';\
	} catch (pm_mode::task::FlowUnFoundException& e) {\
		e << ExceptionMessage("Catch and through");\
		WE_PRINTF("%s\n", e.getAllInfo());\
	}

#define JSON_ARRAY_DATA_SETTER(structure, member, size, type)\
	try {\
		temp = &obj.find(#member);\
		const pm_mode::json::array& array = temp->get<pm_mode::json::array>();\
		for (int i = 0; i < size; ++i) {\
			structure.member[i] = array.at(i).get<type>();\
		}\
	} catch (pm_mode::task::FlowUnFoundException& e) {\
		e << ExceptionMessage("Catch and through");\
		WE_PRINTF("%s\n", e.getAllInfo());\
	}

#define JSON_DATA_LOADER(structure, member)\
	try {\
		temp = &obj.find(#member);\
		weoGlobalDataLoad(temp->get<pm_mode::json::object>(), structure.member);\
	} catch (pm_mode::task::FlowUnFoundException& e) {\
		e << ExceptionMessage("Catch and through");\
		WE_PRINTF("%s\n", e.getAllInfo());\
	}

#define JSON_PTR_DATA_LOADER(structure, member)\
	try {\
		if (structure.member == NULL) { WE_ASSERT(0, ""); }\
		temp = &obj.find(#member);\
		weoGlobalDataLoad(temp->get<pm_mode::json::object>(), *structure.member);\
	} catch (pm_mode::task::FlowUnFoundException& e) {\
		e << ExceptionMessage("Catch and through");\
		WE_PRINTF("%s\n", e.getAllInfo());\
	}

#define JSON_ARRAY_DATA_LOADER(structure, member, size)\
	try {\
		temp = &obj.find(#member);\
		for (int i = 0; i < size; ++i) {\
			weoGlobalDataLoad(temp->get<pm_mode::json::object>(), structure.member[i]);\
		}\
	} catch (pm_mode::task::FlowUnFoundException& e) {\
		e << ExceptionMessage("Catch and through");\
		WE_PRINTF("%s\n", e.getAllInfo());\
	}





namespace pm_mode {
namespace json {

enum Type {
	null_type,
	boolean_type,
	integer_type,
	naturalNumber_type,
	number_type,
	string_type,
	array_type,
	object_type
};

struct null {};

class value
{
public:
	value();
	value(Type type);
	explicit value(bool b);
	explicit value(weInt i);
	explicit value(weUint n);
	explicit value(weDouble n);
	explicit value(const std::string& s);
	explicit value(const array& a);
	explicit value(const object& o);
	~value();
	value(const value& x);
	value& operator=(const value& x);
	template <typename T> bool is() const;
	template <typename T> const T& get() const;
	template <typename T> T& get();
	operator bool() const;
	const value& get(size_t idx) const;
	const value& get(const std::string& key) const;
	std::string to_str() const;
	template <typename Iter> void serialize(Iter os) const;
	std::string serialize() const;
	const value& reset(bool b) { this->type_ = boolean_type; this->boolean_ = b; return *this; }
	const value& reset(weInt i) { this->type_ = integer_type; this->integer_ = i; return *this; }
	const value& reset(weUint n) { this->type_ = naturalNumber_type; this->naturalNumber_ = n; return *this; }
	const value& reset(weDouble d) { this->type_ = number_type; this->number_ = d; return *this; }
	const value& reset(weString s) { this->type_ = string_type; this->string_ = new std::string(s); return *this; }
	const value& reset(const std::string& s) { this->type_ = string_type; this->string_ = new std::string(s); return *this; }
	const value& reset(const array& a);// { this->type_ = array_type; this->array_ = new array(a); return *this; }
	const value& reset(const object& o);// { this->type_ = object_type; this->object_ = new object(o); return *this; }

protected:
	Type type_;
	union {
		bool boolean_;
		weInt integer_;
		weUint naturalNumber_;
		weDouble number_;
		std::string* string_;
		array* array_;
		object* object_;
	};
};

struct array : std::vector<value>{};
//struct object : std::map<std::string, value>{};
struct DataSet {
	std::string name_;
	value       value_;

	DataSet(const std::string& name, const value& data) throw()
		: name_(name)
		, value_(data) {}
	DataSet(const std::string& name) throw() : name_(name) {}
	DataSet() throw() {}

	bool operator==(const DataSet& other) const throw() {
		return this->name_ == other.name_
			&& this->value_ == other.value_;
	}
	bool operator!=(const DataSet& other) const throw() {
		return (*this == other);
	}
};
struct object {
	std::vector<DataSet> value_;

	value& find(const std::string& key) throw() {
		std::vector<DataSet>::iterator ite = std::find_if(this->value_.begin(), this->value_.end(), FindByName(key));
		if (ite != this->value_.end()) {
			return ite->value_;
		}
	}
	const value& find(const std::string& key) const throw() {
		std::vector<DataSet>::const_iterator ite = std::find_if(this->value_.begin(), this->value_.end(), FindByName(key));
		if (ite != this->value_.end()) {
			return ite->value_;
		}
	}

	void insert(const std::string& key, const value& data) {
		this->value_.push_back(DataSet(key, data));
	}

	void clear() throw() { this->value_.clear(); }

	value& operator[](const std::string& key) throw() {
		value* value = NULL;
		if (this->find(key, value) == true) {
			return *value;
		} else {
			this->value_.push_back(DataSet(key));
			return this->value_.back().value_;
		}
	}

	bool find(const std::string& key, value*& value) throw() {
		std::vector<DataSet>::iterator ite = std::find_if(this->value_.begin(), this->value_.end(), FindByName(key));
		if (ite != this->value_.end()) {
			value = &ite->value_;
			return true;
		} else {
			return false;
		}
	}

	bool operator==(const object& other) const throw() {
		return this->value_ == other.value_;
	}
	bool operator!=(const object& other) const throw() {
		return !(*this == other);
	}
};


inline value::value() : type_(null_type) {}

inline value::value(Type type) : type_(type) {
	switch (type) {
#define INIT(p, v) case p##type: p = v; break
		INIT(boolean_, false);
		INIT(integer_, 0);
		INIT(naturalNumber_, 0u);
		INIT(number_, 0.0);
		INIT(string_, new std::string());
		INIT(array_, new array());
		INIT(object_, new object());
#undef INIT
	default: break;
	}
}

inline value::value(bool b) : type_(boolean_type) {
	boolean_ = b;
}

inline value::value(weInt i) : type_(integer_type) {
	this->integer_ = i;
}

inline value::value(weUint n) : type_(naturalNumber_type) {
	this->naturalNumber_ = n;
}

inline value::value(weDouble n) : type_(number_type) {
	number_ = n;
}

inline value::value(const std::string& s) : type_(string_type) {
	string_ = new std::string(s);
}

inline value::value(const array& a) : type_(array_type) {
	array_ = new array(a);
}

inline value::value(const object& o) : type_(object_type) {
	object_ = new object(o);
}

inline value::~value() {
	switch (type_) {
#define DEINIT(p) case p##type: delete p; break
		DEINIT(string_);
		DEINIT(array_);
		DEINIT(object_);
#undef DEINIT
	default: break;
	}
}

inline value::value(const value& x) : type_(x.type_) {
	switch (type_) {
#define INIT(p, v) case p##type: p = v; break
		INIT(boolean_, x.boolean_);
		INIT(integer_, x.integer_);
		INIT(naturalNumber_, x.naturalNumber_);
		INIT(number_, x.number_);
		INIT(string_, new std::string(*x.string_));
		INIT(array_, new array(*x.array_));
		INIT(object_, new object(*x.object_));
#undef INIT
	default: break;
	}
}

inline value& value::operator=(const value& x) {
	if (this != &x) {
		this->~value();
		new (this) value(x);
	}
	return *this;
}

#define IS(ctype, jtype)			     \
	template <> inline bool value::is<ctype>() const { \
		return type_ == jtype##_type;		     \
	}
IS(null, null)
IS(bool, boolean)
IS(weInt, number)
IS(weUint, naturalNumber)
IS(weDouble, number)
IS(std::string, string)
IS(array, array)
IS(object, object)
#undef IS

#define GET(ctype, var)					      \
	template <> inline const ctype& value::get<ctype>() const { \
		return var;						      \
	}							      \
	template <> inline ctype& value::get<ctype>() {	      \
		return var;						      \
	}
GET(bool, boolean_)
GET(weInt, integer_)
GET(weUint, naturalNumber_)
GET(weDouble, number_)
GET(std::string, *string_)
GET(array, *array_)
GET(object, *object_)
#undef GET

inline value::operator bool() const {
	switch (type_) {
	case null_type:
		return false;
	case boolean_type:
		return boolean_;
	case integer_type:
		return this->integer_ != 0;
	case naturalNumber_type:
		return this->naturalNumber_ != 0u;
	case number_type:
		return number_ != 0;
	case string_type:
		return ! string_->empty();
	default:
		return true;
	}
}

inline const value& value::get(size_t idx) const {
	static value s_null;
	assert(is<array>());
	return idx < array_->size() ? (*array_)[idx] : s_null;
}

inline const value& value::get(const std::string& key) const {
	static value s_null;
	assert(is<object>());
	//object::const_iterator i = object_->find(key);
	std::vector<DataSet>::iterator i = std::find_if(this->object_->value_.begin(), this->object_->value_.end(), FindByName(key));
	return i != this->object_->value_.end() ? i->value_ : s_null;
}

inline std::string value::to_str() const {
	switch (type_) {
	case null_type:      return "null";
	case boolean_type:   return boolean_ ? "true" : "false";
	case integer_type:
	case naturalNumber_type: {
		char buf[256];
		SNPRINTF(buf, sizeof(buf), "%d", this->integer_);
		return buf;
	}
	case number_type:    {
		char buf[256];
		SNPRINTF(buf, sizeof(buf), "%f", number_);
		return buf;
	}
	case string_type:    return *string_;
	case array_type:     return "array";
	case object_type:    return "object";
	default:             assert(0);
#ifdef _MSC_VER
		__assume(0);
#endif
	}
}

template <typename Iter> void copy(const std::string& s, Iter oi) {
	std::copy(s.begin(), s.end(), oi);
}

template <typename Iter> void serialize_str(const std::string& s, Iter oi) {
	*oi++ = '"';
	for (std::string::const_iterator i = s.begin(); i != s.end(); ++i) {
		switch (*i) {
#define MAP(val, sym) case val: copy(sym, oi); break
			MAP('"', "\\\"");
			MAP('\\', "\\\\");
			MAP('/', "\\/");
			MAP('\b', "\\b");
			MAP('\f', "\\f");
			MAP('\n', "\\n");
			MAP('\r', "\\r");
			MAP('\t', "\\t");
#undef MAP
		default:
			if ((unsigned char)*i < 0x20 || *i == 0x7f) {
				char buf[7];
				SNPRINTF(buf, sizeof(buf), "\\u%04x", *i & 0xff);
				copy(buf, buf + 6, oi);
			} else {
				*oi++ = *i;
			}
			break;
		}
	}
	*oi++ = '"';
}

template <typename Iter> void value::serialize(Iter oi) const {
	static weInt depth = 0;

	switch (type_) {
	case string_type:
	//for (weInt i = 0; i < depth; ++i) { *oi++ = '\t'; }
		serialize_str(*string_, oi);
		break;
	case array_type: {
		*oi++ = '\n';
		for (weInt i = 0; i < depth; ++i) { *oi++ = '\t'; }
		*oi++ = '[';
		*oi++ = '\n';
		++depth;
		for (array::const_iterator i = array_->begin(); i != array_->end(); ++i) {
			if (i != array_->begin()) {
				*oi++ = ',';
				*oi++ = '\n';
			}
			for (weInt j = 0; j < depth; ++j) { *oi++ = '\t'; }
			i->serialize(oi);
		}
		--depth;
		*oi++ = '\n';
		for (weInt i = 0; i < depth; ++i) { *oi++ = '\t'; }
		*oi++ = ']';
		break;
	}
	case object_type: {
		*oi++ = '\n';
		for (weInt i = 0; i < depth; ++i) { *oi++ = '\t'; }
		*oi++ = '{';
		*oi++ = '\n';
		++depth;
		for (std::vector<DataSet>::iterator ite = this->object_->value_.begin(); ite != this->object_->value_.end(); ++ite)
		{
			if (ite != this->object_->value_.begin()) {
				*oi++ = ',';
				*oi++ = '\n';
			}
			for (weInt j = 0; j < depth; ++j) { *oi++ = '\t'; }
			serialize_str(ite->name_, oi);
			*oi++ = ':';
			ite->value_.serialize(oi);
		}
		--depth;
		*oi++ = '\n';
		for (weInt i = 0; i < depth; ++i) { *oi++ = '\t'; }
		*oi++ = '}';
		break;
	}
	default:
		//for (weInt i = 0; i < depth; ++i) { *oi++ = '\t'; }
		copy(to_str(), oi);
		break;
	}
}

inline std::string value::serialize() const {
	std::string s;
	serialize(std::back_inserter(s));
	return s;
}

inline const value& value::reset(const array& a) {
	this->type_ = array_type;
	this->array_ = new array();
	*this->array_ = a;
	return *this;
}
inline const value& value::reset(const object& o) {
	this->type_ = object_type;
	this->object_ = new object();
	*this->object_ = o;
	return *this;
}


template <typename Iter>
class input
{
public:
	input(const Iter& first, const Iter& last) : cur_(first), end_(last), last_ch_(-1), ungot_(false), line_(1) {}
	weInt getc() {
		if (ungot_) {
			ungot_ = false;
			return last_ch_;
		}
		if (cur_ == end_) {
			last_ch_ = -1;
			return -1;
		}
		if (last_ch_ == '\n') {
			line_++;
		}
		last_ch_ = *cur_++ & 0xff;
		return last_ch_;
	}
	void ungetc() {
		if (last_ch_ != -1) {
			assert(! ungot_);
			ungot_ = true;
		}
	}
	Iter cur() const { return cur_; }
	weInt line() const { return line_; }
	void skip_ws() {
		for (;;) {
			weInt ch = getc();
			if (! (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')) {
				ungetc();
				break;
			}
		}
	}
	bool expect(weInt expect) {
		skip_ws();
		if (getc() != expect) {
			ungetc();
			return false;
		}
		return true;
	}
	bool match(const std::string& pattern) {
		for (std::string::const_iterator pi(pattern.begin());
			 pi != pattern.end();
			 ++pi) {
			if (getc() != *pi) {
				ungetc();
				return false;
			}
		}
		return true;
	}
protected:
	Iter cur_, end_;
	weInt last_ch_;
	bool ungot_;
	weInt line_;
};

template<typename Iter> inline weInt _parse_quadhex(input<Iter> &in) {
	weInt uni_ch = 0, hex;
	for (weInt i = 0; i < 4; i++) {
		if ((hex = in.getc()) == -1) {
			return -1;
		}
		if ('0' <= hex && hex <= '9') {
			hex -= '0';
		} else if ('A' <= hex && hex <= 'F') {
			hex -= 'A' - 0xa;
		} else if ('a' <= hex && hex <= 'f') {
			hex -= 'a' - 0xa;
		} else {
			in.ungetc();
			return -1;
		}
		uni_ch = uni_ch * 16 + hex;
	}
	return uni_ch;
}

template<typename Iter> inline bool _parse_codepoint(std::string& out, input<Iter>& in) {
	weInt uni_ch;
	if ((uni_ch = _parse_quadhex(in)) == -1) {
		return false;
	}
	if (0xd800 <= uni_ch && uni_ch <= 0xdfff) {
		if (0xdc00 <= uni_ch) {
			// a second 16-bit of a surrogate pair appeared
			return false;
		}
		// first 16-bit of surrogate pair, get the next one
		if (in.getc() != '\\' || in.getc() != 'u') {
			in.ungetc();
			return false;
		}
		weInt second = _parse_quadhex(in);
		if (! (0xdc00 <= second && second <= 0xdfff)) {
			return false;
		}
		uni_ch = ((uni_ch - 0xd800) << 10) | ((second - 0xdc00) & 0x3ff);
		uni_ch += 0x10000;
	}
	if (uni_ch < 0x80) {
		out.push_back(uni_ch);
	} else {
		if (uni_ch < 0x800) {
			out.push_back(0xc0 | (uni_ch >> 6));
		} else {
			if (uni_ch < 0x10000) {
				out.push_back(0xe0 | (uni_ch >> 12));
			} else {
				out.push_back(0xf0 | (uni_ch >> 18));
				out.push_back(0x80 | ((uni_ch >> 12) & 0x3f));
			}
			out.push_back(0x80 | ((uni_ch >> 6) & 0x3f));
		}
		out.push_back(0x80 | (uni_ch & 0x3f));
	}
	return true;
}

template<typename Iter> inline bool _parse_string(value& out, input<Iter>& in) {
	// gcc 4.1 cannot compile if the below two lines are merged into one :-(
	out = value(string_type);
	std::string& s = out.get<std::string>();
	for (;;) {
		weInt ch = in.getc();
		if (ch < ' ') {
			in.ungetc();
			return false;
		} else if (ch == '"') {
			return true;
		} else if (ch == '\\') {
			if ((ch = in.getc()) == -1) {
				return false;
			}
			switch (ch) {
#define MAP(sym, val) case sym: s.push_back(val); break
				MAP('"', '\"');
				MAP('\\', '\\');
				MAP('/', '/');
				MAP('b', '\b');
				MAP('f', '\f');
				MAP('n', '\n');
				MAP('r', '\r');
				MAP('t', '\t');
#undef MAP
			case 'u':
				if (! _parse_codepoint(s, in)) {
					return false;
				}
				break;
			default:
				return false;
			}
		} else {
			s.push_back(ch);
		}
	}
}

template <typename Iter> inline bool _parse_array(value& out, input<Iter>& in) {
	out = value(array_type);
	array& a = out.get<array>();
	if (in.expect(']')) {
		return true;
	}
	do {
		a.push_back(value());
		if (! _parse(a.back(), in)) {
			return false;
		}
	} while (in.expect(','));
	return in.expect(']');
}

template <typename Iter> inline bool _parse_object(value& out, input<Iter>& in) {
	out = value(object_type);
	object& o = out.get<object>();
	if (in.expect('}')) {
		return true;
	}
	do {
		value key, val;
		if (in.expect('"')
			&& _parse_string(key, in)
			&& in.expect(':')
			&& _parse(val, in))
		{
			std::vector<DataSet>::iterator ite = std::find_if(o.value_.begin(), o.value_.end(), FindByName(key.to_str()));
			if (ite != o.value_.end()) {
				ite->value_ = val;
			} else {
				o.value_.push_back(DataSet(key.to_str(), val));
			}
		} else {
			return false;
		}
	} while (in.expect(','));
	return in.expect('}');
}

template <typename Iter> inline bool _parse_number(value& out, input<Iter>& in) {
	std::string num_str;
	for (;;) {
		weInt ch = in.getc();
		if (('0' <= ch && ch <= '9') || ch == '+' || ch == '-' || ch == '.'
			|| ch == 'e' || ch == 'E') {
			num_str.push_back(ch);
		} else {
			in.ungetc();
			break;
		}
	}
	char* endp;
	out = value(strtod(num_str.c_str(), &endp));
	return endp == num_str.c_str() + num_str.size();
}

template <typename Iter> inline bool _parse(value& out, input<Iter>& in) {
	in.skip_ws();
	weInt ch = in.getc();
	switch (ch) {
#define IS(ch, text, val) case ch: \
	if (in.match(text)) { \
		out = val; \
		return true; \
	} else { \
		return false; \
	}
		IS('n', "ull", value());
		IS('f', "alse", value(false));
		IS('t', "rue", value(true));
#undef IS
	case '"':
		return _parse_string(out, in);
	case '[':
		return _parse_array(out, in);
	case '{':
		return _parse_object(out, in);
	default:
		if (('0' <= ch && ch <= '9') || ch == '-') {
			in.ungetc();
			return _parse_number(out, in);
		}
		break;
	}
	in.ungetc();
	return false;
}

// obsolete, use the version below
template <typename Iter> inline std::string parse(value& out, Iter& pos, const Iter& last) {
	std::string err;
	pos = parse(out, pos, last, &err);
	return err;
}

template <typename Iter> inline Iter parse(value& out, const Iter& first, const Iter& last, std::string* err) {
	input<Iter> in(first, last);
	if (! _parse(out, in) && err != NULL) {
		char buf[64];
		SNPRINTF(buf, sizeof(buf), "syntax error at line %d near: ", in.line());
		*err = buf;
		for (;;) {
			weInt ch = in.getc();
			if (ch == -1 || ch == '\n') {
				break;
			} else if (ch >= ' ') {
				err->push_back(ch);
			}
		}
	}
	return in.cur();
}

inline std::string parse(value& out, std::istream& is) {
	std::string err;
	parse(out, std::istreambuf_iterator<char>(is.rdbuf()),
		  std::istreambuf_iterator<char>(), &err);
	return err;
}

template <typename T> struct last_error_t {
						  static std::string s;
					  };
template <typename T> std::string last_error_t<T>::s;

inline void set_last_error(const std::string& s) {
	last_error_t<bool>::s = s;
}

inline const std::string& get_last_error() {
	return last_error_t<bool>::s;
}

inline bool operator==(const value& x, const value& y) {
	if (x.is<null>())
		return y.is<null>();
#define PICOJSON_CMP(type)					\
	if (x.is<type>())						\
		return y.is<type>() && x.get<type>() == y.get<type>()
	PICOJSON_CMP(bool);
	PICOJSON_CMP(weInt);
	PICOJSON_CMP(weDouble);
	PICOJSON_CMP(std::string);
	PICOJSON_CMP(array);
	PICOJSON_CMP(object);
#undef PICOJSON_CMP
	assert(0);
#ifdef _MSC_VER
	__assume(0);
#else
	return false;
#endif
}

inline bool operator!=(const value& x, const value& y) {
	return ! (x == y);
}

/////////////////////////////////////////////////////////////////

inline bool readJsonFile(value& data, const char* const fileName) throw() {
	std::string file;

	// 単なるファイルリード
	{
		std::ifstream ifs;
		std::string temp;
		ifs.open(fileName, std::ios::in);
		if (ifs) {
			while (ifs.eof() == false) {
				ifs >> temp;
				file += temp;
			}
		}
		ifs.close();
	}

	std::string::const_iterator begin = file.begin();
	std::string::const_iterator end = file.end();
	std::string error = parse(data, begin, end);
	//std::ifstream ifs = std::ifstream(fileName, std::ios::in);
	//ifs.ignore(1);
	//std::string error = parse(data, ifs);
	return error == "";
}

}   // namespace json
}   // namespace pm_mode



inline std::istream& operator>>(std::istream& is, pm_mode::json::value& x)
{
	pm_mode::json::set_last_error(std::string());
	std::string err = pm_mode::json::parse(x, is);
	if (! err.empty()) {
		pm_mode::json::set_last_error(err);
		is.setstate(std::ios::failbit);
	}
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const pm_mode::json::value& x)
{
	x.serialize(std::ostream_iterator<char>(os));
	return os;
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
#ifdef TEST_PICOJSON
#ifdef _MSC_VER
#pragma warning(disable : 4127) // conditional expression is constant
#endif

using namespace std;

static void plan(weInt num)
{
	printf("1..%d\n", num);
}

static void ok(bool b, const char* name = "")
{
	static weInt n = 1;
	printf("%s %d - %s\n", b ? "ok" : "ng", n++, name);
}

template <typename T> void is(const T& x, const T& y, const char* name = "")
{
	if (x == y) {
		ok(true, name);
	} else {
		ok(false, name);
	}
}

#include <algorithm>

weInt main(void)
{
	plan(61);
	
#define TEST(in, type, cmp, serialize_test) {				\
	pm_mode::json::value v;							\
	const char* s = in;							\
	string err = pm_mode::parse(v, s, s + strlen(s));			\
	ok(err.empty(), in " no error");					\
	ok(v.is<type>(), in " check type");					\
	is(v.get<type>(), cmp, in " correct output");			\
	is(*s, '\0', in " read to eof");					\
	if (serialize_test) {						\
		is(v.serialize(), string(in), in " serialize");			\
	}									\
}
	TEST("false", bool, false, true);
	TEST("true", bool, true, true);
	TEST("90.5", weDouble, 90.5, false);
	TEST("\"hello\"", string, string("hello"), true);
	TEST("\"\\\"\\\\\\/\\b\\f\\n\\r\\t\"", string, string("\"\\/\b\f\n\r\t"),
		 true);
	TEST("\"\\u0061\\u30af\\u30ea\\u30b9\"", string,
		 string("a\xe3\x82\xaf\xe3\x83\xaa\xe3\x82\xb9"), false);
	TEST("\"\\ud840\\udc0b\"", string, string("\xf0\xa0\x80\x8b"), false);
#undef TEST
	
#define TEST(type, expr) {					       \
	pm_mode::json::value v;						       \
	const char *s = expr;					       \
	string err = pm_mode::parse(v, s, s + strlen(s));		       \
	ok(err.empty(), "empty " #type " no error");		       \
	ok(v.is<pm_mode::type>(), "empty " #type " check type");	       \
	ok(v.get<pm_mode::type>().empty(), "check " #type " array size"); \
}
	TEST(array, "[]");
	TEST(object, "{}");
#undef TEST
	
	{
		pm_mode::json::value v;
		const char *s = "[1,true,\"hello\"]";
		string err = pm_mode::parse(v, s, s + strlen(s));
		ok(err.empty(), "array no error");
		ok(v.is<pm_mode::json::array>(), "array check type");
		is(v.get<pm_mode::json::array>().size(), size_t(3), "check array size");
		ok(v.get(0).is<weDouble>(), "check array[0] type");
		is(v.get(0).get<weDouble>(), 1.0, "check array[0] value");
		ok(v.get(1).is<bool>(), "check array[1] type");
		ok(v.get(1).get<bool>(), "check array[1] value");
		ok(v.get(2).is<string>(), "check array[2] type");
		is(v.get(2).get<string>(), string("hello"), "check array[2] value");
	}
	
	{
		pm_mode::json::value v;
		const char *s = "{ \"a\": true }";
		string err = pm_mode::parse(v, s, s + strlen(s));
		ok(err.empty(), "object no error");
		ok(v.is<pm_mode::json::object>(), "object check type");
		is(v.get<pm_mode::json::object>().size(), size_t(1), "check object size");
		ok(v.get("a").is<bool>(), "check property exists");
		is(v.get("a").get<bool>(), true,
		   "check property value");
		is(v.serialize(), string("{\"a\":true}"), "serialize object");
	}
	
#define TEST(json, msg) do {				\
	pm_mode::json::value v;					\
	const char *s = json;				\
	string err = pm_mode::parse(v, s, s + strlen(s));	\
	is(err, string("syntax error at line " msg), msg);	\
} while (0)
	TEST("falsoa", "1 near: oa");
	TEST("{]", "1 near: ]");
	TEST("\n\bbell", "2 near: bell");
	TEST("\"abc\nd\"", "1 near: ");
#undef TEST
	
	{
		pm_mode::json::value v1, v2;
		const char *s;
		string err;
		s = "{ \"b\": true, \"a\": [1,2,\"three\"], \"d\": 2 }";
		err = pm_mode::parse(v1, s, s + strlen(s));
		s = "{ \"d\": 2.0, \"b\": true, \"a\": [1,2,\"three\"] }";
		err = pm_mode::parse(v2, s, s + strlen(s));
		ok((v1 == v2), "check == operator in deep comparison");
	}
	
	{
		pm_mode::json::value v1, v2;
		const char *s;
		string err;
		s = "{ \"b\": true, \"a\": [1,2,\"three\"], \"d\": 2 }";
		err = pm_mode::parse(v1, s, s + strlen(s));
		s = "{ \"d\": 2.0, \"a\": [1,\"three\"], \"b\": true }";
		err = pm_mode::parse(v2, s, s + strlen(s));
		ok((v1 != v2), "check != operator for array in deep comparison");
	}
	
	{
		pm_mode::json::value v1, v2;
		const char *s;
		string err;
		s = "{ \"b\": true, \"a\": [1,2,\"three\"], \"d\": 2 }";
		err = pm_mode::parse(v1, s, s + strlen(s));
		s = "{ \"d\": 2.0, \"a\": [1,2,\"three\"], \"b\": false }";
		err = pm_mode::parse(v2, s, s + strlen(s));
		ok((v1 != v2), "check != operator for object in deep comparison");
	}
	
	{
		pm_mode::json::value v1, v2;
		const char *s;
		string err;
		s = "{ \"b\": true, \"a\": [1,2,\"three\"], \"d\": 2 }";
		err = pm_mode::parse(v1, s, s + strlen(s));
		pm_mode::json::object& o = v1.get<pm_mode::json::object>();
		o.erase("b");
		pm_mode::json::array& a = o["a"].get<pm_mode::json::array>();
		pm_mode::json::array::iterator i;
		i = std::remove(a.begin(), a.end(), pm_mode::json::value(std::string("three")));
		a.erase(i, a.end());
		s = "{ \"a\": [1,2], \"d\": 2 }";
		err = pm_mode::parse(v2, s, s + strlen(s));
		ok((v1 == v2), "check erase()");
	}
	
	return 0;
}

#ifdef _MSC_VER
    #undef SNPRINTF
    #pragma warning(pop)
#else
    #undef SNPRINTF
#endif

#endif
