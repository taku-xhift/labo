


#include <iostream>


//#define TYPEPUBLISH(type, num) static const unsigned int typeID = num;      \
//static unsigned int getTypeID() {                                           \
//	return #type ::typeID;                                                   \
//}

#define STRING(type) #type


#define callTest(name) :: ## name


int test = 0;

int main() {
	using namespace std;

	//cout << STRING(name) << endl;
	cout << callTest(test) << endl;
}


