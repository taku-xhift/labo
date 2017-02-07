


#include <iostream>

struct NULLType {
	static void execute() { std::cout << "NULL" << std::endl; }
};

struct Executer {
	static void execute() { std::cout << "Hello" << std::endl; }
};

template<typename Type>
class Test {
public:
	void execute() {
//		Type::execute();
	}
};

int main() {
	Test<NULLType> testNULL;
	Test<Executer> testExe;
	Test<NULL> testExe;

	testNULL.execute();
	testExe.execute();

	return 0;
}

