


#include <iostream>

template<unsigned int count>
class Count {
private:
	static const unsigned int uniqueCount = count;
public:
	static const unsigned int get = Count<count + 1>::count;
};

int main() {
	using namespace std;
	static unsigned int zero = Count<0>::get;
	//static unsigned int one = Count<0>::get;

	//out << zero << endl;
	//out << one << endl;
}
