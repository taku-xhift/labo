

#include <iostream>
#include <string>


struct Data
{
	Data()
	{
		strncpy(reinterpret_cast<char*>(this->name), "name test", sizeof(this->name));
	}

	unsigned char name[0x30];
};


int main()
{
	Data data;

	const char* name = static_cast<const char*>(data.name);

	std::cout << name << std::endl;
}


