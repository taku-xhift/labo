


#include <iostream>
#include <string>
#include <malloc.h>
#include <cstring>


class Test {
public:
	void* temp;

	Test() {
		this->temp = calloc(1, sizeof(void*));
	}
};


Test get(void* out, const char* strings_) {
	Test test;
	std::string str(strings_);
	str.append(1, '\0');
	memmove(test.temp, str.c_str(), strlen(str.c_str()));
	return test;
}


int main() {
	void* out = calloc(1, sizeof(void*));
	Test test = get(out, "name");
	std::cerr << (const char*)(test.temp) << std::endl;

	return 0;
}

