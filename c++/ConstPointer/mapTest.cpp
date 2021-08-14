#include <iostream>
#include <map>
#include <string>

typedef ::std::map<int, ::std::string> KeyState;


int main()
{
	KeyState keyState;
	keyState.insert(::std::map<int, ::std::string>::value_type(0, "0"));


	KeyState::iterator kmIterator = keyState.begin();
	while (kmIterator != keyState.end()) {
		if ((*kmIterator).first == 1) {
			::std::cout << (*kmIterator).second << std::endl;
		}
		++kmIterator;
	}


	return 0;
}

