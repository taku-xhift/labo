// 例外メッセージの自動生成
#define ExceptionMessage(message_) ExceptionMessageCreator(message_, __FILE__, __LINE__, __FUNCTION__)

#include <string>
#include <sstream>
#include <iostream>

std::string ExceptionMessageCreator(const std::string& message, const char* fileName, int line, const char* function) {
	std::stringstream ss;
	std::string returnValue;

	returnValue += "Exception is thrown!!\nmessage: " + message;

	returnValue.append("\nfile: ");
	returnValue.append(fileName);

	ss << line;
	returnValue += "\nline: ";
	returnValue += ss.str();

	returnValue.append("\nfunction: ");
	returnValue.append(function);
	returnValue.append("\n");

	return returnValue;
}


int main() {
	std::cout << ExceptionMessage("test") << std::endl;
}

