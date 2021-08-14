

// Enum with its name (string)
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

#define ExEnum( classname, ... ) \
	struct classname { \
		static enum Tag { __VA_ARGS__ } _##classname##Tag; \
		static string toString(int i){ \
			static map<int, string> _str; \
			if( _str.empty() ){ \
				vector<string> _strvec; \
				boost::algorithm::split( _strvec , #__VA_ARGS__, \
										 boost::is_any_of(",")); \
				int key=0; \
				for(int j=0;j<_strvec.size();++j) { \
					vector<string> tmp; \
					boost::algorithm::split( tmp, _strvec[j], \
											 boost::is_any_of("=")); \
					boost::trim(tmp[0]); \
					if(tmp.size()>1) { \
						key = boost::lexical_cast<int>(tmp[1]); \
					} \
					_str.insert(std::pair<int, string>(key++,string(tmp[0]))); \
				} \
			} \
			return _str[i]; \
		} \
	}



// 宣言
ExEnum(color, RED=1, BLUE=2, GREEN=4, PINK);

int main()
{
	std::cout << color::RED << " " << color::BLUE << " "
		<< color::GREEN << " " << color::PINK << std::endl;
	std::cout << color::RED << " "
		<< color::toString(color::RED) << std::endl;
	std::cout << color::BLUE << " "
		<< color::toString(color::BLUE) << std::endl;
	std::cout << color::GREEN << " "
		<< color::toString(color::GREEN) << std::endl;
	std::cout << color::PINK << " "
		<< color::toString(color::PINK) << std::endl;
	color::Tag c = color::RED;  // タグへの代入も当然可能
	std::cout << c << color::toString(c) << std::endl;
}

