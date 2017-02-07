

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <functional>

std::function<int (int, int)> plus     = [](int lhs, int rhs) { return lhs + rhs; }; 
std::function<int (int, int)> minus    = [](int lhs, int rhs) { return lhs - rhs; };
std::function<int (int, int)> products = [](int lhs, int rhs) { return lhs * rhs; };
std::function<int (int, int)> digit    = [](int lhs, int rhs) { return lhs / rhs; };
std::function<int (int, int)> empty    = [](int lhs, int rhs) { return lhs * 10 + rhs; };

struct Func {
	std::function<int (int, int)> func;
	const char* str; 
} const funcList[] = {
	{ plus          , " + " },
	{ minus         , " - " },
	{ products      , " * " },
	{ digit         , " / " },
	{ empty         , ""    },
};

template<typename T, std::size_t N>
std::size_t size(const T(&array)[N]) {
	return N;
}

bool IsGood(const std::string& org, const std::string& src) {
	// std::string reversed = src.reverse();	
	std::string reversed(src.rbegin(), src.rend());	
	return reversed == src;
}

std::vector<int> Factorization(const std::string& src) {
	std::vector<int> ret(4, 0);
		
	std::stringstream ss;
	
	for (size_t i = 0; i < src.size(); ++i) {
		ss << src[i];
		ss >> ret.at(i);
		ss.str("");
		ss.clear();
	}
	
	return std::move(ret);
}


void Check(const std::string& src) {
	std::stringstream ss;
	auto list = Factorization(src);
	int digitNum = 3;
	
	for (size_t i = 0; i < size(funcList); ++i)
	for (size_t j = 0; j < size(funcList); ++j)
	for (size_t k = 0; k < size(funcList); ++k) {
		if (i == 3 && )
		
		int temp1 = funcList[i].func(list.at(0), list.at(1));
		int temp2 = funcList[j].func(temp1, list.at(2));
		int temp3 = funcList[k].func(temp2, list.at(3)); 
		ss << temp3; 
		bool isGood = src == ss.str();  
		if (isGood == true) {
			std::cout << temp3 << ":\n"
				<< "\t" << list.at(0)
						<< funcList[i].str << list.at(1)
						<< funcList[j].str << list.at(2)
						<< funcList[k].str << list.at(3) << "\n";
		}
		ss.str("");
		ss.clear();
	}
}




int main() {
	std::stringstream ss;
	std::string str;
	for (int i = 1000; i < 10000; ++i) {
		ss << i;
		ss >> str;
		Check(str);
	}
}

