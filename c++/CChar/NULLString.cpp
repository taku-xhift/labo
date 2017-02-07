


#include <iostream>
#include <string>
#include <cstring>


int main() {
	const char* strings = "name";

	const char* temp;
	memmove((void*)temp, strings, strlen(strings));

	printf("%s\n", temp);

	void* voider = malloc(sizeof(void*));
	std::string stlstring(strings);
	stlstring.append(1, '\0');
	memmove(voider, stlstring.c_str(), strlen(stlstring.c_str()));

	printf("%s\n", (const char*)voider);

	return 0;
}


