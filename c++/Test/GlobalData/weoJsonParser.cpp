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

#include "weoJsonParser.h"


#define SAFE_DELETE(ptr) { if (!ptr) { delete ptr; ptr = NULL; } }


namespace pm_mode {
namespace json {


value::value() : type_(null_type) {}

value::value(Type type) : type_(type) {
	switch (type) {
#define INIT(p, v) case p##type: p = v; break
		INIT(boolean_, false);
		INIT(integer_, 0);
		INIT(naturalNumber_, 0u);
		INIT(number_, 0.0);
		INIT(string_, NEW std::string());
		INIT(array_, NEW array());
		INIT(object_, NEW object());
#undef INIT
	default: break;
	}
}

value::value(bool b) : type_(boolean_type) {
	boolean_ = b;
}

value::value(weInt i) : type_(integer_type) {
	this->integer_ = i;
}

value::value(weUint n) : type_(naturalNumber_type) {
	this->naturalNumber_ = n;
}

value::value(weDouble n) : type_(number_type) {
	number_ = n;
}

value::value(const std::string& s) : type_(string_type) {
	string_ = NEW std::string(s);
}

value::value(const array& a) : type_(array_type) {
	array_ = NEW array(a);
}

value::value(const object& o) : type_(object_type) {
	object_ = NEW object(o);
}

value::~value() {
	this->free();
}

value::value(const value& x) : type_(x.type_) {
	switch (type_) {
#define INIT(p, v) case p##type: p = v; break
		INIT(boolean_, x.boolean_);
		INIT(integer_, x.integer_);
		INIT(naturalNumber_, x.naturalNumber_);
		INIT(number_, x.number_);
		INIT(string_, NEW std::string(*x.string_));
		INIT(array_, NEW array(*x.array_));
		INIT(object_, NEW object(*x.object_));
#undef INIT
	default: break;
	}
}

value& value::operator=(const value& x) {
	if (this != &x) {
		this->~value();
		new (this) value(x);
	}
	return *this;
}

value::operator bool() const {
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

const value& value::get(size_t idx) const {
	static value s_null;
	assert(is<array>());
	return idx < array_->size() ? (*array_)[idx] : s_null;
}

const value& value::get(const std::string& key) const {
	static value s_null;
	assert(is<object>());
	//object::const_iterator i = object_->find(key);
	std::vector<DataSet>::iterator i = std::find_if(this->object_->value_.begin(), this->object_->value_.end(), FindByName(key));
	return i != this->object_->value_.end() ? i->value_ : s_null;
}

std::string value::to_str() const {
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

std::string value::serialize() const {
	std::string s;
	serialize(std::back_inserter(s));
	return s;
}

const value& value::reset(bool b) {
	this->free();

	this->type_ = boolean_type;
	this->boolean_ = b;
	return *this;
}
const value& value::reset(weInt i) {
	this->free();

	this->type_ = integer_type;
	this->integer_ = i;
	return *this;
}
const value& value::reset(weUint n) {
	this->free();

	this->type_ = naturalNumber_type;
	this->naturalNumber_ = n;
	return *this;
}
const value& value::reset(weDouble d) {
	this->free();

	this->type_ = number_type;
	this->number_ = d;
	return *this;
}
const value& value::reset(weString s) {
	this->free();

	this->type_ = string_type;
	this->string_ = NEW std::string(s);
	return *this;
}
const value& value::reset(const std::string& a) {
	this->free();

	this->type_ = string_type;
	this->string_ = NEW std::string(a);
	return *this;
}
const value& value::reset(const array& a) {
	this->free();

	this->type_ = array_type;
	this->array_ = NEW array(a);
	return *this;
}
const value& value::reset(const object& o) {
	this->free();

	this->type_ = object_type;
	this->object_ = NEW object(o);
	return *this;
}


void value::free() throw() {
	switch (this->type_) {
	case string_type:
		SAFE_DELETE(this->string_);
		break;
	case array_type:
		SAFE_DELETE(this->array_);
		break;
	case object_type:
		SAFE_DELETE(this->object_);
		break;
	default:
		break;
	}
}


void set_last_error(const std::string& s) {
	last_error_t<bool>::s = s;
}

const std::string& get_last_error() {
	return last_error_t<bool>::s;
}

bool operator==(const value& x, const value& y) {
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

bool operator!=(const value& x, const value& y) {
	return ! (x == y);
}

/////////////////////////////////////////////////////////////////

bool readJsonFile(value& data, const char* const fileName) throw() {
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

}
}

