


#include <iostream>
#include <type_traits>
#include <typeinfo>


namespace {

	unsigned int readSize = 0;

	template<typename Type>
	void readBinary(std::ifstream& fin, Type& value) throw() {
		fin.read((char*)&value, sizeof(Type));
		readSize += sizeof(Type);
	}

	template<typename Type, int N>
	void readBinary(std::ifstream& fin, Type (&array)[N]) throw() {
		fin.read((char*)&value, sizeof(Type));
		readSize += sizeof(Type) * N;
	}

}

struct Test {
	std::add_reference<int[3]>::type getArray() { return this->array_; }
	std::add_reference<const int[3]>::type getArray() const { return this->array_; }

	void setArray(int (&array)[3]) { this->array_[0] = array[0]; this->array_[1] = array[1]; this->array_[2] = array[2]; }

	int array_[3];
};


int main() {
	Test test;
	std::cout << typeid(test.getArray()).name() << std::endl;

	int array[2] = {0};
	test.setArray(array);
}
