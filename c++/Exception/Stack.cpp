


#include <iostream>
#include <string>

class Message {
public:
	Message(int line, const std::string& file, const std::string& function, const std::string& message) throw()
		: line_(line)
		, file_(file)
		, function_(function)
		, message_(message)
	{
		
	}


	int         line_;
	std::string file_;
	std::string function_;
	std::string message_;
};



void print() throw(Message) {
	throw Message(__LINE__, __FILE__, __FUNCTION__, "");
}


void catchAndThrow() throw(Message) {
	try {
		print();
	} catch(Message& e) {
		std::cout << "line = "      << e.line_      << "\n";
		std::cout << "file = "      << e.file_      << "\n";
		std::cout << "function = "  << e.function_  << "\n";
		std::cout << "message = "   << e.message_   << "\n";
		e.line_     = __LINE__;
		e.file_     = __FILE__;
		e.function_ = __FUNCTION__;
		throw;
	}
}


int main() {
	try {
		catchAndThrow();
	} catch (Message& e) {
		std::cout << "line = "      << e.line_      << "\n";
		std::cout << "file = "      << e.file_      << "\n";
		std::cout << "function = "  << e.function_  << "\n";
		std::cout << "message = "   << e.message_   << "\n";
		std::cout << std::endl;
	}
}


