


#include <iostream>

template<int swfID, int xmlID = INT_MAX>
class Test
{
public:

	Test()
//		: swfID_(swfID)
//		, xmlID_(xmlID)
	{
		
	}

	int swfID_() {
		return swfID;
	}

//	int swfID_;
//	int xmlID_;
};


int main() {
	Test<100> test;
//	std::cout << "swfID = " << test.swfID_ << std::endl;
//	std::cout << "xmlID = " << test.xmlID_ << std::endl;
	std::cout << "swfID = " << test.swfID_() << std::endl;
}
