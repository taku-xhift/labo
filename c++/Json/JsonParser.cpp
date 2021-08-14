


#include <iostream>
//#include <vector>
#include <string>
#include <map>
//#include <boost/variant.hpp>


enum Type {
	type_string,
	type_array,
	type_hash,
};


struct Variant {
	union {
		bool boolean_;
		int integer_;
		float floating_;
		const char* string_;
	};
};


struct Hash {
	typedef std::multimap<std::string, Variant> List;
	typedef std::multimap<std::string, Variant>::iterator ListIte;
	typedef std::multimap<std::string, Variant>::const_iterator ListCIte;
	List list_;

	template<typename Type>
	Type get(const char* const key) const throw();

	template<>
	int get(const char* const key) const throw() {
		std::pair<ListCIte, ListCIte> itePair = this->list_.equal_range(key);
		return itePair.first->second.integer_;
	}
	template<>
	const char* get<const char*>(const char* const key) const throw() {
		std::pair<ListCIte, ListCIte> itePair = this->list_.equal_range(key);
		return itePair.first->second.string_;
	}
	template<>
	std::string get<std::string>(const char* const key) const throw() {
		std::pair<ListCIte, ListCIte> itePair = this->list_.equal_range(key);
		return std::string(itePair.first->second.string_);
	}

	std::pair<ListCIte, ListCIte> get(const char* const key) const throw() {
		return this->list_.equal_range(key);
	}
};


int main() {
	Hash value;
	Variant variant;

	variant.integer_ = 3;
	value.list_.insert(std::make_pair<std::string, Variant>("integer", variant));

	variant.floating_ = 4.0f;
	value.list_.insert(std::make_pair<std::string, Variant>("floating", variant));

	//std::strncpy(variant.string_, "Hello, World", 12);
	variant.string_ = "Hello, World";
	value.list_.insert(std::make_pair<std::string, Variant>("string", variant));

	for (int i = 0; i < 10; ++i) {
		variant.integer_ = i;
		value.list_.insert(std::make_pair<std::string, Variant>("Array", variant));
	}

	std::cout << value.get<std::string>("string").c_str() << std::endl;

	std::cout << "Output of Array" << std::endl;
	int count = 0;
	std::pair<Hash::ListCIte, Hash::ListCIte> list = value.get("Array");
	for (Hash::ListCIte ite = list.first; ite != list.second; ++ite, ++count) {
		std::cout << "Array[" << count << "] = " << ite->second.integer_ << std::endl;
	}
}


