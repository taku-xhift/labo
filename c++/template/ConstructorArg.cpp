


#include <iostream>
#include <string>

template<typename Test1Type>
class Test1 {
public:
	Test1(std::string message_) : message(message_) {}

	std::string message;
};

template<typename Test1Type, typename Test2Type>
class Test2 {
public:
	Test2(Test1<Test1Type> data_) : data(data_) {}

	Test1<Test1Type> data;
};

int main() {

	Test2<int, Test1<int> >* test2 = new Test2<int, Test1<int> >(Test1<int>("message"));

	return 0;
}


