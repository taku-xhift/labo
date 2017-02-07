

#include <iostream>
#include <string>
#include <sstream>
#include <Personal/StreamObject.hpp>

template<typename To, typename From>
To lexical_cast(const From& from_) {
	To result;
	std::stringstream ss;

	ss << from_;
	ss >> result;

	return result;
}

template<typename From>
class lexical_cast_t {

	From from;

public:

	lexical_cast_t(From from_) throw()
		: from(from_)
	{
	}


	template<typename To>
	operator To() const {
		return lexical_cast<To>(this->from);
	}
};


template<typename From>
lexical_cast_t<From> lexical_auto_cast(From from_) throw() {
	return lexical_cast_t<From>(from_);
}

int main() {
	using namespace std;

	int n = lexical_cast<int>("20");
	cerr << "n = " << n << endl;

	string strings = lexical_cast<string>(n);
	cerr << "strings = " << strings << endl;

	int n2 = lexical_auto_cast(strings);
	cerr << "n2 = " << n2 << endl;
	string strings2 = lexical_auto_cast(n2);
	cerr << "strings2 = " << strings2 << endl;


	so::out << "sample";
}
