


#include <iostream>
#include <vector>
#include <cassert>
#include <boost/static_assert.hpp>


#define WE_ASSERT(check, message) assert(check)


template<typename Type, std::size_t N>
int SizeOf(const Type (&/*array*/)[N]) throw() {
	return N;
}

template<typename Type>
int SizeOf(const Type container) throw() {
	return container.size();
}

template<typename Type, std::size_t N>
void Resize(Type (&/*array*/)[N], unsigned int size) throw() {
	// Can not do anything!!!
	WE_ASSERT(N < size, "Can not Resize!!!");
}

template<typename Type>
void Resize(Type& container, unsigned int size) throw() {
	container.resize(size);
}

int main() {
	const int size = 10;
	int array[size];
	std::vector<int> container;

	for (int i = 0; i < size; ++i) {
		array[i] = i;
		container.push_back(i);
	}

	if (SizeOf(array) < size) {
		Resize(array, size);
	}
	if (SizeOf(container) < size) {
		Resize(container, size);
	}

	std::cout << SizeOf(array) << std::endl;
	std::cout << SizeOf(container) << std::endl;
}


