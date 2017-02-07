


#include <string>
#include <iostream>



int main() {
	const char newLine = '\n';
	const char* sample = "s,a,m,p,l,e\nl,i,n,e,2\nl,i,n,e,3";
	//char source[sizeof(sample)];
	char* source = new char[0xff];
	strcpy(source, sample);
	//source[sizeof(source)] = '\0';


	//std::string string(source, source[sizeof(source)]);
	std::string string = source;

	std::string::size_type prePos = 0;
	std::string::size_type nowPos = 0;

	while (nowPos != std::string::npos) {
		nowPos = string.find_first_of(newLine, prePos);
		std::string line = string.substr(prePos, nowPos - prePos);
		std::cerr << line << "\nendofline" << std::endl;

		prePos = nowPos + sizeof(newLine);
	}

	//std::cerr << string << std::endl;
}

