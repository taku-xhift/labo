#include <stdexcept>
#include <boost/exception/all.hpp>

// 例外クラスを boost::exception を継承して定義すると…
class MyException
	: public boost::exception, public std::exception {};


int main() {
	std::cout << sizeof(MyException) << std::endl;
}
